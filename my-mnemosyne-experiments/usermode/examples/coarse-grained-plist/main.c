/*!
 * TODO: Free td memory
 *
 *PROBLEMS: for transcationally pmalloc the lhs var has to be global other wise crash.
 */
#include <math.h>
#include "pvar.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

mynode_t* node;

/*should sum upto 100*/
uint num_insert_percent = 50;
uint num_delete_percent = 40;
uint num_lookup_percent = 10;
uint num_insert, num_delete, num_lookup;
double duration;
struct timeval start_time, end_time;

/**************************************************************************************/
//barrier code
/**************************************************************************************/
//Barrier code
typedef struct barrier {
    pthread_cond_t complete;
    pthread_mutex_t mutex;
    int count;
    int crossing;
} barrier_t;

pthread_t thr[NUM_THREADS];
struct thread_info{
   uint  thread_id;
   barrier_t *barrier;
};

void barrier_init(barrier_t *b, int n)
{
    pthread_cond_init(&b->complete, NULL);
    pthread_mutex_init(&b->mutex, NULL);
    b->count = n;
    b->crossing = 0;
}

void barrier_cross(barrier_t *b)
{
    pthread_mutex_lock(&b->mutex);
    b->crossing++;
   // printf("crossing val: %d count: %d\n",b->crossing, b->count);
    /* If not all here, wait */
    if (b->crossing < b->count) {
        pthread_cond_wait(&b->complete, &b->mutex);
    } else {
        pthread_cond_broadcast(&b->complete);

        //printf("reset barrier\n");
        b->crossing = 0;
    }
    pthread_mutex_unlock(&b->mutex);
}

//evaluation code:
struct timeval start_time, end_time;

void* finder(void *threadData)
{
	struct thread_info *d = (struct thread_info *)threadData;
	int tid = d->thread_id;
	barrier_cross(d->barrier);

	for (int i = 0; i < 1; ++i){
		uint key = rand()%(MAX_KEY-1) + 1;
		uint val = rand()%(MAX_KEY-1) + 1;
		uint res = find(((list_t*)PADDR(mylist)), key, &val);		
	}
}

void* remover(void *threadData)
{
	struct thread_info *d = (struct thread_info *)threadData;
	int tid = d->thread_id;
	barrier_cross(d->barrier);
	for (int i = 0; i < 1; ++i){
		uint key = rand()%(MAX_KEY-1) + 1;
		uint val = rand()%(MAX_KEY-1) + 1;
		uint res = del(((list_t*)PADDR(mylist)), key, &val);		
	}
}

void* adder(void *threadData)
{
	struct thread_info *d = (struct thread_info *)threadData;
	int tid = d->thread_id;
	barrier_cross(d->barrier);
	for (int i = 0; i < 1; ++i)
	{
		uint key = rand()%(MAX_KEY-1) + 1;
		uint val = rand()%(MAX_KEY-1) + 1;
		uint res = insert(((list_t*)PADDR(mylist)), key, val);
	}
}

void list_bench()
{
	barrier_t barrier;
	struct thread_info *td;
	td = (struct thread_info*)malloc(NUM_THREADS*sizeof(struct thread_info));
	barrier_init(&barrier, NUM_THREADS +1);

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		td[i].thread_id = i;
		td[i].barrier = &barrier;
		
		if(i < num_insert)
		{
			pthread_create(&thr[i], NULL, &adder, (void *)&td[i]);
		}
		else if(i < (num_insert + num_delete ))
		{
			pthread_create(&thr[i], NULL, &remover, (void *)&td[i]);
		}
		else if(i < (num_insert + num_delete + num_lookup))//init for lookup threads
		{
			pthread_create(&thr[i], NULL, &finder, (void *)&td[i]);
		}
		else
		{
			printf("screwed thread distribution: NUM_THREADS should be multiple of 10\n");
			return;
		}
	}

	printf("STARTING:*****************\n");
	barrier_cross(&barrier);
	gettimeofday(&start_time, NULL);

	

	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(thr[i], NULL);
	}
	gettimeofday(&end_time, NULL);
	printf("STOPPING:*****************\n");

/*	pthread_create(&thr[0], NULL, &adder, NULL);
	pthread_create(&thr[1], NULL, &remover, NULL);
	pthread_create(&thr[2], NULL, &finder, NULL);

	pthread_join(thr[0], NULL);
	pthread_join(thr[1], NULL);
	pthread_join(thr[2], NULL);*/



}

int main (int argc, char const *argv[])
{
	time_t tt;
	srand(time(&tt));

	#ifdef TIME_EVAL
	FILE *fptr;
	char buf[10];
	sprintf(buf, "%d", NUM_THREADS);
	fptr = fopen(buf,"a");
	if(fptr == NULL)
	{
		printf("Error!");   
		exit(1);             
	}
	#endif
	PSET(flag, 0);

	printf("persistent flag: %d\n", PGET(flag));
	printf("persistent list addr: %p\n", (list_t*)PADDR(mylist));
	//printf("list node count:%d\n",((list_t*)PADDR(mylist))->node_count);

	if((num_insert_percent + num_delete_percent + num_lookup_percent) != 100)
	{
		printf("Oo LaLa! Seems you got arithmatic wrong :) #operations should sumup to 100\n");
		return 0;
	}

	num_insert = (uint)((num_insert_percent*NUM_THREADS)/100);
	num_delete = (uint)((num_delete_percent*NUM_THREADS)/100);
	num_lookup = (uint)((num_lookup_percent*NUM_THREADS)/100);

	printf(" num_insert: %d\n num_delete: %d\n num_lookup: %d\n", num_insert, num_delete, num_lookup);
	if((num_insert + num_delete + num_lookup) > NUM_THREADS)
	{
		printf("((insertNum + delNum + lookupNum) > number_of_threads)\n");
		return 0;
	}

	PTx {
		if (PGET(flag) == 0) {
			PSET(flag, 1);
			printf("INIT LIST: \n");
			init();
			print_list(((list_t*)PADDR(mylist)));
		} else {
			printf("LIST ALREADY INITED: \n");
			recover_init();//to re init locks
		}
	}
	
	printf(" --> %d\n", PGET(flag));
	printf("&persistent flag = %p\n", PADDR(flag));

	list_bench();
	print_list(((list_t*)PADDR(mylist)));
	
	duration = (end_time.tv_sec - start_time.tv_sec);
	duration += ( end_time.tv_usec - start_time.tv_usec)/ 1000000.0;

	printf("time: %lf seconds\n", duration);
	#ifdef TIME_EVAL
	fprintf(fptr,"%lf\n",duration);
	fclose(fptr);
	#endif
	return 0;
}

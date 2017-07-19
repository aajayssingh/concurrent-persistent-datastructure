/*!
 * \file
 *
 *PROBLEMS: for transcationally pmalloc the lhs var has to be global other wise crash.
 */
#include "pvar.h"
#include <stdio.h>
#include <stdlib.h>
/*#include <pmalloc.h>
#include <pthread.h>
#include <signal.h>*/

unsigned long long cl_mask = 0xffffffffffffffc0;
#define sz 32
#define count 100000
long *ptr;
long* ptrl;
mynode_t* node;

pthread_t thr[3];/*thr[NUM_THREADS];*/

/**************************************************************************************/
//List Global declarations
/**************************************************************************************/



void* finder()
{
	for (int i = 0; i < 5; ++i){
		uint key = rand()%10 + 1;
		uint val = rand()%10 + 1;
		uint res = find(((list_t*)PADDR(mylist)), key, &val);		
	}
}

void* remover()
{
	for (int i = 0; i < 5; ++i){
		uint key = rand()%10 + 1;
		uint val = rand()%10 + 1;
		uint res = del(((list_t*)PADDR(mylist)), key, &val);		
	}
}

void* adder()
{
	for (int i = 0; i < 10; ++i)
	{
		uint key = rand()%(10) + 1;
		uint val = rand()%(10) + 1;
		uint res = insert(((list_t*)PADDR(mylist)), key, val);
	}
}

void* worker()
{
	uint key = rand()%(MAX_KEY - 1) + 1;
	uint val = rand()%(MAX_KEY - 1) + 1;
	uint res = insert(((list_t*)PADDR(mylist)), key, val);
}

void malloc_bench()
{
	/*for (int i = 0; i < NUM_THREADS; ++i)
	{
		pthread_create(&thr[i], NULL, &worker, NULL);
	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(thr[i], NULL);
	}*/
	pthread_create(&thr[0], NULL, &adder, NULL);
	pthread_create(&thr[1], NULL, &remover, NULL);
	pthread_create(&thr[2], NULL, &finder, NULL);

	pthread_join(thr[0], NULL);
	pthread_join(thr[1], NULL);
	pthread_join(thr[2], NULL);



}

int main (int argc, char const *argv[])
{
	time_t tt;
	srand(time(&tt));

	printf("persistent flag: %d\n", PGET(flag));
	printf("persistent list addr: %p\n", (list_t*)PADDR(mylist));
	printf("list node count:%d\n",((list_t*)PADDR(mylist))->node_count);
//	((list_t*)PADDR(mylist))->node_count = ((list_t*)PADDR(mylist))->node_count+1;

		
	
	
	
/*	if (PGET(flag) == 0){
		PTx { node = (mynode_t*)pmalloc(sizeof(mynode_t)); }
		node->key = 98;
		((list_t*)PADDR(mylist))->head = node;
		printf("persistent HEAD addr: %p\n", ((list_t*)PADDR(mylist))->head);

		printf("key: %d\n", ((list_t*)PADDR(mylist))->head->key);
	}
	else{
		printf("persistent list HEAD addr: %p, key: %d", ((list_t*)PADDR(mylist))->head, ((list_t*)PADDR(mylist))->head->key);
	}*/
//	PSET(flag, 0);

	PTx {
		if (PGET(flag) == 0) {
			PSET(flag, 1);
			printf("INIT LIST: \n");
			//init();
		} else {
			printf("LIST ALREADY INITED: \n");
			//recover_init();

			// adder();
			// print_list(((list_t*)PADDR(mylist)));
			// printf("**************************************\n");
			//remover();
			// uint key = rand()%(MAX_KEY - 1) + 1;
			// uint val = rand()%(MAX_KEY - 1) + 1;
			// uint res = insert(((list_t*)PADDR(mylist)), key, val);
			PSET(flag, 0);
		}
	}
	
	printf(" --> %d\n", PGET(flag));
	printf("&persistent flag = %p\n", PADDR(flag));

	//printf("\nstarting malloc bench\n");
	//malloc_bench();
	//print_list(((list_t*)PADDR(mylist)));
	return 0;
}

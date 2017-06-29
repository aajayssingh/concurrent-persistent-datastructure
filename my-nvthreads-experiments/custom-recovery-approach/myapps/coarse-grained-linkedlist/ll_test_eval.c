/*
NVThread coarse grained linked list with evaluation
*/


#include <iostream>
#include <pthread.h>
#include <unistd.h> // for sleep function
#include<climits>
#include <math.h>
#include <fstream>

#include <sys/time.h>
#include <time.h>
#include <mutex>
#include "linkedlist.h"

using namespace std;

/**********************************************************************************************************************************************/
//  FUNCTION DECLARATION
/**********************************************************************************************************************************************/

void* test(void *threadData);



/**********************************************************************************************************************************************/
//  MACROS DECLARATION
/**********************************************************************************************************************************************/
#define VAL_MIN  0
#define VAL_MAX  99
#define DEBUG0

/**********************************************************************************************************************************************/
//  GLOBAL DECLARATION
/**********************************************************************************************************************************************/

list_t *list;
fstream file10runGTOD, file10runCPU, file10runTH, file10runRT, file10runCLOCK;

static int ic = 0;

#ifdef DEBUG
mutex mtx, mtxc;
#endif

//Barrier code
typedef struct barrier {
    pthread_cond_t complete;
    pthread_mutex_t mutex;
    int count;
    int crossing;
} barrier_t;

void barrier_init(barrier_t *b, int n)
{
    pthread_cond_init(&b->complete, NULL);
    pthread_mutex_init(&b->mutex, NULL);
    b->count = n;
//    cout<<"init barrier "<<n<<endl;
    b->crossing = 0;
}

void barrier_cross(barrier_t *b)
{
    pthread_mutex_lock(&b->mutex);
    /* One more thread through */
    //printf("crossing val: %d, %d\n",b->crossing, ic);
    b->crossing++;
    ic++;

#ifdef DEBUG
    printf("aj crossings %d %d\n",b->crossing, ic);
#endif
    /* If not all here, wait */
    if (/*b->crossing*/ic < b->count) {
        pthread_cond_wait(&b->complete, &b->mutex);
    } else {
        pthread_cond_broadcast(&b->complete);
        /* Reset for next time */
        #ifdef DEBUG
        printf("reset barrier\n");
        #endif
        b->crossing = 0;
        ic = 0;
    }
    pthread_mutex_unlock(&b->mutex);
}


struct thread_info{
   int  thread_id;
   int thread_key;
   int thread_val;//value to be inserted for insert operation
   int thread_op;//insert = 0,   delete = 1, lookup = 2
   barrier_t *barrier;
};

int number_of_threads = 50;
pthread_t *threads ;

//number of delete, insert and lookup threads
int delNum = 0, insertNum = 0, lookupNum = 0;

//default percentage of delete , insert and lookup threads
float delp = 20, insertp = 60, lookp = 20;

//AJ
struct timespec startajcpu, startajth, startajrt, finishajcpu, finishajth, finishajrt;
double elapsedajrt;
double elapsedajcpu;
double elapsedajth, duration;
//clock_t timeaj;
struct timeval start, endaj;
//AJ

void *taj(void *args)
{ 
    lkey_t key;  //key range forced to 1 to 99 (0 and 100 are for sentinel)
    val_t v;

   // pthread_mutex_lock(&gm);
    for (int i = 0; i < 10; i++)
    {
        key = rand()%(VAL_MAX - 1) + 1;
        v = rand()%(VAL_MAX - 1) + 100;        
        add(list, key, v);
    }  

    // pthread_mutex_unlock(&gm);
 
    nvcheckpoint();//redundant check later
  //  free(args);
    pthread_exit(NULL);
}



int main()
{
    printf("Checking crash status\n");
    if ( isCrashed() )
    {
        printf("I need to recover!\n");

        gettimeofday(&start, NULL);
        list = recover_init_list();
        printf("Recovered list...\n");

        printf("list->head->key: %d\n", list->head->key);
        printf("list->head->next->key: %d\n", list->head->next->key);

        sort_list(list);

        gettimeofday(&endaj, NULL);

        show_list (list);

        duration = (endaj.tv_sec - start.tv_sec);
        duration += ( endaj.tv_usec - start.tv_usec)/ 1000000.0;
        cout<<"recover time in (s):"<<duration<<endl;
    }
    else    
    {
        struct thread_info *td; //to store each thread information
        int rc;
        int i;
        void *status;
        int val = 0;
        time_t t;
        barrier_t barrier;
        pthread_t tid1;

        srand((unsigned) time(&t));

        /*ALLOCATING MEMORY TO THREADS FOR BOOKEEPING*/
        threads = new pthread_t [number_of_threads];//pthread_t threads[NUMTHREADS];
        td = new struct thread_info [number_of_threads];//struct thread_info td[NUMTHREADS];

        if((threads == nullptr)||(td == nullptr))
        {
            cout<<"error allocating memory";
        }

        // openfile to store completion time for plotting performance graphs
        file10runGTOD.open("runGTOD.txt", fstream::out | fstream::app);
        file10runCPU.open("runCPU.txt", fstream::out | fstream::app);
        file10runTH.open("runTH.txt", fstream::out | fstream::app);
        file10runRT.open("runRT.txt", fstream::out | fstream::app);
        file10runCLOCK.open("runCLOCK.txt", fstream::out | fstream::app);

        //INIT LIST

        list = init_list();

        //add some nodes initially
        lkey_t key;  //key range forced to 1 to 99 (0 and 100 are for sentinel)
        val_t v;

        pthread_create(&tid1, NULL, taj, NULL);
        pthread_join(tid1, NULL);
       
        cout<<"starting list:"<<endl;
        show_list(list);

        insertNum = (int)ceil((insertp*number_of_threads)/100);
        delNum = (int)ceil((delp*number_of_threads)/100);
        lookupNum = (int)ceil((lookp*number_of_threads)/100);

        cout<<"#operations over the list:\n";
        cout<<"#insert:"<<insertNum<<" "<<"#delete:"<<delNum<<" "<<"#lookup:"<<lookupNum<<endl;
        //exception verification
        if((insertNum + delNum + lookupNum) > number_of_threads)
        {
            cout<<"((insertNum + delNum + lookupNum) > number_of_threads)"<<endl;
            cout<<insertNum<<" "<<delNum<<" "<<lookupNum<<endl;
            return 0;
        }

        barrier_init(&barrier, number_of_threads +1);


        cout<<"creating "<<number_of_threads<<" threads:"<<endl;
        /*INITIATING THREADINFO */
        for( i=0; i < number_of_threads; i++ )
        {
            #ifdef DEBUG
            cout <<"main() : creating thread, " << i << endl;
            #endif
            td[i].thread_id = i;
            td[i].barrier = &barrier;

            if(i < insertNum)//init threaddata for insert threads
            {
                td[i].thread_op = 0;
                td[i].thread_key = rand()%(VAL_MAX - 1) + 1;  //1 t0 99: 0 & 100 is reserved for head and tail
                td[i].thread_val = td[i].thread_key +100;//value of linked list to be inserted
                val = td[i].thread_val;
            }
            else if(i < (insertNum + delNum ))//init threadData for delete threads
            {
                td[i].thread_op = 1;
                td[i].thread_key = rand()%(VAL_MAX - 1) + 1;  //1 t0 99: 0 & 100 is reserved for head and tail
                td[i].thread_val = td[i].thread_key +100;
            }
            else if(i < (insertNum + delNum + lookupNum))//init for lookup threads
            {
                td[i].thread_op = 2;
                td[i].thread_key = rand()%(VAL_MAX - 1) + 1;  //1 t0 99: 0 & 100 is reserved for head and tail
                td[i].thread_val = td[i].thread_key +100;
            }
            else
            {
              cout<<"something wrong in thread distribution to operations"<<endl;
            }

            //creating threads for insert del and lookup operations
            {
                rc = pthread_create(&threads[i], NULL,
                test, (void *)&td[i]);
                if (rc)
                {
                    cout << "Error:unable to create thread," << rc << endl;
                    exit(-1);
                }
            }
        }//FOR

        /* main thread awakes all threads */
        barrier_cross(&barrier);
        cout<<"STARTING..."<<endl;
        //init time to log completion time into file

        gettimeofday(&start, NULL);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startajcpu);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &startajth);
        clock_gettime(CLOCK_MONOTONIC_RAW, &startajrt);

        double timeaj;
        timeaj = clock();


        /*WAIT FOR ALL THREADS TO FINISH*/
        for( i=0; i < number_of_threads; i++ )
        {
            rc = pthread_join(threads[i], &status);
            //cout<<"joinin";
            if (rc)
            {
                cout << "Error:unable to join," << rc << endl;
                exit(-1);
            }
        }


        //log completion time
        gettimeofday(&endaj, NULL);
        //CLOCK_MONOTONIC_RAW
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &finishajcpu);
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &finishajth);
        clock_gettime(CLOCK_MONOTONIC_RAW, &finishajrt);
        timeaj = clock() - timeaj;

        timeaj = clock() - timeaj;
        timeaj = ((double)timeaj)/(CLOCKS_PER_SEC);


        cout<<"STOPPING..."<<endl;


        duration = (endaj.tv_sec - start.tv_sec);
        duration += ( endaj.tv_usec - start.tv_usec)/ 1000000.0;

        //  elapsedaj = (finishaj.tv_sec - startaj.tv_sec);
        //elapsedaj += (finishaj.tv_nsec - startaj.tv_nsec) / 1000000000.0;

        elapsedajcpu = (finishajcpu.tv_sec - startajcpu.tv_sec);
        elapsedajcpu += (finishajcpu.tv_nsec - startajcpu.tv_nsec) / 1000000000.0;

        elapsedajth = (finishajth.tv_sec - startajth.tv_sec);
        elapsedajth += (finishajth.tv_nsec - startajth.tv_nsec) / 1000000000.0;
        elapsedajrt = (finishajrt.tv_sec - startajrt.tv_sec);
        elapsedajrt += (finishajrt.tv_nsec - startajrt.tv_nsec) / 1000000000.0;



        cout<<"time in (s):"<<duration<<endl;
        //cout<<"clock() in (s)"<<timeaj<<endl;
      //  cout<<"gettimeofday() in (s)"<<duration<<endl;
        // cout<<"elapsedajcpu in (s)"<<elapsedajcpu<<endl;
        // cout<<"elapsedajth in (s)"<<elapsedajth<<endl;
        // cout<<"elapsedajrt in (s)"<<elapsedajrt<<endl;
        // printf("clock timeaj %lf \n", timeaj);
        cout<<"final list"<<endl;
        show_list(list);

        printf("internally abort! node count: %d\n", list->node_count);
        abort(); 

        file10runGTOD<<duration<<endl;
        file10runCPU<<elapsedajcpu<<endl;
        file10runTH<<elapsedajth<<endl;
        file10runRT<<elapsedajrt<<endl;
        file10runCLOCK<<timeaj<<endl;


        delete[] threads;
        delete[] td;
    }
    return 0;
}//main()




/*
*DESCRIPTION :  test() executes insert, delete or lookup operation by reading the thread_op of each thread
                if thread_op = 0 --> insert()
                or thread_op = 1 --> delete()
                or thread_op = 2 --> lookup()
*AUTHOR      :  AJAY SINGH
*COMPANY     :  IIT Hyderabad
*REMARK      :  didnot made separate set_add() as threadData was not getting carried and causing crash   TODO
*/
void* test(void *threadData)
{
thread_info *d = (thread_info *)threadData;
int tid = d->thread_id;

/*barrier for all threads otherwise sum inserting threads may arrive later than the main threads finish joining.*/
barrier_cross(d->barrier);

/*......................................................INSERT............................................................................*/
if(d->thread_op == 0)//insert()
{
    lkey_t key = d->thread_key;
    val_t v = d->thread_val;
    bool res = add(list, key, v); //key 0 reserved for head node

#ifdef DEBUG
    mtx.lock();
    if(res)
    {
        printf("added [key:%d, val:%d]\n", key, v);
    }
    else
    {
        printf("could not add key:%d \n", key);
    }
    mtx.unlock();
#endif

}//if(d->thread_id < insertNum)//insert()

/*......................................................INSERT END............................................................................*/

/*......................................................DELETE................................................................................*/
else if(d->thread_op == 1)//(d->thread_id < insertNum + delNum)//delete()
{
    lkey_t key = d->thread_key;
    val_t v ;

    bool res = remove(list, key, &v);
    #ifdef DEBUG
    mtx.lock();
    if(res)
    {
        printf("deleted [key:%d, val:%d]\n", key, v);
    }
    else
    {
        printf("could not delete key:%d\n", key);
    }
    mtx.unlock();
#endif
}//remove
/*......................................................DELETE END............................................................................*/

/*......................................................LOOKUP............................................................................*/
else if(d->thread_op == 2)//find
{
    lkey_t key = d->thread_key;
    val_t v ;

    bool res = find(list, key, &v);
    #ifdef DEBUG
    mtx.lock();
    if(res)
        printf("found [key:%d, val:%d] \n", key, v);
    else
        printf("not found key: %d \n", key);
    mtx.unlock();
    #endif
}

/*......................................................LOOKUP END............................................................................*/

//    mtxc.lock();
//    cout<< d->thread_id<<"exiting"<<endl;
//    mtxc.unlock();

   pthread_exit(NULL);
}
/*!
 * DESCP:     Driver file for coarse grained persistent list implemented using Nvthreads.
 
 * AUTHOR:      Ajay Singh, IIT Hyderabad
 
 * ORGANIZATION:  LIP6 - INRIA&UPMC.
 * DATE:      Jul 25, 2017.
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

list_t *list;
pthread_mutex_t gm;
unsigned int num_threads = 1;

struct thread_data {
    int tid;
};


void *t(void *args){  

    lkey_t key = -1;  //key range forced to 1 to 99 (0 and 100 are for sentinel)
    val_t v = -1;

pthread_mutex_lock(&gm);
    list = init_list();

    //show list after init
   // show_list_with_offsets(list);
    
    for (int i = 0; i < 1; i++)
    {
        key = rand()%(VAL_MAX - 1) + 1; // 1 - 99
        v = rand()%(VAL_MAX - 1) + 100;        
        add(list, key, v);
    }

/*    for (int i = 0; i < 10; i++)
    {
        key = rand()%(VAL_MAX - 1) + 1; // 1 - 99
        v = rand()%(VAL_MAX - 1) + 100;        
        del(list, key, &v);
    }*/

    pthread_mutex_unlock(&gm);

    nvcheckpoint();
    pthread_exit(NULL);
}

/*
using -num_threads and + tid to keep tid within range
*/
void *ajt(void *args){
    struct thread_data *data = (struct thread_data*)args;
    int tid = data->tid;
    lkey_t key = -1;  //key range forced to 1 to 99 (0 and 100 are for sentinel)
    val_t v = -1;

    //pthread_mutex_lock(&gm);

   // if((tid%2) == 0)
    {
        for (int i = 1; i < 5; i++)
        {
            key = rand()%(VAL_MAX - num_threads) + 1 + tid; // num_threads is used for fair distribution of keys
            v = rand()%(VAL_MAX - 1) + 100;        
        
            add(list, i, v);    

        }

    }
    // else if(tid == 1)
    // {
    //     for (int i = 0; i < 2; i++)
    //     {
    //         key = rand()%(VAL_MAX - num_threads) + 1 + tid; // 1 - 99
    //         //v = rand()%(VAL_MAX - 1) + 100;        
    //         find(list, key, &v);
    //     }
    // }
    // else /*if(tid == 2)*/
    // {
    //     for (int i = 0; i < 10; i++)
    //     {
    //         key = rand()%(VAL_MAX - num_threads) + 1 + tid; // 1 - 99
    //         //v = rand()%(VAL_MAX - 1) + 100;        
    //         del(list, key, &v);
    //     }
    // }
    
   // pthread_mutex_unlock(&gm);
 
    free(args);
    nvcheckpoint();
    pthread_exit(NULL);
}

int main()
{
    printf("Checking crash status\n");
    if ( isCrashed() )
    {
        printf("I need to recover!\n");
        list = recover_init_list();
        //show_list(list);
        show_list_with_offsets(list);
    }
    else    
    {
        lkey_t key;  //key range forced to 1 to 99 (0 and 100 are for sentinel)
        val_t v;        
        pthread_t tid1;
        pthread_t tid[num_threads];
        pthread_mutex_init(&gm, NULL);
        time_t tt;
        srand(time(&tt));
      
        //INIT LIST
        pthread_create(&tid1, NULL, t, NULL);

        nvcheckpoint();
        pthread_join(tid1, NULL); //wait for init thread to fisnish and persist


        printf("\t\tMULTITHREAD OPS BEGIN :\n");
        /*logic for multithread goes here: */
        for (int i = 0; i < num_threads; i++)
        {
            struct thread_data *tmp = (struct thread_data*)malloc(sizeof(struct thread_data));
            tmp->tid = i;
            pthread_create(&tid[i], NULL, ajt, (void*)tmp);
            //srand(i);
        }



        nvcheckpoint();
        for (int i = 0; i < num_threads; i++)
        {
            pthread_join(tid[i], NULL);
        }

        //show_list(list); 
        nvcheckpoint();

        //pthread_mutex_lock(&gm);  
        show_list_with_offsets(list);
        //pthread_mutex_unlock(&gm);         
        printf("internally abort! node_count: %d, real_node_count: %d\n", list->node_count, list->real_node_count);
        abort(); 
    }

    return 0;
}//main()


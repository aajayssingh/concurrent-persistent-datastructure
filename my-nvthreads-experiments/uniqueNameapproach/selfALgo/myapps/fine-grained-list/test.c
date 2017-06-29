
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "nvrecovery.h"
#include "linkedlist.h"

pthread_mutex_t gm;
#define touch_pages 10
#define touch_size 4096 * touch_pages
int threads_num = 10;
list_t *list;
// aggregate data structures
struct bar{
    int a;
    char c[15000];
};
struct foo{
    int id;
    struct bar b;
};


struct thread_data {
    int tid;
    struct foo *local_data;
};

void *t(void *args){
    struct thread_data *data = (struct thread_data*)args;
    int tid = data->tid;
    struct foo *tmp = data->local_data;

    pthread_mutex_lock(&gm);

    wrappercreate(list);
    printf("\n");
  
    pthread_mutex_unlock(&gm);
 
    free(args);
    pthread_exit(NULL);
}

int main(){
    pthread_mutex_init(&gm, NULL);
    pthread_t tid[threads_num];    
    
    printf("Checking crash status\n");
    if ( isCrashed() ) {
        printf("I need to recover!\n");
        // Recover aggregate data structure
        
     recover_init_list();
     printf("****\n");
       
    }
    else{    
        printf("Program did not crash before, continue normal execution.\n");

        // Assign magic numbers and character to the aggregate data structure
        //struct foo *f = (struct foo*)nvmalloc(sizeof(struct foo), (char*)"f");

        list = init_list();

        wrappercreate(list);
        wrappercreate(list);
        wrappercreate(list);
        wrappercreate(list);
        wrappercreate(list);

        //for (int i = 0; i < threads_num; i++)
    
        printf("*******************finish init writing to values\n");                
       
        int i;
        for (i = 0; i < threads_num; i++) {
            struct thread_data *tmp = (struct thread_data*)malloc(sizeof(struct thread_data));
            tmp->tid = i;
            //tmp->local_data = f;
            pthread_create(&tid[i], NULL, t, (void*)tmp);
        }

        for (i = 0; i < threads_num; i++) {
            pthread_join(tid[i], NULL);
        }

     

        // Crash the program
        printf("internally abort!\n");
        abort(); 
    }

    printf("-------------main exits-------------------\n");
    return 0;
}


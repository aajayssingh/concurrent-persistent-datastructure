

#include <stdio.h>
#include "linkedlist.h"

#define num_threads 10
pthread_mutex_t gm; //to fix order of write to nvmalloc recovermap

list_t *list;

struct thread_data {
    int tid;
    list_t *local_data;
};

#ifdef SINGLE_THREAD
void *t(void *args)
{ 
    nvcheckpoint();
    pthread_exit(NULL);
}
#else
void *t(void *args)
{ 
    struct thread_data *data = (struct thread_data*)args;
    int tid = data->tid;
    list_t *tmp = data->local_data;

   // pthread_mutex_lock(&gm);
    bool res = add(list, (tid + 1), (tid + 100)); //key 0 reserved for head node    

    if(tid == 4)
    {
       bool res = add(list, 5, 1000);
    }

    if(tid == 1)
    {
      val_t v;
      if(find(list, tid +1, &v))
        printf("found key %d with val = %d \n", tid+1, v);
      remove(list, tid+1, &v);

      printf("removed key: %d\n", tid+1);
      
      if(find(list, tid + 1, &v))
        printf("found key %d with val = %d \n", tid+1, v);
      else
        printf("not found key %d\n", tid+1);

    }

   // pthread_mutex_unlock(&gm);
 
    nvcheckpoint();//redundant check later
    free(args);
    pthread_exit(NULL);
}
#endif

int main (int argc, char **argv)
{
  key_t i;
  val_t g;
  pthread_mutex_init(&gm, NULL);

  #ifdef SINGLE_THREAD
  pthread_t tid1;
  #else
  pthread_t tid[num_threads];
  #endif
    
    
    printf("Checking crash status\n");
    if ( isCrashed() ) {
        printf("I need to recover!\n");
        
        void *ptr = malloc(sizeof(int));
        nvrecover(ptr, sizeof(int), (char *)"c", 0);
        printf("Recovered c = %d\n", *(int*)ptr);
        free(ptr);

//testing free
        // int *fr = (int *)nvmalloc(sizeof(int), (char *)"d");
        // *fr = 123;
        // printf("d: %d\n", *fr);
        // free(fr);


        list = recover_init_list();
        printf("Recovered list...\n");

        printf("list->head->key: %d\n", list->head->key);
        printf("list->head->next->key: %d\n", list->head->next->key);

        sort_list(list);

        show_list (list);
    }
  #ifdef SINGLE_THREAD
    else
    {    
        printf("Program did not crash before, continue normal single thread execution.\n");
        
        pthread_create(&tid1, NULL, t, NULL);
      
        //pthread_mutex_lock(&gm);
        int *c = (int *)nvmalloc(sizeof(int), (char *)"c");
        *c = 12345;
        printf("c: %d\n", *c);
       
        list = init_list();
        bool res = add(list, 1, 100);
        printf("added key 1- %d\n", res);

        res = add(list, 2, 101);
        printf("added key 2- %d\n", res);//add()

        show_list (list);

        val_t v;
        res = remove(list, 1, &v);
        printf("removed key 1- %d val = %d\n", res, v);
   //     free(c);
  //      c = NULL;
//        printf("c after free %d\n", *c);

      
        printf("finish writing to values\n");
        nvcheckpoint();

        pthread_join(tid1, NULL);
         
        show_list (list);

        printf("internally abort!\n");
        abort(); 
    }
  #else
    else{    
        printf("Program did not crash before, continue normal multi thread execution.\n");
              
        //pthread_mutex_lock(&gm);
        int *c = (int *)nvmalloc(sizeof(int), (char *)"c");
        *c = 12345;
        printf("c: %d\n", *c);
       
        list = init_list();

        int i;
        for (i = 0; i < num_threads; i++) 
        {
          struct thread_data *tmp = (struct thread_data*)malloc(sizeof(struct thread_data));
          tmp->tid = i;
          tmp->local_data = list;
          pthread_create(&tid[i], NULL, t, (void*)tmp);
        }

        
        printf("finish writing to values\n");
        nvcheckpoint();

        for (i = 0; i < num_threads; i++)
        {
          pthread_join(tid[i], NULL);
        }
        
        show_list (list);
        printf("internally abort! node count: %d\n", list->node_count);
        abort(); 
    } 
  #endif

    /*find(list, 1, &g);
    printf("found key 1 with val%d\n", g);*/
    printf("-------------main exits-------------------\n");

  return 0;
}
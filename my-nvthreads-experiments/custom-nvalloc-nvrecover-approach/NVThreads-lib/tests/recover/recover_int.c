/*
(c) Copyright [2017] Hewlett Packard Enterprise Development LP

This program is free software; you can redistribute it and/or modify it under 
the terms of the GNU General Public License, version 2 as published by the 
Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY 
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with 
this program; if not, write to the Free Software Foundation, Inc., 59 Temple 
Place, Suite 330, Boston, MA 02111-1307 USA
*/
// Auther: Terry Hsu
// Verify that aggregate data structures spanning multiple pages can be recovered by NVthreads
// Result: recovery works correctly

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "nvrecovery.h"

pthread_mutex_t gm;
#define touch_size 4096 * 3

struct node{
    int id;
    struct node *next;
};

struct list 
{
    int head_id;
    struct node *head; // pointer to the head of the list
} list_t;

void *t(void *args){        
    nvcheckpoint();
    pthread_exit(NULL);
}

int main(){
    pthread_mutex_init(&gm, NULL);
    pthread_t tid1;
    pthread_t tid2;
    
    
    printf("CHECKING CRASH STATUS...\n");
    if ( isCrashed() ) {
        printf("I NEED TO RECOVER!\n");
        
        void *ptr = malloc(sizeof(int));
        nvrecover(ptr, sizeof(int), (char *)"c");
        printf("RECOVERED c = %d WITH ADD %p\n", *(int*)ptr, (int*)ptr);
        free(ptr);

        //AJAY CODE BEGINS

        //recover first node
        // struct list *ptr_list_head = (struct list*)malloc(sizeof(struct list)/*, (char*)"z"*/);
        // nvrecover(ptr_list_head, sizeof(struct list), (char*)"z");
        // printf("Recovered ptr_list_head->head_id = %d\n", ptr_list_head->head_id);
        
        // printf("ptr_list_head: %p\n", ptr_list_head);

        // //check second node address
        // printf("ptr_list_head->head: %p\n", ptr_list_head->head);  

        // //going to derefernce the next node
        // if(ptr_list_head->head)
        // {
        //    printf("GONNA ACCESS NEXT NODE.\n");          
        //    printf("Recovered ptr_list_head->head not null = %d\n", (ptr_list_head->head)->id);
        // }
       
        //free(ptr);
    }
    else{    
        printf("PROGRAM DIDNOT CRASH BEFORE, CONTINUE NORMAL EXECUTION.\n");
       pthread_create(&tid1, NULL, t, NULL);
       //pthread_create(&tid2, NULL, t, NULL);
        
        pthread_mutex_lock(&gm);
        int *c = (int *)nvmalloc(sizeof(int), (char *)"c");
        *c = 12345;
        printf("c: %d ADD %p\n", *c, c);
       

       //AJAY code begins

       //  //nvmalloc first node
       //  struct list *nd = (struct list *)nvmalloc(sizeof(struct list), (char *)"z");
       //  nd->head_id = 99;
       
       //  //nvmalloc second node
       //  struct node *nd1 = (struct node *)nvmalloc(sizeof(struct node), (char *)"z"/*(char *)"w"*/);
       //  nd1->id = 999;
       //  nd1->next = NULL;

       //  //link both the nodes
       //  nd->head = nd1;
        
       //  //debug messages
       //  printf("addr nd: %p\n", nd);
       //  printf("addr nd1: %p\n", nd1);
       //  printf("&nd->head: %p\n", &(nd->head));
       //  printf("nd->head: %p\n", nd->head);  
       //  printf("nd->sentinel_id: %d\n", nd->head_id); 
       //  printf("nd->head->id: %d\n", nd->head->id);

       //  pthread_mutex_unlock(&gm);
        
        
       //  printf("FINISH WRITING TO VALUES\n");
       //  nvcheckpoint();

       // pthread_join(tid1, NULL);
       //pthread_join(tid2, NULL);
        printf("INTERNALLY ABORT!\n");
        abort(); 
    }

    printf("-------------MAIN EXITS-------------------\n");
    return 0;
}
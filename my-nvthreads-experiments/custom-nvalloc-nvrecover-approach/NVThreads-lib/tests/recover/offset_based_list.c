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
#define NODE_INFO_ARR_SIZE 3

struct node{
    int id;
    struct node *next;
    unsigned long nextNodeInfo[NODE_INFO_ARR_SIZE];
};

struct list 
{
    int head_id;
    struct node *next; // pointer to first node of the list
    unsigned long nextNodeInfo[NODE_INFO_ARR_SIZE];
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

      /*  ptr = malloc(sizeof(int));
        nvrecover(ptr, sizeof(int), (char *)"d");
        printf("RECOVERED d = %d WITH ADD %p\n", *(int*)ptr, (int*)ptr);
        free(ptr);*/


        //AJAY CODE BEGINS

        //recover list entry object
        struct list *l = (struct list*)malloc(sizeof(struct list)/*, (char*)"z"*/);
        nvrecover(l, sizeof(struct list), (char*)"z");
        printf("Recovered l->head_id = %d\n", l->head_id);
        
        printf("list entry object address, l: %p\n", l);

        //recover first node with custom recover
//         unsigned long my_custom_nvrecover(void *dest, unsigned long pageNo, unsigned long pageOffset, size_t size);
        struct node *nd = (struct node*)malloc(sizeof(struct node)/*, (char*)"z"*/);
        printf("sizeof node: %d, size in l->nextNodeInfo[2]: %d\n",sizeof(struct node), l->nextNodeInfo[2]);
        my_custom_nvrecover(nd, l->nextNodeInfo[0], l->nextNodeInfo[1], l->nextNodeInfo[2]);

        printf("nd->id: %d\n", nd->id);  

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

        //pthread_mutex_lock(&gm);
       /* int *d = (int *)nvmalloc(sizeof(int), (char *)"d");
        *d = 9999;
        printf("d: %d ADD %p\n", *d, d);
*/

       //AJAY code begins

        //nvmalloc list entry object
        struct list *l = (struct list *)nvmalloc(sizeof(struct list), (char *)"z");
        l->head_id = 99;

        unsigned long *nextNodeInfo = (unsigned long *)malloc(NODE_INFO_ARR_SIZE*sizeof(unsigned long)); 
       
        //nvmalloc first node
        struct node *nd1 = (struct node *)my_custom_nvmalloc(sizeof(struct node), (char *)"z", true, nextNodeInfo);
        nd1->id = 999;
        nd1->next = NULL;

        //link both the nodes
        l->next = nd1;
        l->nextNodeInfo[0] = nextNodeInfo[0];
        l->nextNodeInfo[1] = nextNodeInfo[1];
        l->nextNodeInfo[2] = nextNodeInfo[2];

        //free the temp array
        free(nextNodeInfo);
        
        //debug messages
        printf("addr l: %p\n", l);
        printf("addr nd1: %p\n", nd1);
        printf("l->next: %p\n", l->next);  
        printf("l->head_id: %d\n", l->head_id); 
        printf("l->next->id: %d\n", l->next->id);
//*******************************************************
        printf("pageNo, l->nextNodeInfo[0]: %zu\n", l->nextNodeInfo[0]);
        printf("pageOffset, l->nextNodeInfo[1]: %zu\n", l->nextNodeInfo[1]);
        printf("size, l->nextNodeInfo[2]: %zu\n", l->nextNodeInfo[2]);



         pthread_mutex_unlock(&gm);
        
        
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
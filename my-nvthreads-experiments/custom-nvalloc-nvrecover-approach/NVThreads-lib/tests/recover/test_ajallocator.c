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
#include "ajmalloc.h"

pthread_mutex_t gm;
#define touch_size 4096 * 3

typedef struct node
{
    uint8_t id;
    unsigned int offset;
    struct node *next;
}node_t;


void *t(void *args){        
    nvcheckpoint();
    pthread_exit(NULL);
}

int main(){
    pthread_mutex_init(&gm, NULL);
    pthread_t tid1;
    
    
    printf("Checking crash status\n");
    if ( isCrashed() ) {
        printf("I need to recover!\n");
        void *ptr = malloc(sizeof(int));
        nvrecover(ptr, sizeof(int), (char *)"c");
        printf("Recovered c = %d\n", *(int*)ptr);
        free(ptr);
        ptr = malloc(sizeof(int));
        nvrecover(ptr, sizeof(int), (char*)"d");
        printf("Recovered d = %d\n", *(int*)ptr);
        free(ptr);
        ptr = malloc(sizeof(int));
        nvrecover(ptr, sizeof(int), (char*)"e");
        printf("Recovered e = %d\n", *(int*)ptr);
        free(ptr);

        void *offset = malloc(sizeof(int));
        nvrecover(offset, sizeof(int), (char*)"ptm");
        printf("Recovered ptm offset = %d\n", *(int*)offset);
        //free(ptr);

//offset of list head, base ass of the list on which rest of the nodes would be recovered
        void *offset_list = malloc(sizeof(int));
        nvrecover(offset_list, sizeof(int), (char*)"ptho");
        printf("Recovered ptho offset = %d\n", *(int*)offset_list); 
        //free(ptr);

        void *ptr1 = malloc(touch_size);
        nvrecover(ptr1, touch_size, (char*)"l");
        //printf("Recovered l = %x, next: %x, val: %d\n", ptr1, ptr1 +4, *((int*)(ptr1 + 4)));

        printf("Recovered l = %x, next: %x, val: %d\n", ptr1, ptr1 + (*(int*)offset), *((int*)(ptr1 + (*(int*)offset))));
       
        printf("*********************************************\n");

        printf("Recovered l-head = %x, next: %x, val: %d\n", ptr1, ptr1 + (*(int*)offset_list), ((node_t*)(ptr1 + (*(int*)offset_list)))->id);       

        printf("*********************************************\n");
        int head_offset = ((node_t*)(ptr1 + (*(int*)offset_list)))->offset;

        printf("Recovered l-head-next = %x, next: %x, val: %d\n", ptr1, ptr1 + head_offset, ((node_t*)(ptr1 + head_offset))->id);




    }
    else{    
        printf("Program did not crash before, continue normal execution.\n");
        pthread_create(&tid1, NULL, t, NULL);

        int *c = (int *)nvmalloc(sizeof(int), (char *)"c");
        *c = 12345;
        printf("c: %d\n", *c);
        int *d = (int *)nvmalloc(sizeof(int), (char *)"d");
        *d = 56789;
        printf("d: %d\n", *d);
        int *e = (int *)nvmalloc(sizeof(int), (char *)"e");
        *e = 99999;
        printf("e: %d\n", *e);
//***************************************************************************
printf("*********************************************\n");

        char *l = (char *)nvmalloc(touch_size, (char *)"l");
        my_init(l, touch_size); //memory init.

        int *my_int = (int*)my_alloc(sizeof(int));
        *my_int = 54321;
        printf("my_int: %d\n", *my_int);

        int *ptr_to_my = ( int *)nvmalloc(sizeof( int), (char *)"ptm");
        *ptr_to_my = (uintptr_t)my_int - (uintptr_t)l; //store the offset of the myalloced int
        printf("*ptr_to_my: %d\n", *ptr_to_my);
        
        printf("l: %x my_int: %x, ptr_to_my: %x \n", /*(unsigned int)*/l, my_int, ptr_to_my);
        printf("l next addr: %x, val of next l: %d\n", l + 4, *((int*)(l+4)));

        printf("*********************************************\n");

//***************************************************************************

        printf("sizeof(node), %d", sizeof(node_t));
        node_t *head = (node_t*)my_alloc(sizeof(node_t));
        head->id = 1;

        printf("head->id: %d\n", head->id);

        int *ptr_to_headoff = ( int *)nvmalloc(sizeof( int), (char *)"ptho");
        *ptr_to_headoff = (uintptr_t)head - (uintptr_t)l; //store the offset of the myalloced int
        printf("*ptr_to_headoff: %d\n", *ptr_to_headoff);
        
        printf("l: %x head: %x, ptr_to_headoff: %x \n", /*(unsigned int)*/l, head, ptr_to_headoff);
       // printf("l next addr: %x, val of next l: %d\n", l + 4, *((int*)(l+4)));

        printf("*********************************************\n");

        node_t *node1 = (node_t*)my_alloc(sizeof(node_t));
        node1->id = 2;
        int node_offset  = (uintptr_t)node1 - (uintptr_t)l;
        printf("node_offset: %d\n", node_offset);
        head->offset = node_offset;


        printf("*********************************************\n");





        printf("finish writing to values\n");
        nvcheckpoint();

        pthread_join(tid1, NULL);
        printf("internally abort!\n");
        abort(); 
    }

    printf("-------------main exits-------------------\n");
    return 0;
}

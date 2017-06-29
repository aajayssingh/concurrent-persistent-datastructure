/* ---------------------------------------------------------------------------
 * Coarse-Grained Singly-linked List

 * ---------------------------------------------------------------------------
 */
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
#include <assert.h>


#include "common.h"
#include "nvrecovery.h"
//#define _SINGLE_THREAD_

//pthread_mutex_t gm;

typedef struct _node //the name _node is not meant to be used outside the file
{
  key_t key;            /* key */
  val_t val;             /* value  */
  bool marked;
  struct _node *next;  /* pointer to the next node */
} node_t;

typedef struct _list
{
  int node_count;
  node_t *head;
  node_t *tail;
  pthread_mutex_t gmtx;  
} list_t;


bool add (list_t *, const key_t, const val_t);
bool remove (list_t *, const key_t, val_t *);
bool find (list_t *, const key_t, val_t *);
list_t * init_list (void);
list_t * recover_init_list (void);

void free_list (list_t *);
void show_list(const list_t *);
void sort_list(const list_t *);

#endif

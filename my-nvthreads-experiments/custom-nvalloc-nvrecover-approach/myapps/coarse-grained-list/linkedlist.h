/* ---------------------------------------------------------------------------
 * Coarse-Grained Singly-linked List

 * ---------------------------------------------------------------------------
 */
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "common.h"
#include "nvrecovery.h"

#define NODE_INFO_ARR_SIZE 3
#define VAL_MIN  0  //id of head node(sentinel node)
#define VAL_MAX  100 //id of tail node(sentinel node)

typedef struct _node //the name _node is not meant to be used outside the file
{
  //recovery info to be used while recovery of each node with correct address
  //during custom nvmalloc this array will be populated.
  unsigned long nextNodeInfo[NODE_INFO_ARR_SIZE]; /* has to be unsigned long as lib APIs use same type*/
  unsigned long selfNodeInfo[NODE_INFO_ARR_SIZE]; /*used during malloc to link newly created node*/

   key_t key;            /* key */
  val_t val;             /* value  */
  bool marked;
  struct _node *next;  /* pointer to the next node, to be used during normal list operations for efficency */

} node_t;

typedef struct _list
{
  int node_count; //needed to know how many nodes to be recovered, during recovery. 

  node_t *head;
  unsigned long headNodeInfo[NODE_INFO_ARR_SIZE];//used during recovery
  node_t *tail;
  unsigned long tailNodeInfo[NODE_INFO_ARR_SIZE];//used during recovery

  pthread_mutex_t gmtx; /*list global mutex for coarse grained list.*/  
} list_t;
//pthread_mutex_t gm;

bool add (list_t *, const key_t, const val_t);
bool remove (list_t *, const key_t, val_t *);
bool find (list_t *, const key_t, val_t *);
list_t * init_list (void);
list_t * recover_init_list (void);

void free_list (list_t *);
void show_list(const list_t *l);
void show_list_with_offsets(const list_t *l);

void sort_list(const list_t *);
void printNodeInfo(node_t * node);

#endif

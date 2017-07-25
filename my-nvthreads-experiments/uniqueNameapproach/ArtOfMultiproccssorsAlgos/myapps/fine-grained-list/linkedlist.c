/*!
 * AUTHOR:      Ajay Singh, IIT Hyderabad
 
 * ORGANIZATION:  LIP6 - INRIA&UPMC.
 * DATE:      Jul 25, 2017.
 */
#include <algorithm>
#include "linkedlist.h"
int *a,*b,*c,*d;
static node_t *create_node(const key_t, const val_t, list_t *list);

/*
 * success : return pointer of this node
 * failure : return NULL
 */
static node_t *create_node(const key_t key, const val_t val, list_t *list)
{
  node_t *node;

  //if intermediate node has prohivted key val
  if(((key == VAL_MAX) || (key == VAL_MIN)) && (list->node_count >= 2))
  {
    printf("Please adhere to sentinel node value invariants\n");
    return NULL;
  }

  char *name = (char *)malloc(NODE_INFO_ARR_SIZE*sizeof(char)); 
  memset(name, '\0', sizeof(NODE_INFO_ARR_SIZE*sizeof(char)));   

  if(list->node_count == 0)
  {
    sprintf(name, "head");
    list->node_count++;
    list->real_node_count++;
  }
  else if(list->node_count == 1)
  {
    sprintf(name, "tail");
    list->node_count++;
    list->real_node_count++;
  }
  else
  {
    sprintf(name, "n-%d", list->node_count++);
    list->real_node_count++;
  }
   

  node = (node_t *)nvmalloc(sizeof(node_t), name);
  memset(node, 0, sizeof(node_t));
 // printf("created node\n");  
  if (node == NULL) {
    elog("create_node | nvmalloc error");
    return NULL;
  }

  // node fields
  node->key = key;
  node->val = val;
  node->marked = false;
  //init node mutex lock 
  pthread_mutex_init(&(node->node_mtx), NULL);
 // printf("&(node->node_mtx) : %p\n", &(node->node_mtx));
  
  //init node info of its location in memory
  memset(node->nvnext.selfNodeName, '\0', sizeof(char)*NODE_INFO_ARR_SIZE);
  strcpy(node->nvnext.selfNodeName, name);
 /* for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
  {
//    node->nvnext.selfNodeName[i] = name[i];
      node->nvnext.nextNodeName[i] = '\0';  
  }*/
  memset(node->nvnext.nextNodeName, '\0', sizeof(char)*NODE_INFO_ARR_SIZE);
  node->next = NULL;

  //printf("%s\n", node->selfNodeName);

  //free the temp array
  free(name); 
  return node;
}

/*updates the links of first node to point to second node
1) nextNodeName
2) next field
both are updated to point to the second node.
Meant to be atomically executed.
*/
void updateLinks(node_t* first, node_t* second)
{
//  size_t destination_size = sizeof (first->nvnext.nextNodeName);

  memset(first->nvnext.nextNodeName, '\0', sizeof(char)*NODE_INFO_ARR_SIZE );
  strcpy(first->nvnext.nextNodeName, second->nvnext.selfNodeName);
  //first->nvnext.nextNodeName[destination_size - 1] = '\0';

/*  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
  {
      first->nvnext.nextNodeName[i] = second->nvnext.selfNodeName[i];
  }*/
  first->next = second;
}


/*
 * success : return true
 * failure(key already exists) : return false
 */
bool add(list_t * list, const key_t key, const val_t val)
{
//  pthread_mutex_lock(&(list->gmtx));
  
  node_t *pred, *curr;
  node_t *newNode;
  bool ret = true;
  #ifdef DBG
  printf("add | enter add [%d, %d]\n", key, val);
  #endif
     
  #ifdef DBG
  printf("add [%d, %d]\n", key, val);
  #endif

  pthread_mutex_lock(&(list->head->node_mtx));//lock head
  pred = list->head;
  curr = pred->next;
  pthread_mutex_lock(&(curr->node_mtx));//lock curr
  
    while (curr->key < key)
    {
      pthread_mutex_unlock(&(pred->node_mtx));
      pred = curr;
      curr = curr->next;
      pthread_mutex_lock(&(curr->node_mtx));
    }
    
    if (key == curr->key)//node found between sentinels
    {
     //#ifdef DBG
      printf("NODE already PRESENT with key = %d - node not created\n", key);
      //#endif
      ret = false;
      //list->node_count = list->node_count + 1;
    }
    else
    {
      if ((newNode = create_node(key, val, list)) == NULL) //creating nodes atomically solves the problem of 
      {
        printf("node could not be created\n");
        abort();
      }
printf("abcd---\n");
  if(key == 1)
  {
  a = (int *)nvmalloc(sizeof(int), (char*)"a");
  *a  = 1231;
  printf("add a\n");
  }
  if(key == 2)
  {
  b = (int *)nvmalloc(sizeof(int), (char*)"b");
  *b  = 1232;
    printf("add b\n");
  }
  if(key == 3)
  {
   c = (int *)nvmalloc(sizeof(int), (char*)"c");
  *c  = 1233;
    printf("add c\n");
  }
  if(key == 4){
   d = (int *)nvmalloc(sizeof(int), (char*)"d");
  *d  = 1234;
    printf("add d\n");
  }

      updateLinks(newNode, curr); //newNode->next = curr;
      updateLinks(pred, newNode); //pred->next = newNode;

     /* if(strcmp(pred->nvnext.nextNodeName, list->tailNodeName) != 0)
      {
        newNode->nvnext.nextNodeName[3] = '\0';
        printf("forcing null for key:%d , %s - %s\n", newNode->key, pred->nvnext.nextNodeName, list->tailNodeName);
      }*/
      ret = true;
      //list->node_count = list->node_count + 1;
    }
  
  if(ret)
    printf("add [%d, %d], pred:%s, %s, newNode:%s, %s, curr: %s\n", key, val, pred->nvnext.selfNodeName, pred->nvnext.nextNodeName, newNode->nvnext.selfNodeName, newNode->nvnext.nextNodeName, curr->nvnext.selfNodeName);

  // pthread_mutex_unlock(&(list->gmtx));
  //nvcheckpoint(); //exploring reason of unrecovered val
  
  pthread_mutex_unlock(&(curr->node_mtx));
  pthread_mutex_unlock(&(pred->node_mtx));
  nvcheckpoint();
  return ret;
}

/*
 * success : return true
 * failure(not found) : return false
 make sure keys lies in range
 */
bool del(list_t * list, const key_t key, val_t *val)
{
 // pthread_mutex_lock(&(list->gmtx));
  node_t *pred, *curr;
  bool ret = true;
  
  pthread_mutex_lock(&(list->head->node_mtx));//lock head
  pred = list->head;
  curr = pred->next;
  pthread_mutex_lock(&(curr->node_mtx));//lock curr
  
  while (curr->key < key) /*traverse correct location*/
  {
    pthread_mutex_unlock(&(pred->node_mtx));
    pred = curr;
    curr = curr->next;
    pthread_mutex_lock(&(curr->node_mtx));
  }

  if (key == curr->key)
  {
    *val = curr->val;      
    //update links
    updateLinks(pred, curr->next);
    
    curr->key = -1;
    curr->val = -1;
    curr->marked = true;
    curr->next = NULL;

    list->real_node_count = list->real_node_count - 1;
    
    free(curr);
    ret = true;
  }
  else
  {
    ret = false;
  }
  
  nvcheckpoint();
  printf("delete [%d, %d] res: %d\n", key, (ret)?(*val):(-1), ret);

  pthread_mutex_unlock(&(curr->node_mtx));
  pthread_mutex_unlock(&(pred->node_mtx));
  return ret;
}

/*
 * success : return true
 * failure(not found) : return false
 */
bool find(list_t * list, const key_t key, val_t *val)
{
  node_t *pred, *curr;
  bool ret = true;
  
  pthread_mutex_lock(&(list->gmtx));
  
  pred = list->head;
  curr = pred->next;
  
  if (curr == list->tail) 
  {
    ret = false;
  }
  else
  {
    while (curr != list->tail && curr->key < key)
    {
      pred = curr;
      curr = curr->next;
    }
    if (curr != list->tail && key == curr->key)
    {
      *val = curr->val;
      ret = true;
    }
    else
      ret = false;
  }
   printf("find [%d, %d] res: %d\n", key, (ret)?(*val):(-1), ret);
  pthread_mutex_unlock(&(list->gmtx));
  return ret;
}

/*
 * success : return pointer to the initial list to be executed before spawning threads
 * failure : return NULL
 */
list_t *init_list(void)
{
  list_t *list;
 
  //malloc entry object with library nvmalloc to recover it using lib recovery mechanism
  list = (list_t *)nvmalloc(sizeof(list_t), (char *)"z");
  memset(list, 0, sizeof(list_t));
  if (list == NULL) {
    elog("nvmalloc error");
    return NULL;
  }
  list->node_count = 0;//used to uniquely name the nodes
  list->real_node_count = 0;  //maintains correct count of nodes as nodes can be delted as well.
  
  //init sentinel nodes
  list->head = create_node(VAL_MIN, VAL_MIN, list);
  if (list->head == NULL) {
    elog("nvmalloc error");
    goto end;
  }
  strcpy(list->headNodeName, list->head->nvnext.selfNodeName);

  list->tail = create_node(VAL_MAX, VAL_MAX, list);
  if (list->tail == NULL) {
    elog("nvmalloc error");
    goto end;
  }
strcpy(list->tailNodeName, list->tail->nvnext.selfNodeName);
   
  updateLinks(list->head, list->tail);

  //init global list mutex lock 
  pthread_mutex_init(&(list->gmtx), NULL);
  //printf("list->gmtx init: %p\n", &(list->gmtx));

  printf("list inited\n");
  printNodeInfo(list->head);
  printNodeInfo(list->tail);
 
  return list;
  
 end:
  free(list->head);
  free(list);
  return NULL;
}

void printNodeInfo(node_t * node)
{
  #if DETAIL_DBG
  printf("\t*****NODEINFO\n");
  printf("node->key: %d, node->val: %d, node: %p, node->next: %p\n", node->key, node->val, node, node->next);
  printf("node->nvnext.selfNodeName: %s\n", node->nvnext.selfNodeName);
  printf("node->nvnext.nextNodeName: %s\n\n", node->nvnext.nextNodeName);
  #endif
}


/*
 * success : return pointer to the initial list
 * failure : return NULL
 */
list_t * recover_init_list (void)
{
  list_t *list;
  
  list = (list_t*)malloc(sizeof(list_t));
   memset(list, 0, sizeof(list_t));
  
  nvrecover(list, sizeof(list_t), (char*)"z");
  printf("Recovered list & node_count: %d, real_node_count: %d\n", list->node_count, list->real_node_count);
  pthread_mutex_init(&(list->gmtx), NULL);

  printf("recovering head...\n");
  node_t *head = (node_t *)malloc(sizeof(node_t));
  nvrecover(head, sizeof(node_t), (char*)"head");
  list->head = head;
  printNodeInfo(list->head);

  printf("recovering tail...\n");
  node_t *tail = (node_t *)malloc(sizeof(node_t));
  nvrecover(tail, sizeof(node_t), (char*)"tail");
  list->tail = tail;
  printNodeInfo(list->tail); 

  node_t *pred, *curr;
  pred = list->head;

  int node_index = 0;
  while ((++node_index) <= (list->real_node_count - 2))
  {    
   // #if DETAIL_DBG
    printf("recovering node: %s, index:%d\n", pred->nvnext.nextNodeName, node_index);
    //#endif
    node_t *curr = (node_t *)malloc(sizeof(node_t));
     memset(curr, 0, sizeof(node_t));
    nvrecover(curr, sizeof(node_t), pred->nvnext.nextNodeName);
    printNodeInfo(curr);//here next field is garbage

    updateLinks(pred, curr); //reconstructing the next field
    pred = curr;
  } 
  updateLinks(pred, tail);

  printf("recover_init_list | full list recovered :) :)\n");

//int *a,*b,*c,*d;
  int *ptr = (int*)malloc(sizeof(int));

  nvrecover(ptr, sizeof(int), (char*)"a");
  printf("Recovered a = %d\n", *(int*)ptr);
        free(ptr);
  nvrecover(ptr, sizeof(int), (char*)"b");
  printf("Recovered b = %d\n", *(int*)ptr);
        free(ptr);
  nvrecover(ptr, sizeof(int), (char*)"c");
  printf("Recovered c = %d\n", *(int*)ptr);
        free(ptr);
  nvrecover(ptr, sizeof(int), (char*)"d");
  printf("Recovered d = %d\n", *(int*)ptr);
        free(ptr);

 //printf("%d,%d,%d,%d\n",*a,*b,*c,*d);
  return list;
}
#if 0
/*
 * void free_list(list_t * list)
 */
void free_list(list_t * list)
{
  node_t *curr, *next;

  curr = list->head->next;

  while (curr != list->tail) {
    next = curr->next;
    free_node (curr);
    curr = next;
  }

  free_node(list->head);
  free_node(list->tail);
  //pthread_mutex_destroy(&list->mtx);
  free(list);
}
#endif
/*
 * void show_list(const list_t * l)
 */
void show_list(const list_t * l)
{
    node_t *pred, *curr;

    pred = l->head;
    curr = pred->next;

//    printNodeInfo(pred);

    printf ("list:\n\n");
    printf(" -->[%ld:%ld]: %p\n", (long int) pred->key, (long int)pred->val, pred);
    while (curr != l->tail)
    {
      if(curr->key == 0 && curr->val == 0)
        printf("----->");
      printf(" -->[%ld:%ld]: %p\n", (long int) curr->key, (long int)curr->val, curr);

      pred = curr;
      curr = curr->next;
    }
    printf(" -->[%ld:%ld]: %p\n", (long int) curr->key, (long int)curr->val, curr);
    printf("\n");
/**************************************************************************************/
#if 0//DETAIL_DBG
    printf("detailed list\n");
    pred = l->head;
    curr = pred->next;

//    printNodeInfo(pred);

    printNodeInfo(pred);
    while (curr != l->tail) {
      printNodeInfo(curr);
      pred = curr;
      curr = curr->next;
    }
    printNodeInfo(curr);
    printf("\n");
#endif

}

/*
 * void show_list(const list_t * l)
 */
void show_list_with_offsets(const list_t * l)
{
    node_t *pred, *curr;

    pred = l->head;
    curr = pred->next;

    printf ("list:\n\n");
    printf(" -->[%ld:%ld]: %s %s\n", (long int) pred->key, (long int)pred->val, pred->nvnext.selfNodeName, pred->nvnext.nextNodeName);
    int node_index = 0;

    while ((curr != l->tail)&&(++node_index < l->real_node_count - 1)) {
      printf(" -->curr[%ld:%ld]: pred:%s %s :: curr:%s %s      ->%d\n", (long int) curr->key, (long int)curr->val, pred->nvnext.selfNodeName, pred->nvnext.nextNodeName, curr->nvnext.selfNodeName, curr->nvnext.nextNodeName, node_index);
      /*for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
      {
        printf(" %c",curr->nvnext.nextNodeName[i]);
        //curr->nvnext.nextNodeName[3] = '\0';
      }*/

    if(curr->key == 0 && curr->val == 0)
      printf("----->");
    if(strcmp(pred->nvnext.nextNodeName, curr->nvnext.selfNodeName) != 0)
      printf("***blunder next pointer and offsets not synchronized***");

      pred = curr;
      curr = curr->next;
    }
    printf(" -->[%ld:%ld]: %s %s\n", (long int) curr->key, (long int)curr->val, curr->nvnext.selfNodeName, curr->nvnext.nextNodeName);
    printf("****************----%d----******************************************\n", l->real_node_count);
 printf("a: %d, %d, %d, %d\n", *(int*)a, *b, *c, *d);
}

/* ---------------------------------------------------------------------------
ISSUES: I get map error: 0xffffffffffff if try to free a node.
 * ---------------------------------------------------------------------------
 */
#include <algorithm>
#include "linkedlist.h"

// #define lock(mtx) pthread_mutex_lock(&(mtx))
// #define unlock(mtx) pthread_mutex_unlock(&(mtx))
// #ifdef _FREE_
// #define free_node(node) free(node)
// #else
#define free_node(node) free(node);
//#endif

static node_t *create_node(const key_t, const val_t);

/*
 * success : return pointer of this node
 * failure : return NULL
 */
static node_t *create_node(const key_t key, const val_t val)
{
  node_t *node;

  unsigned long *selfNodeInfo = (unsigned long *)malloc(NODE_INFO_ARR_SIZE*sizeof(unsigned long)); 
  memset(selfNodeInfo, 0, sizeof(NODE_INFO_ARR_SIZE*sizeof(unsigned long)));   
 // printf("gonna create node\n");
  //nvmalloc first node
  node = (node_t *)my_custom_nvmalloc(sizeof(node_t), (char *)"z", true, selfNodeInfo);
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
  node->next = NULL;

  //init node info of its location in memory
  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
  {
    node->selfNodeInfo[i] = selfNodeInfo[i];
    node->nextNodeInfo[i] = 0;  
  }

  //free the temp array
  free(selfNodeInfo);
 
  return node;
}

/*updates the links of first node to point to second node
1) nextNodeInfo
2) next field
both are updated to point to the second node.
Meant to be atomically executed.
*/
void updateLinks(node_t* first, node_t* second)
{
  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
  {
      first->nextNodeInfo[i] = second->selfNodeInfo[i];
  }
  first->next = second;
}
/*
 * success : return true
 * failure(key already exists) : return false
 */
bool add(list_t * list, const key_t key, const val_t val)
{
  node_t *pred, *curr;
  node_t *newNode;
  bool ret = true;
  #ifdef DBG
  printf("add | enter add [%d, %d]\n", key, val);
  #endif

 /* if ((newNode = create_node(key, val)) == NULL)
    return false;*/
  
  pthread_mutex_lock(&(list->gmtx));
   
  //#ifdef DBG
  printf("add [%d, %d]\n", key, val);
  // #endif
  pred = list->head;
  curr = pred->next;
  
  if (curr == list->tail)
  {
    if ((newNode = create_node(key, val)) == NULL) //creating nodes atomically solves the problem of negative values for the nodes.
    abort();

    updateLinks(list->head, newNode);//list->head->next = newNode;
    updateLinks(newNode, list->tail);//newNode->next = list->tail;
    list->node_count++;
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
      //free_node(newNode); /free causes map error
      // newNode->key = -1;
      // newNode->val = -1;
      //#ifdef DBG
      printf("NODE already PRESENT with key = %d - node not created\n", key);
      //#endif
      ret = false;
      //list->node_count = list->node_count + 1;
    }
    else
    {
      if ((newNode = create_node(key, val)) == NULL) //creating nodes atomically solves the problem of 
        abort();

      updateLinks(newNode, curr); //newNode->next = curr;
      updateLinks(pred, newNode); //pred->next = newNode;

      list->node_count = list->node_count + 1;
    }
  }
  
  pthread_mutex_unlock(&(list->gmtx));
#ifdef DBG
  printf("add | exit add [%d, %d] and node_count- %d \n", key, val, list->node_count);
#endif
  return ret;
}

/*
 * success : return true
 * failure(not found) : return false
 */
bool remove(list_t * list, const key_t key, val_t *val)
{
  node_t *pred, *curr;
  bool ret = true;
  
  pthread_mutex_lock(&(list->gmtx));

  pred = list->head;
  curr = pred->next;
  
  if (curr == list->tail) /*list empty*/ 
  {
    ret = false;
    printf("pal! cannot remove anymore the list has only head & tail :(\n");
  }
  else
  {
    while (curr->key < key && curr != list->tail) /*traverse correct location*/
    {
      pred = curr;
      curr = curr->next;
    }


    if (key == curr->key)
    {
      *val = curr->val;
      
      //update links
      updateLinks(pred, curr->next);
      //pred->next = curr->next;
     // free_node(curr); //node free causes maperr 0xffffffff!
      //curr = NULL;
      curr->key = -1;
      curr->val = -1;
      list->node_count = list->node_count - 1;
      ret = true;

      //printf("freed the node key: %d\n", key);
      //#ifdef DBG
      //printf("freed node data, key: %d, value: %d", curr->key, curr->val);
      //printf("delete [%d, %d]\n", key, val);
      //#endif
//      printf("delete [%d, %d]\n", key, val);
    }
    else
      ret = false;
  }
  printf("delete [%d, %d] res: %d\n", key, (ret)?(*val):(-1), ret);
  pthread_mutex_unlock(&(list->gmtx));
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

  if (list == NULL) {
    elog("nvmalloc error");
    return NULL;
  }
  
  
  //init sentinel nodes
  list->head = create_node(VAL_MIN, VAL_MIN);//(node_t *)nvmalloc(sizeof(node_t), (char *)"h");  
  if (list->head == NULL) {
    elog("nvmalloc error");
    goto end;
  }
  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++) //used during recovery of head node
  {
    list->headNodeInfo[i] = list->head->selfNodeInfo[i];
  }
  

  list->tail = create_node(VAL_MAX, VAL_MAX);;//(node_t *)nvmalloc(sizeof(node_t), (char *)"t");
  if (list->tail == NULL) {
    elog("nvmalloc error");
    goto end;
  }
  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
  {
    list->tailNodeInfo[i] = list->tail->selfNodeInfo[i];
  }
  
  updateLinks(list->head, list->tail);// list->head->next = list->tail;
  
  list->node_count = 2;
//  list->mtx = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

  //init global list mutex lock 
  pthread_mutex_init(&(list->gmtx), NULL);

  printf("list init\n");
  printf("list->headNodeInfo[1]: %d, %p\n",  list->headNodeInfo[1], list->head);
  printf("list->tailNodeInfo[1]: %d, %p\n",  list->tailNodeInfo[1], list->tail);


  
  return list;
  
 end:
  free(list->head);
  free(list);
  return NULL;
}

void printNodeInfo(node_t * node)
{
  printf("node->key: %d, node->val: %d, node: %p, node->next: %p\n", node->key, node->val, node, node->next);
  printf("node->selfNodeInfo: %d, %d, %d\n", node->selfNodeInfo[0], node->selfNodeInfo[1], node->selfNodeInfo[2]);
  printf("node->nextNodeInfo: %d, %d, %d\n", node->nextNodeInfo[0], node->nextNodeInfo[1], node->nextNodeInfo[2]);
}

/*
 * success : return pointer to the initial list
 * failure : return NULL
 */
list_t * recover_init_list (void)
{
  list_t *list;
  
  list = (list_t*)malloc(sizeof(list_t));
  
  nvrecover(list, sizeof(list_t), (char*)"z");
  printf("Recovered list & node_count = %d\n", list->node_count);
  pthread_mutex_init(&(list->gmtx), NULL);

  //printf("list->head: %p\n", list->head);  
  //printf("list->tail: %p\n", list->tail);

 // printf("recovering head & tail...\n");

  node_t *head = (node_t *)malloc(sizeof(node_t));
  //nvrecover(head, sizeof(node_t), (char*)"z", node_index);
  my_custom_nvrecover(head, list->headNodeInfo[0], list->headNodeInfo[1], list->headNodeInfo[2]/*sizeof(node_t)*/);
  list->head = head;
  printf(" recovered head[%lu:%ld], %d, %d, %p\n", (unsigned long int) head->key, (long int)head->val, list->headNodeInfo[0], list->headNodeInfo[1], list->head);

  //node_index++;
  node_t *tail = (node_t *)malloc(sizeof(node_t));
  my_custom_nvrecover(tail, list->tailNodeInfo[0], list->tailNodeInfo[1], list->tailNodeInfo[2]/*sizeof(node_t)*/);
  list->tail = tail;
  printf(" recovered tail[%lu:%ld], %d, %d, %p\n", (unsigned long int) tail->key, (long int)tail->val, list->tailNodeInfo[0], list->tailNodeInfo[1], list->tail); 

  node_t *pred, *curr;
  pred = list->head;

  int node_index = 0;
  while ((++node_index) <= (list->node_count -2 )) //skiping the tail node 
  {    
    
    printf("pred: %p, %d, %d, %d  & prednextInfo: %d, %d\n\n",pred, pred->selfNodeInfo[0], pred->selfNodeInfo[1], pred->key, pred->nextNodeInfo[0], pred->nextNodeInfo[1]);

    node_t *curr = (node_t *)malloc(sizeof(node_t));
    my_custom_nvrecover(curr, pred->nextNodeInfo[0], pred->nextNodeInfo[1], pred->nextNodeInfo[2]);
    
    printf(" recovered [%ld:%ld], node_index: %d\n", (unsigned long int) curr->key, (long int)curr->val, node_index);

printf("curr: %p, %d, %d, %d  & nextInfo: %d, %d\n\n",curr, curr->selfNodeInfo[0], curr->selfNodeInfo[1], curr->key, curr->nextNodeInfo[0], curr->nextNodeInfo[1]);

    if(curr->key == -1 && curr->val == -1)
    {
      free(curr);
      printf("aww! key & value both -1 accessing the deleted node, backoff :(\n");
      continue;
    }

   // pred->next = curr;  //use updateLinks()?????? 
    updateLinks(pred, curr); 
    pred = curr;

  } 
//  pred->next = tail;
  updateLinks(pred, tail);

  printf("recover_init_list | full list recovered :) :)\n");
  //list->node_count -= real_count;

//  list->mtx = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
  
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

    printf("pred: %p, %d, %d, %d  --> next: %p, %d, %d, %d \n\n",pred, pred->selfNodeInfo[0], pred->selfNodeInfo[1], pred->key, pred->next, pred->nextNodeInfo[0], pred->nextNodeInfo[1], pred->next->key);

    printf ("list:\n\n");
    while (curr != l->tail) {
      printf(" -->[%ld:%ld]: %p\n", (long int) curr->key, (long int)curr->val, curr);
      pred = curr;
      curr = curr->next;
     
     printf("pred: %p, %d, %d, %d  --> next: %p, %d, %d, %d \n\n",pred, pred->selfNodeInfo[0], pred->selfNodeInfo[1], pred->key, pred->next, pred->nextNodeInfo[0], pred->nextNodeInfo[1], pred->next->key);

    }
    printf("\n");
}

void show_list_with_offsets(const list_t *l)
{
  /* node_t *pred, *curr;

    pred = l->head;
    

    curr = pred->next;

  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
  {
    list->tailNodeInfo[i] = list->tail->selfNodeInfo[i];
  }


    printf ("list:\n\t");
    while (curr != l->tail) {
      printf(" -->[%ld:%ld]", (long int) curr->key, (long int)curr->val);
      pred = curr;
      curr = curr->next;
    }
    printf("\n");*/
}


#if 0
bool wayToSort(int i, int j) { return i < j; }

/*
 * void sort_list(const list_t * l)
 */
void sort_list(const list_t * l)
{
    node_t *pred, *curr;
    
    node_t **array = malloc((l->node_count - 2) * sizeof(node_t*)); // array of pointers of size `size`
 
    pred = l->head;
    curr = pred->next;
    int i = 0;
    printf ("list:\n\t");
    while (curr != l->tail) {
      printf(" ------>[%ld:%ld]", (long int) curr->key, (long int)curr->val);
      array[i] = curr;
      pred = curr;
      curr = curr->next;
      i++;
    }
    printf("\n");
//sorting with lambda function
std::sort(array, array + (l->node_count - 2), []( node_t* a,  node_t* b)
                                            {
                                                return (a->key < b->key);
                                            });

    /*std::cout<<"After array sort list: \n";
    for ( int i =0; i < (l->node_count - 2); ++i )
    {
      printf(" ->[%ld:%ld]", (long int) array[i]->key, (long int)array[i]->val);
    }
    printf("\n");
*/
    //reconstruct the links from array
    l->head->next = l->tail;
 
    for ( int i = (l->node_count - 2) - 1; i >= 0; --i )
    {
      node_t* nd_ptr = array[i];

      //insert in beg of list
      nd_ptr->next = l->head->next;
      l->head->next = nd_ptr;
    }

    std::cout<<"After reconstruct from array list: \n";
    show_list(l);

}
#endif

/*#include <string.h>

list_t *list;

int main (int argc, char **argv)
{
  key_t i;
  val_t g;

  list = init_list();

  show_list (list);

  for (i = 0; i < 10; i++) {
    add (list, (key_t)i, (val_t) i * 10);
  }  

  show_list (list);

  for (i = 0; i < 5; i++) {
    delete (list, (key_t)i, &g);
    printf ("ret = %ld\n", (long int)g);
  }

  show_list (list);

  free_list (list);

  return 0;
}*/

//#endif

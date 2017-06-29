/* ---------------------------------------------------------------------------
ISSUES: I get map error: 0xffffffffffff if try to free a node.
 * ---------------------------------------------------------------------------
 */
#include <algorithm>
#include "linkedlist.h"
pthread_mutex_t gmog;

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
  memset(name, 0, sizeof(NODE_INFO_ARR_SIZE*sizeof(char)));   

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
  
  //init node info of its location in memory
  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
  {
    node->nvnext.selfNodeName[i] = name[i];
    node->nvnext.nextNodeName[i] = 'A';  
  }
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
  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
  {
      first->nvnext.nextNodeName[i] = second->nvnext.selfNodeName[i];
  }
  first->next = second;
}


/*
 * success : return true
 * failure(key already exists) : return false
 */
bool add(list_t * list, const key_t key, const val_t val)
{
  pthread_mutex_lock(&(list->gmtx));
   // pthread_mutex_lock(&(gmog));
  
  node_t *pred, *curr;
  node_t *newNode;
  bool ret = true;
  #ifdef DBG
  printf("add | enter add [%d, %d]\n", key, val);
  #endif

 /* if ((newNode = create_node(key, val)) == NULL)
    return false;*/
  
     
  #ifdef DBG
  printf("add [%d, %d]\n", key, val);
  #endif
  pred = list->head;
  curr = pred->next;
  
  if (curr == list->tail)
  {
    if ((newNode = create_node(key, val, list)) == NULL) //creating nodes atomically solves the problem of negative values for the nodes.
    {
      printf("node could not be created\n");
      abort();
    }

    updateLinks(list->head, newNode);//list->head->next = newNode;
    updateLinks(newNode, list->tail);//newNode->next = list->tail;
  }
  else
  {
    while (curr != list->tail && curr->key < key)
    {
      pred = curr;
      curr = curr->next;
    }
    
    if (curr != list->tail && key == curr->key)//node found between sentinels
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
      if ((newNode = create_node(key, val, list)) == NULL) //creating nodes atomically solves the problem of 
      {
        printf("node could not be created\n");
        abort();
      }

      updateLinks(newNode, curr); //newNode->next = curr;
      updateLinks(pred, newNode); //pred->next = newNode;

      //list->node_count = list->node_count + 1;
    }
  }
  nvcheckpoint();
  if(ret)
    printf("add [%d, %d], %s, %s, %s, %s, %s\n", key, val, pred->nvnext.selfNodeName, pred->nvnext.nextNodeName, newNode->nvnext.selfNodeName, newNode->nvnext.nextNodeName, curr->nvnext.selfNodeName);

  pthread_mutex_unlock(&(list->gmtx));
  //  pthread_mutex_unlock(&(gmog));
  //nvcheckpoint(); //exploring reason of unrecovered val

  return ret;
}

/*
 * success : return true
 * failure(not found) : return false
 */
bool del(list_t * list, const key_t key, val_t *val)
{
  pthread_mutex_lock(&(list->gmtx));
   // pthread_mutex_lock(&(gmog));
  node_t *pred, *curr;
  bool ret = true;
  
  
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
      
      curr->key = -1;
      curr->val = -1;
      curr->marked = true;
      curr->next = NULL;
      //list->node_count = list->node_count - 1;//if i decrease then the names of two nodes would be same.
      list->real_node_count = list->real_node_count - 1;
      
      free(curr);
      ret = true;
    }
    else
    {
      ret = false;
    }
  }
  //nvcheckpoint();
  printf("delete [%d, %d] res: %d\n", key, (ret)?(*val):(-1), ret);
  pthread_mutex_unlock(&(list->gmtx));
 // pthread_mutex_unlock(&(gmog));
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
  list->node_count = 0;
  list->real_node_count = 0;  
  
  //init sentinel nodes
  list->head = create_node(VAL_MIN, VAL_MIN, list);
  if (list->head == NULL) {
    elog("nvmalloc error");
    goto end;
  }
  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++) //used during recovery of head node
  {
    list->headNodeName[i] = list->head->nvnext.selfNodeName[i];
  }  

  list->tail = create_node(VAL_MAX, VAL_MAX, list);
  if (list->tail == NULL) {
    elog("nvmalloc error");
    goto end;
  }
  for(int i = 0; i < NODE_INFO_ARR_SIZE; i++)
  {
    list->tailNodeName[i] = list->tail->nvnext.selfNodeName[i];
  }
  
  updateLinks(list->head, list->tail);

  //init global list mutex lock 
  pthread_mutex_init(&(list->gmtx), NULL);
   // pthread_mutex_init(&(gmog), NULL);

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
    
    printf("recovering node: %s\n", pred->nvnext.nextNodeName);
    node_t *curr = (node_t *)malloc(sizeof(node_t));
    nvrecover(curr, sizeof(node_t), pred->nvnext.nextNodeName);
    printNodeInfo(curr);//here next field is garbage

    updateLinks(pred, curr); //reconstructing the next field
    pred = curr;
  } 
  updateLinks(pred, tail);

  printf("recover_init_list | full list recovered :) :)\n");
  
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

    if(curr->key == 0 && curr->val == 0)
      printf("----->");
    if(strcmp(pred->nvnext.nextNodeName, curr->nvnext.selfNodeName) != 0)
      printf("***blunder next pointer and offsets not synchronized***");

      pred = curr;
      curr = curr->next;
    }
    printf(" -->[%ld:%ld]: %s %s\n", (long int) curr->key, (long int)curr->val, curr->nvnext.selfNodeName, curr->nvnext.nextNodeName);
    printf("********************************************************************************\n");
}

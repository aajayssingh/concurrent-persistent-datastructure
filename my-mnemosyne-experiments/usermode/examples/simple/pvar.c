#ifndef __PVAR_C__
#define __PVAR_C__
#include "pvar.h"

void init(void)
{
	PTx { 
			((list_t*)PADDR(mylist))->head = (mynode_t*)pmalloc(sizeof(mynode_t));
			((list_t*)PADDR(mylist))->head->key = MIN_KEY;
			((list_t*)PADDR(mylist))->head->val = MIN_KEY;
			((list_t*)PADDR(mylist))->head->next = NULL;

			((list_t*)PADDR(mylist))->tail = (mynode_t*)pmalloc(sizeof(mynode_t));
			((list_t*)PADDR(mylist))->tail->key = MAX_KEY;
			((list_t*)PADDR(mylist))->tail->val = MAX_KEY;
			((list_t*)PADDR(mylist))->tail->next = NULL;

			((list_t*)PADDR(mylist))->head->next = ((list_t*)PADDR(mylist))->tail;
			((list_t*)PADDR(mylist))->node_count = 2; /*UNUSED: head-->tail initially: meant to be used just for validation*/

			//init list gmtx
			pthread_mutex_init(&(((list_t*)PADDR(mylist))->gmtx), NULL);
	 	}

		printf("list inited...\n");
}

/*To init locks*/
void recover_init (void)
{
	printf("LIST: INIT LOCK\n");
	pthread_mutex_init(&(((list_t*)PADDR(mylist))->gmtx), NULL);
}
uint insert (list_t *list, uint key, uint val)
{
	uint ret = 0;
	pthread_mutex_lock(&(((list_t*)PADDR(mylist))->gmtx));
	
	mynode_t* pred = (mynode_t*)list->head;
	mynode_t* curr = (mynode_t*)pred->next;

	while(curr->key < key)
	{
		pred = curr;
		curr = curr->next;
	}

	if(curr->key == key)
	{
		ret = 0;
		printf("INSERT: key: %d already present!\n", key);
	}
	else
	{
		mynode_t* newPnode;
		PTx{
			newPnode = (mynode_t*)pmalloc(sizeof(mynode_t));
			newPnode->key = key;
			newPnode->val = val;
			newPnode->next = NULL;

			newPnode->next = curr;
			pred->next = newPnode;
			printf("INSERT: <key:val> ---> <%d:%d> \n", key, val);
		}
		ret = 1;
	}
	pthread_mutex_unlock(&(((list_t*)PADDR(mylist))->gmtx));
	return ret;
}

uint del (list_t *list, uint key, uint* val)
{
	uint ret = 0;
	pthread_mutex_lock(&(((list_t*)PADDR(mylist))->gmtx));
	
	mynode_t* pred = (mynode_t*)list->head;
	mynode_t* curr = (mynode_t*)pred->next;

	while(curr->key < key)
	{
		pred = curr;
		curr = curr->next;
	}

	if(curr->key == key)
	{
		PTx{
			*val = curr->val;
			pred->next = (mynode_t*)(curr->next);

			//pfree(curr);/*GIVES SEG FAult no Idea Why :P, I will Blame the library ;)*/
			curr->next = NULL;

			printf("DELETE: <key:val> ---> <%d:%d> \n", key, *val);
		}
		ret = 1;
	}
	else
	{
		ret = 0;
		printf("DELETE: Couldn't delete key:%d\n", key);
	}
	pthread_mutex_unlock(&(((list_t*)PADDR(mylist))->gmtx));
	return ret;
}
uint find (list_t *list, uint key, uint* val)
{
	uint ret = 0;
	pthread_mutex_lock(&(((list_t*)PADDR(mylist))->gmtx));
	
	mynode_t* pred = (mynode_t*)list->head;
	mynode_t* curr = (mynode_t*)pred->next;

	while(curr->key < key)
	{
		pred = curr;
		curr = curr->next;
	}

	if(curr->key == key)
	{
		*val = curr->val;
		printf("FIND: <key:val> ---> <%d:%d> \n", key, *val);
		ret = 1;
	}
	else
	{
		ret = 0;
		printf("FIND: Couldn't find key:%d\n", key);
	}
	pthread_mutex_unlock(&(((list_t*)PADDR(mylist))->gmtx));
	return ret;
}

void print_list(const list_t *list)
{
	mynode_t* node = NULL;
/*	for (node = (mynode_t*)(((list_t*)PADDR(mylist))->head); ((mynode_t*)node->next) != NULL; node = ((mynode_t*)(node->next)))
	{
		printf("<key:val> : <%d:%d>\n", node->key, node->val);
	}*/

	for (node = (mynode_t*)(list->head); ((mynode_t*)node) != NULL; node = ((mynode_t*)(node->next)))
	{
		printf("<key:val> : <%d:%d>\n", node->key, node->val);
	}
}


#endif

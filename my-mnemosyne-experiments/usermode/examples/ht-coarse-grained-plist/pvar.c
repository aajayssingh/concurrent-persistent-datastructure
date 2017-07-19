#ifndef __PVAR_C__
#define __PVAR_C__
#include "pvar.h"
/*Prepares a initial list with sentinel nodes as follows: 
  head -> tail

  mylist is the root structure which holds the list data.
*/
#if 0
void init(void)
{
	PTx { 
			/*explicit type cast is needed as mnemosyene doesnt have implicit way to support typed pointers.*/
			((list_t*)PADDR(mylist))->head = (mynode_t*)pmalloc(sizeof(mynode_t));
			((list_t*)PADDR(mylist))->head->key = MIN_KEY;
			((list_t*)PADDR(mylist))->head->val = MIN_KEY;
			((list_t*)PADDR(mylist))->head->next = NULL;
			pthread_mutex_init(&((((list_t*)PADDR(mylist))->head)->lmtx), NULL);


			((list_t*)PADDR(mylist))->tail = (mynode_t*)pmalloc(sizeof(mynode_t));
			((list_t*)PADDR(mylist))->tail->key = MAX_KEY;
			((list_t*)PADDR(mylist))->tail->val = MAX_KEY;
			((list_t*)PADDR(mylist))->tail->next = NULL;
			pthread_mutex_init(&((((list_t*)PADDR(mylist))->tail)->lmtx), NULL);

			((list_t*)PADDR(mylist))->head->next = ((list_t*)PADDR(mylist))->tail;
			((list_t*)PADDR(mylist))->node_count = 2; /*UNUSED: head-->tail initially: meant to be used just for validation*/

			//init list gmtx
			//pthread_mutex_init(&(((list_t*)PADDR(mylist))->gmtx), NULL);
	 	}

		printf("list inited...\n");
}
#endif
/*failed first time after sys boot comment the code for lock init and run and then works fine for later runs*/
void init(void)
{
	PTx {
			((root_t*)PADDR(myroot))->ht = (list_t*)pmalloc(sizeof(list_t)*TAB_SIZE);
			
			//assert(((root_t*)PADDR(myroot))->ht != 0); putting assert throws tx mode change error
			// if(NULL == ((root_t*)PADDR(myroot))->ht)
			// {
			// 	return;
			// }
			pthread_mutex_init(&( ((root_t*)PADDR(myroot))->htmtx ), NULL);

			((root_t*)PADDR(myroot))->ht_size = TAB_SIZE;

			// pthread_mutex_init(&( ( ((root_t*)PADDR(myroot))->ht )->gmtx ), NULL);

			 //pthread_mutex_t *pmtx = &(((mynode_t*)((list_t*)(((root_t*)PADDR(myroot))->ht))->head)->lmtx);

			//pthread_mutex_init(pmtx, NULL);


			for (int i = 0; i < TAB_SIZE; ++i)
			{
				((((root_t*)PADDR(myroot))->ht) + i)->node_count = 0;//dummy

				((((root_t*)PADDR(myroot))->ht) + i)->head = (mynode_t*)pmalloc(sizeof(mynode_t));
				((((root_t*)PADDR(myroot))->ht) + i)->head->key = MIN_KEY;
				((((root_t*)PADDR(myroot))->ht) + i)->head->val = MIN_KEY;
				((((root_t*)PADDR(myroot))->ht) + i)->head->next = NULL;
				//pthread_mutex_init(&( ((((root_t*)PADDR(myroot))->ht) + i)->head->lmtx ), NULL);

				((((root_t*)PADDR(myroot))->ht) + i)->tail = (mynode_t*)pmalloc(sizeof(mynode_t));
				((((root_t*)PADDR(myroot))->ht) + i)->tail->key = MAX_KEY;
				((((root_t*)PADDR(myroot))->ht) + i)->tail->val = MAX_KEY;
				((((root_t*)PADDR(myroot))->ht) + i)->tail->next = NULL;
				//pthread_mutex_init(&(((((root_t*)PADDR(myroot))->ht) + i)->tail->lmtx), NULL);

				((((root_t*)PADDR(myroot))->ht) + i)->head->next = ((((root_t*)PADDR(myroot))->ht) + i)->tail;

			}
		}

		/*init within transaction throws assert - cannot change tx mode*/
		for (int i = 0; i < TAB_SIZE; ++i)
		{
			 pthread_mutex_init(&(((list_t*)(((root_t*)PADDR(myroot))->ht + i))->gmtx), NULL);
		}
		printf("list inited...\n");
}


/*To re init the locks. In previous run if the application had crashed then, I have to ensure that
lock state which is recorded in persistent memory is reinitialised to ensure proper 
lock acquisition in the subsequent run of the application.*/
void recover_init (void)
{
	printf("RECOVER INIT: INIT LOCKS\n");
	mynode_t* node = NULL;

	for (int i = 0; i < TAB_SIZE; ++i)
	{
		pthread_mutex_init(&(((list_t*)(((root_t*)PADDR(myroot))->ht + i))->gmtx), NULL);
		printf("\n");
	}
}

/*insert a node with <key, val> inside the list if same key is not already present .
If the node<key, val> is inserted successfuly then function returns 1. Else if the node<key> is already
present the function returns 0.
*/
uint insert (list_t *list, uint key, uint val)
{
	uint ret = 0;
	pthread_mutex_lock(&(list->gmtx));
	
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
	pthread_mutex_unlock(&(list->gmtx));
	return ret;
}

/* Deletes a node<key> from the list and returns the <val> of the node<key>. If node cannot be deleted 
function returns 0. Else function returns 1 along with the <val>.
*/
uint del (list_t *list, uint key, uint* val)
{
	uint ret = 0;
	pthread_mutex_lock(&(list->gmtx));
	
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
			printf("\n\n Gonna DELETE: <key:val> ---> <%d:%d> \n", key, *val);
			*val = curr->val;
			pred->next = (mynode_t*)(curr->next);

			//pfree(curr);/*TODO: GIVES SEG FAult no Idea Why :P, I will Blame the library ;)*/
			//curr = NULL;

			printf("DELETE: <key:val> ---> <%d:%d> \n", key, *val);
		}
		ret = 1;
	}
	else
	{
		ret = 0;
		printf("DELETE: Couldn't delete key:%d\n", key);
	}
	pthread_mutex_unlock(&(list->gmtx));
	return ret;
}

/*Find a node<key> in the list and returns 1 alongwith the <val> found else returns 0.*/
uint find (list_t *list, uint key, uint* val)
{
	uint ret = 0;
	pthread_mutex_lock(&(list->gmtx));
	
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
	pthread_mutex_unlock(&(list->gmtx));
	return ret;
}

/*Print a bucket list of the hast table*/
void print_list(const list_t *list)
{
	mynode_t* node = NULL;

	printf("\tPRINTING LIST:\n");

	for (node = (mynode_t*)(list->head); ((mynode_t*)node) != NULL; node = ((mynode_t*)(node->next)))
	{
		printf("<key:val> : <%d:%d>\n", node->key, node->val);
	}
}

/*Print the hast table*/
uint print_tab()
{
	mynode_t* node = NULL;
	uint node_counter = 0;
	//assert to scheck myroot non null
	printf("\tPRINTING HT:\n");
	for (int i = 0; i < TAB_SIZE; ++i)
	{
		for (node = (mynode_t*)((((root_t*)PADDR(myroot))->ht) + i)->head; ((mynode_t*)node) != NULL; node = ((mynode_t*)(node->next)))
		{
			printf("<key:val> : <%d:%d> -->", node->key, node->val);
			node_counter++;
		}
		node_counter -= 2;
		printf(" %d\n", node_counter);
	}
	return node_counter;
}
#endif

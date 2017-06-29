/*
 * queue.cpp -- queue example implemented using pmemobj cpp bindings
 *
 * Please see pmem.io blog posts for more details.
 */

#include <ex_common.h>
#include <iostream>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/mutex.hpp>
#include <math.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <thread>

#define LAYOUT "plist"
#define MIN_KEY 0
#define MAX_KEY 100
#define NUM_THREADS 2

#define AJPMEMOBJ_MIN_POOL ((size_t)(1024 * 1024 * 1024 * 1)) /* 1 MB */

pthread_mutex_t ajlock;

namespace
{

/* available queue operations */
enum list_op {
	UNKNOWN_LIST_OP,
	LIST_INIT,
	LIST_INSERT,
	LIST_DELETE,
	LIST_PRINT,

	MAX_LIST_OP,
};

/* queue operations strings */
//const char *ops_str[MAX_LIST_OP] = {"", "init", "insert", "remove", "print"};

/*
 * parse_list_op -- parses the operation string and returns matching list_op
 */
/*list_op
parse_list_op(const char *str)
{
	for (int i = 0; i < MAX_LIST_OP; ++i)
		if (strcmp(str, ops_str[i]) == 0)
			return (list_op)i;

	return UNKNOWN_LIST_OP;
}*/
}

using nvml::obj::p;
using nvml::obj::persistent_ptr;
using nvml::obj::pool;
using nvml::obj::pool_base;
using nvml::obj::make_persistent;
using nvml::obj::delete_persistent;
using nvml::obj::transaction;
using nvml::obj::mutex;

namespace examples
{

/*
 * Persistent memory list-based queue
 *
 * A simple, not template based, implementation of queue using
 * libpmemobj C++ API. It demonstrates the basic features of persistent_ptr<>
 * and p<> classes.
 */
class pmem_list {

	/* entry in the list */
	struct pmem_entry {
		p<uint64_t> key;
		p<uint64_t> val;

		mutex local_node_pmutex;
		persistent_ptr<pmem_entry> next;
	};

	persistent_ptr<pmem_entry> head;
	persistent_ptr<pmem_entry> tail;
	p<bool> is_init = false;
	mutex global_list_pmutex;

public:
	
	void
	init (pool_base &pop)
	{
		transaction::exec_tx(pop, [&] {
			head = make_persistent<pmem_entry>();
			if(head == nullptr)
				std::cerr <<"head is nullptr"<< std::endl;
			head->key = MIN_KEY;
			head->val = MIN_KEY;
			head->next = nullptr;

			tail = make_persistent<pmem_entry>();
			if(tail == nullptr)
				std::cerr <<"tail is nullptr"<< std::endl;
			tail->key = MAX_KEY;
			tail->val = MAX_KEY;
			tail->next = nullptr;

			//link head and tail
			head->next = tail;
			is_init = true;

			std::cout <<"inited"<<std::endl;

		});
	}

	/*
	 * Inserts a new element in the list.
	 */
	bool
	insert(pool_base &pop, uint64_t key, uint64_t val)
	{
		bool ret = false;
		//std::cout<<"thread in insert" <<std::endl;
			this->global_list_pmutex.lock();
			std::cout<<"ADD entered CS key:"<<key <<std::endl;
		 	
			auto pred = head;
			auto curr = pred->next;

			while(curr->key < key)
			{
				pred = curr;
				curr = curr->next;
			}

			if(curr->key == key)
			{
				ret = false;
				std::cout<<"Node with key:"<<key<<" already present" <<std::endl;
			}
			else
			{
				persistent_ptr<pmem_entry> newPnode;
				std::cout <<"insert: "<< pred->key<<":"<<curr->key<<std::endl;
				

				transaction::exec_tx(pop, [&] {
					auto n =  make_persistent<pmem_entry>();
					newPnode = n;
					newPnode->key = key;
					newPnode->val = val;
					newPnode->next =curr;
				});

				// transaction::exec_tx(pop, [&] {
				// auto n = make_persistent<pmem_entry>();
				// n->key = 10;
				// });

				std::cout<<"new node created successfully" <<std::endl;
//				transaction::exec_tx(pop, [&] {});
				transaction::exec_tx(pop, [&] { //TODO: try adding the rane manually with manual Tx.
					pred->next = newPnode;
				});

/*	REPORT PROB:
//with this manual TX the second thread is unable to add node, runs successfully 
//but node not added, the problem is revealed by C++ binding, it says that 
//cannot add object to the transaction for second thread while setting pred->next = newNode.

			TX_BEGIN(pop.get_handle()){

				newPnode =  pmemobj_tx_alloc(sizeof (pmem_entry), 0);
				newPnode->key = key;
				newPnode->next =curr;
				}TX_END

				std::cout<<"new node created successfully" <<std::endl;


				TX_BEGIN(pop.get_handle()){
				pred->next = newPnode;
				}TX_END*/

				// persistent_ptr<void> newPvnode = newPnode;
				// pmemobj_persist(pop.get_handle(),  &newPvnode, sizeof (pmem_entry));		

				ret = true;
			//});
			}

			//pthread_exit(NULL);
	
			// pthread_mutex_unlock(&ajlock);
			std::cout<<"ADD gonna exit CS"<<key <<std::endl;
			print();
			this->global_list_pmutex.unlock();
	//	});
		
		return ret;
	}

	/*
	 * Removes the element from the list.
	 */
	bool remove(pool_base &pop, uint64_t key, uint64_t* val)
	{
		bool ret = false;
		*val = 0;
		this->global_list_pmutex.lock();
		std::cout<<"DELETE entered CS"<<key <<std::endl;
		//transaction::exec_tx(pop, [&] {
			if ((head == nullptr) || (tail == nullptr))
				transaction::abort(EINVAL);

			auto pred = head;
			auto curr = pred->next;

			while(curr->key < key)
			{
				pred = curr;
				curr = curr->next;
			}

			if(curr->key == key)
			{
				auto n = curr;
				*val = n->key;
				pred->next = curr->next;
				std::cout <<"*****************found to delete:"<< std::endl;
transaction::exec_tx(pop, [&] {
	//			pred->next = curr->next;
				//std::cout<<"inTX"<<std::endl;
				delete_persistent<pmem_entry>(n);
	});
				ret = true;
			}
			else
			{
				ret = false;
			}

			std::cout<<"DELETE gonna exit CS"<<key<<":" <<*val <<std::endl;
			this->global_list_pmutex.unlock();
		//});

		return ret;
	}

	/*
	 * finds the element in the list.
	 */
	bool find(pool_base &pop, uint64_t key, uint64_t* val)
	{
		bool ret = false;
		*val = 0;
		this->global_list_pmutex.lock();
		std::cout<<"FIND entered CS"<<key <<std::endl;
		//transaction::exec_tx(pop, [&] {
			if ((head == nullptr) || (tail == nullptr))
				transaction::abort(EINVAL);

			auto pred = head;
			auto curr = pred->next;

			while(curr->key < key)
			{
				pred = curr;
				curr = curr->next;
			}

			if(curr->key == key)
			{
				auto n = curr;
				*val = n->key;
				std::cout <<"*****************found key:"<< std::endl;
				ret = true;
			}
			else
			{
				ret = false;
			}

			std::cout<<"FIND gonna exit CS"<<key<<":" <<*val <<std::endl;
			this->global_list_pmutex.unlock();
		//});

		return ret;
	}


	/*
	 * Prints the entire contents of the queue.
	 */
	void
	print(void) const
	{
		std::cout<<"printing:" <<std::endl;
		for (auto n = head; n != nullptr; n = n->next)
			std::cout << n->key << std::endl;
	}

	bool
	is_inited(void)
	{
		return is_init;
	}
};

} /* namespace examples */

pool<examples::pmem_list> pop;
std::thread t[NUM_THREADS];

void worker(int tid)
{
	//std::cout<<"tid:" <<tid+1<<std::endl;
	auto q = pop.get_root();

	
	//if(tid%2 == 0)
	{
		uint64_t key = rand()%(MAX_KEY - 1) + 1;
		uint64_t val = rand()%(MAX_KEY - 1) + 1;
		q->insert(pop, key, val);
	}	
	/*else
	{
//		sleep(2);
		uint64_t key = rand()%10 + 1;
		uint64_t val;
		q->remove(pop, key, &val);//
	}*/
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cerr << "usage: " << argv[0]
			  << " file-name " << std::endl;
		return 1;
	}

	const char *path = argv[1];

	//list_op op = parse_list_op(argv[2]);

//	pool<examples::pmem_list> pop;

	if (file_exists(path) != 0) {
		pop = pool<examples::pmem_list>::create(
			path, LAYOUT, AJPMEMOBJ_MIN_POOL, CREATE_MODE_RW);
	} else {
		pop = pool<examples::pmem_list>::open(path, LAYOUT);
	}

	auto q = pop.get_root();

	if(!q->is_inited())
	{
		std::cout <<"init the list first!" <<std::endl;
		q->init(pop);
		q->print();
		return 0;
	}
	else
	{
		std::cout <<"list already inited, carry on operations" <<std::endl;
		q->print();
	}
	if (pthread_mutex_init(&ajlock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

		

	time_t tt;
	srand(time(&tt));

	for (int i = 0; i < 2; ++i)
	{
		uint64_t key = rand()%(MAX_KEY - 1) + 1;
		uint64_t val = rand()%(MAX_KEY-1) + 1;		
		q->insert(pop, key, val);
	}

	std::cout <<"\n********STARTING...\n";	
	
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		t[i] = std::thread(worker, i);
	}

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		t[i].join();
	}
	std::cout <<"\n********STOPPING...\n";

	q->print();
	

#if 0
	switch (op) {
		case LIST_INIT:
			std::cout <<"init:" <<std::endl;
			q->init(pop);
			//q->print();
			break;
		case LIST_INSERT:
		{
			std::thread t[NUM_THREADS];
			int i;
			for ( i = 1; i <= NUM_THREADS; ++i)
			{
				t[i] = std::thread(&(examples::pmem_list::q->insert), pop, i);
			}

			for ( i = 1; i <= NUM_THREADS; ++i)
			{
				t[i].join();
			}
//			std::cout <<"insert: "<<q->insert(pop, atoll(argv[3]))<<std::endl;
		}
	
			break;
		case LIST_DELETE:
		{
			uint64_t val;
			std::cout <<"remove res:" <<q->remove(pop, atoll(argv[3]), &val);
			std::cout <<"removed val: "<< val <<std::endl;
		}
			break;
		case LIST_PRINT:
			std::cout <<"print:" <<std::endl;
			q->print();
			break;
		default:
			throw std::invalid_argument("invalid queue operation");
			break;
	}
	#endif

	pop.close();

	return 0;
}

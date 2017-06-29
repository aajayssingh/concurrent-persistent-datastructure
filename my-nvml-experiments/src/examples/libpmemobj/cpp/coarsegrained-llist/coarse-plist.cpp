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
#define AJPMEMOBJ_MIN_POOL ((size_t)(1024 * 1024 * 1024 * 1)) /*1 GB*/
typedef uint64_t uint_t;

//DEFAULT VALUES
const uint_t num_threads = 10; /*multiple of 10 the better, for exact thread distribution */

/*should sum upto 100*/
uint_t num_insert_percent = 50;
uint_t num_delete_percent = 40;
uint_t num_lookup_percent = 10;
uint_t num_insert, num_delete, num_lookup;

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
		p<uint_t> key;
		p<uint_t> val;

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
	insert(pool_base &pop, uint_t key, uint_t val)
	{
		bool ret = false;
		this->global_list_pmutex.lock();
			//std::cout<<"ADD entered CS key:"<<key <<std::endl;
		 	
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
				
				transaction::exec_tx(pop, [&] {
					auto n =  make_persistent<pmem_entry>();
					newPnode = n;
					newPnode->key = key;
					newPnode->val = val;
					newPnode->next =curr;
					pred->next = newPnode;
					std::cout<<"INSERT: <pred:curr>: "<< pred->key<<":"<<curr->key <<" --> INSERT <key:val> "<< key<<":"<<val <<std::endl;
				});

		//		std::cout<<"ADD: <key:val>"<<key <<":"<<val <<std::endl;
//				transaction::exec_tx(pop, [&] {});
			//	transaction::exec_tx(pop, [&] { //TODO: try adding the rane manually with manual Tx.
			//		pred->next = newPnode;
			//	});

//	REPORT PROB:
//with this manual TX the second thread is unable to add node, runs successfully 
//but node not added, the problem is revealed by C++ binding, it says that 
//cannot add object to the transaction for second thread while setting pred->next = newNode.

				ret = true;
			}
			//std::cout<<"ADD gonna exit CS"<<key <<std::endl;
			//print();
			this->global_list_pmutex.unlock();

		return ret;
	}

	/*
	 * Removes the element from the list.
	 */
	bool remove(pool_base &pop, uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		this->global_list_pmutex.lock();
//		std::cout<<"DELETE entered CS"<<key <<std::endl;
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
				//pred->next = curr->next;
transaction::exec_tx(pop, [&] {
				pred->next = curr->next;
				//std::cout<<"inTX"<<std::endl;
				delete_persistent<pmem_entry>(n);
				std::cout <<"***DELETE: Deleted :) <key:val> "<<key<<":"<<*val<< std::endl;
	});
				ret = true;
			}
			else
			{
				ret = false;
				std::cout <<"***DELETE: Not Deleted <key:val> "<<key<<":"<<*val<< std::endl;
			}

//			std::cout<<"DELETE gonna exit CS"<<key<<":" <<*val <<std::endl;
			this->global_list_pmutex.unlock();
		return ret;
	}

	/*
	 * finds the element in the list.
	 */
	bool find(pool_base &pop, uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		this->global_list_pmutex.lock();
		//std::cout<<"FIND entered CS"<<key <<std::endl;
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
				std::cout <<"***FIND: found <key:val> "<<key<<":"<<*val<< std::endl;
				ret = true;
			}
			else
			{
				ret = false;
				std::cout <<"***FIND: Not found <key:val> "<<key<<":"<<*val<< std::endl;
			}

			//std::cout<<"FIND gonna exit CS"<<key<<":" <<*val <<std::endl;
			this->global_list_pmutex.unlock();

		return ret;
	}


	/*
	 * Prints the entire contents of the list.
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
std::thread t[num_threads];

void worker(uint_t tid)
{
	auto q = pop.get_root();

	if(tid%2 == 0)
		sleep(1);
	
	if(tid < num_insert)
	{
		uint_t key = rand()%10 + 1;
		uint_t val = rand()%(MAX_KEY - 1) + 1;
		q->insert(pop, key, val);
	}
	else if(tid < (num_insert + num_delete ))
    {
    	uint_t key = rand()%10 + 1;
		uint_t val;
		q->remove(pop, key, &val);
    }
	else if(tid < (num_insert + num_delete + num_lookup))//init for lookup threads
	{
		uint_t key = rand()%10 + 1;
		uint_t val;
		q->find(pop, key, &val);
	}
	else
	{
		std::cout<<"something wrong in thread distribution to operations"<<std::endl;
	}
	
	

/*	if(tid%2 == 0)
	{
		uint_t key = rand()%10 + 1;
		uint_t val = rand()%(MAX_KEY - 1) + 1;
		q->insert(pop, key, val);
	}	
	else
	{
//		sleep(2);
		uint_t key = rand()%10 + 1;
		uint_t val;
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

	if((num_insert_percent + num_delete_percent + num_lookup_percent) != 100)
	{
		std::cout<<"Oo LaLa! Seems you got arithmatic wrong :) #operations should sumup to 100" <<std::endl;
		return 0;
	}

	const char *path = argv[1];

	if (file_exists(path) != 0) 
	{
		pop = pool<examples::pmem_list>::create(path, LAYOUT, AJPMEMOBJ_MIN_POOL, CREATE_MODE_RW);
	} 
	else
	{
		pop = pool<examples::pmem_list>::open(path, LAYOUT);
	}

	auto q = pop.get_root();
	time_t tt;
	srand(time(&tt));

	if(!q->is_inited())
	{
		std::cout <<"init the list first!" <<std::endl;
		q->init(pop);
		for (uint_t i = 0; i < 2; ++i)
		{
			uint_t key = rand()%10 + 1;
			uint_t val = rand()%(MAX_KEY-1) + 1;		
			q->insert(pop, key, val);
		}

		q->print();
		return 0;
	}
	else
	{
		std::cout <<"list already inited, carry on operations" <<std::endl;
		q->print();
	}

	num_insert = (uint_t)ceil((num_insert_percent*num_threads)/100);
	num_delete = (uint_t)ceil((num_delete_percent*num_threads)/100);
	num_lookup = (uint_t)ceil((num_lookup_percent*num_threads)/100);

	std::cout<<"num_insert:"<<num_insert<<" num_delete: "<<num_delete<<" num_lookup: "<<num_lookup<<std::endl;

	if((num_insert + num_delete + num_lookup) > num_threads)
	{
		std::cout<<"((insertNum + delNum + lookupNum) > number_of_threads)"<<std::endl;
		return 0;
	}


	std::cout <<"\n********STARTING...\n";	
	
	for (uint_t i = 0; i < num_threads; ++i)
	{
		t[i] = std::thread(worker, i);
	}

	for (uint_t i = 0; i < num_threads; ++i)
	{
		t[i].join();
	}
	std::cout <<"\n********STOPPING...\n";

	q->print();

	pop.close();

	return 0;
}

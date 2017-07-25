/*!
 * AUTHOR:      Ajay Singh, IIT Hyderabad
 
 * ORGANIZATION:  LIP6 - INRIA&UPMC.
 * DATE:      Jul 20, 2017.
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

#define LAYOUT "plist"
#define MIN_KEY 0
#define MAX_KEY 1000
#define AJPMEMOBJ_MIN_POOL ((size_t)(1024 * 1024 * 1024 * 1)) /*1 GB*/
#define TIME_EVAL
typedef uint64_t uint_t;


using nvml::obj::p;
using nvml::obj::persistent_ptr;
using nvml::obj::pool;
using nvml::obj::pool_base;
using nvml::obj::make_persistent;
using nvml::obj::delete_persistent;
using nvml::obj::transaction;
using nvml::obj::mutex;

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
	/*
	* DESCP:	Prepares a initial list with sentinel nodes as follows: head -> tail
	* AUTHOR:	Ajay Singh
	*/
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
	* DESCP:	Insert a node with <key, val> inside the list if same key is not already present .
	If the node<key, val> is inserted successfuly then function returns 1. Else if the node<key> is already
	present the function returns 0.
	* AUTHOR:	Ajay Singh
	*/
	bool
	insert(pool_base &pop, uint_t key, uint_t val)
	{
		bool ret = false;
		
		head->local_node_pmutex.lock();
		auto pred = head;
		auto curr = pred->next;
		curr->local_node_pmutex.lock();

		while(curr->key < key)
		{
			pred->local_node_pmutex.unlock();
			pred = curr;
			curr = curr->next;
			curr->local_node_pmutex.lock();
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
			ret = true;
		}

		curr->local_node_pmutex.unlock();
		pred->local_node_pmutex.unlock();
		return ret;
	}

	/* 
	* DESCP:	Deletes a node<key> from the list and returns the <val> of the node<key>. If node cannot be deleted 
	function returns 0. Else function returns 1 along with the <val>.
	* AUTHOR:	Ajay Singh
	*/
	bool remove(pool_base &pop, uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		if ((head == nullptr) || (tail == nullptr))
			transaction::abort(EINVAL);

		head->local_node_pmutex.lock();
		auto pred = head;
		auto curr = pred->next;
		curr->local_node_pmutex.lock();

		while(curr->key < key)
		{
			pred->local_node_pmutex.unlock();
			pred = curr;
			curr = curr->next;
			curr->local_node_pmutex.lock();
		}

		if(curr->key == key)
		{
			auto n = curr;
			*val = n->key;
			transaction::exec_tx(pop, [&] {
					pred->next = curr->next;
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
		curr->local_node_pmutex.unlock();
		pred->local_node_pmutex.unlock();

		return ret;
	}

	/*
	* DESCP:	Find a node<key> in the list and returns 1 alongwith the <val> found else returns 0.
	* AUTHOR:	Ajay Singh
	*/
	bool find(pool_base &pop, uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		if ((head == nullptr) || (tail == nullptr))
			transaction::abort(EINVAL);

		head->local_node_pmutex.lock();
		auto pred = head;
		auto curr = pred->next;
		curr->local_node_pmutex.lock();

		while(curr->key < key)
		{
			pred->local_node_pmutex.unlock();
			pred = curr;
			curr = curr->next;
			curr->local_node_pmutex.lock();
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
		curr->local_node_pmutex.unlock();
		pred->local_node_pmutex.unlock();
		return ret;
	}


	/*
	* DESCP:	Print the list
	* AUTHOR:	Ajay Singh
	*/
	void
	print(void) const
	{
		std::cout<<"printing:" <<std::endl;
		for (auto n = head; n != nullptr; n = n->next)
			std::cout << n->key << std::endl;
	}

	/*
	 * DESCP:	checks if the list is already present in NVM.
	 * AUTHOR:	Ajay Singh
	 */
	bool
	is_inited(void)
	{
		return is_init;
	}
};

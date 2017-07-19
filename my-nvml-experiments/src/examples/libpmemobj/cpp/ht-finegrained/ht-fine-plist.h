/*
 * author: Ajay Singh
 */
#include <ex_common.h>
#include <iostream>
#include <libpmemobj++/make_persistent_array.hpp>
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
const uint_t tab_size = 16;

using nvml::obj::p;
using nvml::obj::persistent_ptr;
using nvml::obj::pool;
using nvml::obj::pool_base;
using nvml::obj::make_persistent;
using nvml::obj::delete_persistent;
using nvml::obj::transaction;
using nvml::obj::mutex;

/*
 * Persistent memory list-based queue
 *
 * A simple, not template based, implementation of queue using
 * libpmemobj C++ API. It demonstrates the basic features of persistent_ptr<>
 * and p<> classes.
 */
class pmem_ht {

	/* entry in the list */
	struct pmem_entry {
		p<uint_t> key;
		p<uint_t> val;

		mutex local_node_pmutex;
		persistent_ptr<pmem_entry> next;
	};

	struct pmem_list{
		persistent_ptr<pmem_entry> head;
		persistent_ptr<pmem_entry> tail;
		mutex global_list_pmutex;
	};

	p<bool> is_init = false;
	p<bool> ht_size = tab_size;
	persistent_ptr<pmem_list[]> ht;

public:

	uint_t hash_func(uint_t key)
	{
		//std::cout<<"ht_size"<<ht_size<<std::endl;
		return (key%tab_size);
	}
	/*
	 * creates the initial list with two sentinel nodes: head --->tail
	 */
	void
	init (pool_base &pop)
	{
		transaction::exec_tx(pop, [&] {

			ht_size = tab_size;
			ht = make_persistent<pmem_list[]>(tab_size);

			for (uint_t i = 0; i < tab_size; ++i)
			{
				ht[i].head = make_persistent<pmem_entry>();
				 if(ht[i].head == nullptr)
					std::cerr <<"head is nullptr"<< std::endl;
				ht[i].head->key = MIN_KEY;
				ht[i].head->val = MIN_KEY;
				ht[i].head->next = nullptr;

				ht[i].tail = make_persistent<pmem_entry>();
				if(ht[i].tail == nullptr)
					std::cerr <<"tail is nullptr"<< std::endl;
				ht[i].tail->key = MAX_KEY;
				ht[i].tail->val = MAX_KEY;
				ht[i].tail->next = nullptr;

				//link head and tail
				ht[i].head->next = ht[i].tail;
			}


			is_init = true;
			std::cout <<"inited"<<std::endl;

		});
	}

	/*
	 * Inserts a new node<key, val> in the list. If the operation succeeds then return true, 
	 * otherwise if the node<key> is already present return false.
	 */
	bool
	insert(pool_base &pop, uint_t key, uint_t val)
	{
		bool ret = false;
		uint_t bucket_index = hash_func(key);

		ht[bucket_index].head->local_node_pmutex.lock();
		auto pred = ht[bucket_index].head;
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
* Removes the node<key> from the list. If the node is present remove it and return true along with the node<val>, 
* else just return false.
*/
	bool remove(pool_base &pop, uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		uint_t bucket_index = hash_func(key);
		
			if ((ht[bucket_index].head == nullptr) || (ht[bucket_index].tail == nullptr))
				transaction::abort(EINVAL);

			ht[bucket_index].head->local_node_pmutex.lock();
			auto pred = ht[bucket_index].head;
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
	 * finds the node<key> in the list. If found return true along with node<val> corresponding to the desired key
	 * Else return false.
	 */
	bool find(pool_base &pop, uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		uint_t bucket_index = hash_func(key);

		if ((ht[bucket_index].head == nullptr) || (ht[bucket_index].tail == nullptr))
				transaction::abort(EINVAL);

		ht[bucket_index].head->local_node_pmutex.lock();
		auto pred = ht[bucket_index].head;
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
	 * Prints the entire contents of the list.
	 */
	void
	print(void) const
	{
		std::cout<<"printing:" <<std::endl;
		for (uint_t i = 0; i < tab_size; i = i+1)
		{
			for (auto n = ht[i].head; n != nullptr; n = n->next)
				std::cout <<"-->[" <<n->key <<":" <<n->val <<"] ";
			std::cout<< std::endl;
		}
	}

	/*
	 * checks if the list is already present in NVM.
	 */
	bool
	is_inited(void)
	{
		return is_init;
	}
};

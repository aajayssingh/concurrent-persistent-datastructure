#include <iostream>
#include <thread>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <sys/time.h>
#include <math.h>

//#define LAYOUT "plist"
#define MIN_KEY 0
#define MAX_KEY 100
//#define AJPMEMOBJ_MIN_POOL ((size_t)(1024 * 1024 * 1024 * 1)) /*1 GB*/
typedef uint64_t uint_t;

class volatile_list {

	/* entry in the list */
	struct volatile_entry {
		uint_t key;
		uint_t val;

		std::mutex local_node_pmutex;
		struct volatile_entry *next;
	};

	struct volatile_entry* head;
	struct volatile_entry* tail;
	std::mutex global_list_pmutex;
	uint_t node_count;
public:
	
	void
	init ()
	{
		head = new volatile_entry();
		if(head == nullptr)
			std::cerr <<"head is nullptr"<< std::endl;
		head->key = MIN_KEY;
		head->val = MIN_KEY;
		head->next = nullptr;

		std::cout <<"node alloc\n";
		tail = new volatile_entry();
		if(tail == nullptr)
			std::cerr <<"tail is nullptr"<< std::endl;
		tail->key = MAX_KEY;
		tail->val = MAX_KEY;
		tail->next = nullptr;

		//link head and tail
		head->next = tail;
		node_count = 2;

		std::cout <<"inited"<<std::endl;
	}

	/*
	 * Inserts a new element in the list.
	 */
	bool
	insert(uint_t key, uint_t val)
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
				struct volatile_entry* newVnode = new volatile_entry();
				
				newVnode->key = key;
				newVnode->val = val;
				newVnode->next =curr;
				pred->next = newVnode;
				std::cout<<"INSERT: <pred:curr>: "<< pred->key<<":"<<curr->key <<" --> INSERT <key:val> "<< key<<":"<<val <<std::endl;
				node_count++;
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
	bool remove(uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		this->global_list_pmutex.lock();
//		std::cout<<"DELETE entered CS"<<key <<std::endl;
			if ((head == nullptr) || (tail == nullptr))
				abort();

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
				
				delete(n);
				std::cout <<"***DELETE: Deleted :) <key:val> "<<key<<":"<<*val<< std::endl;
				node_count--;
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
	bool find(uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		this->global_list_pmutex.lock();
		//std::cout<<"FIND entered CS"<<key <<std::endl;
			if ((head == nullptr) || (tail == nullptr))
				abort();

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
		std::cout<<"printing: node_count: "<<node_count <<std::endl;
		for (auto n = head; n != nullptr; n = n->next)
			std::cout << n->key << std::endl;
	}
};
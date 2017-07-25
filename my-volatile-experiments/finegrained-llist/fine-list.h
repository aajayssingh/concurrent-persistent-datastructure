/*!
 * AUTHOR:			Ajay Singh, IIT Hyderabad 
 * ORGANIZATION: 	LIP6 - INRIA&UPMC.
 * DATE:			Jul 25, 2017.
 */
#ifndef FINE_LIST_H
#define FINE_LIST_H

#include <iostream>
#include <thread>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <sys/time.h>
#include <math.h>

//#define LAYOUT "plist"
#define MIN_KEY 0
#define MAX_KEY 100
#define TIME_EVAL
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
	//std::mutex global_list_pmutex;
	uint_t node_count;
public:
	/*
	* DESCP:	Prepares a initial list with sentinel nodes as follows: head -> tail
	* AUTHOR:	Ajay Singh
	*/
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
	* DESCP:	Insert a node with <key, val> inside the list if same key is not already present .
	If the node<key, val> is inserted successfuly then function returns 1. Else if the node<key> is already
	present the function returns 0.
	* AUTHOR:	Ajay Singh
	*/
	bool
	insert(uint_t key, uint_t val)
	{
		bool ret = false;
		head->local_node_pmutex.lock();
			//std::cout<<"ADD entered CS key:"<<key <<std::endl;
		 	
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
			curr->local_node_pmutex.unlock();
			pred->local_node_pmutex.unlock();
		return ret;
	}

	/* 
	* DESCP:	Deletes a node<key> from the list and returns the <val> of the node<key>. If node cannot be deleted 
	function returns 0. Else function returns 1 along with the <val>.
	* AUTHOR:	Ajay Singh
	*/
	bool remove(uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		head->local_node_pmutex.lock();
//		std::cout<<"DELETE entered CS"<<key <<std::endl;
			if ((head == nullptr) || (tail == nullptr))
				abort();

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
			curr->local_node_pmutex.unlock();
			pred->local_node_pmutex.unlock();
		return ret;
	}

	/*
	* DESCP:	Find a node<key> in the list and returns 1 alongwith the <val> found else returns 0.
	* AUTHOR:	Ajay Singh
	*/
	bool find(uint_t key, uint_t* val)
	{
		bool ret = false;
		*val = 0;
		head->local_node_pmutex.lock();
		//std::cout<<"FIND entered CS"<<key <<std::endl;
			if ((head == nullptr) || (tail == nullptr))
				abort();

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

			//std::cout<<"FIND gonna exit CS"<<key<<":" <<*val <<std::endl;
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
		std::cout<<"printing: node_count: "<<node_count <<std::endl;
		for (auto n = head; n != nullptr; n = n->next)
			std::cout << n->key << std::endl;
	}
};
#endif
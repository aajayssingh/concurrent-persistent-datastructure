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
#include <math.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define LAYOUT "plist"
#define MIN_KEY 0
#define MAX_KEY 100

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
const char *ops_str[MAX_LIST_OP] = {"", "init", "insert", "remove", "print"};

/*
 * parse_list_op -- parses the operation string and returns matching list_op
 */
list_op
parse_list_op(const char *str)
{
	for (int i = 0; i < MAX_LIST_OP; ++i)
		if (strcmp(str, ops_str[i]) == 0)
			return (list_op)i;

	return UNKNOWN_LIST_OP;
}
}

using nvml::obj::p;
using nvml::obj::persistent_ptr;
using nvml::obj::pool;
using nvml::obj::pool_base;
using nvml::obj::make_persistent;
using nvml::obj::delete_persistent;
using nvml::obj::transaction;

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
		persistent_ptr<pmem_entry> next;
		p<uint64_t> key;
	};

	persistent_ptr<pmem_entry> head;
	persistent_ptr<pmem_entry> tail;

public:
	
	void
	init (pool_base &pop)
	{
		transaction::exec_tx(pop, [&] {
			head = make_persistent<pmem_entry>();
			if(head == nullptr)
				std::cerr <<"head is nullptr"<< std::endl;
			head->key = MIN_KEY;
			head->next = nullptr;

			tail = make_persistent<pmem_entry>();
			if(tail == nullptr)
				std::cerr <<"tail is nullptr"<< std::endl;
			tail->key = MAX_KEY;
			tail->next = nullptr;

			//link head and tail
			head->next = tail;

			std::cout <<"inited"<<std::endl;

		});
	}

	/*
	 * Inserts a new element at the end of the queue.
	 */
	bool
	insert(pool_base &pop, uint64_t key)
	{
		bool ret = false;
		transaction::exec_tx(pop, [&] {
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
			}
			else
			{
				auto newPnode = make_persistent<pmem_entry>();
				newPnode->key = key;
				newPnode->next =curr;
				pred->next = newPnode;
				ret = true;
			}
		});
		return ret;
	}

	/*
	 * Removes the first element in the queue.
	 */
	bool remove(pool_base &pop, uint64_t key, uint64_t* val)
	{
		bool ret = false;
		*val = 0;
		transaction::exec_tx(pop, [&] {
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
				delete_persistent<pmem_entry>(n);
				ret = true;
			}
			else
			{
				ret = false;
			}
		});

		return ret;
	}

	/*
	 * Prints the entire contents of the queue.
	 */
	void
	print(void) const
	{
		for (auto n = head; n != nullptr; n = n->next)
			std::cout << n->key << std::endl;
	}
};

} /* namespace examples */

int
main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cerr << "usage: " << argv[0]
			  << " file-name [insert [key]|pop|print]" << std::endl;
		return 1;
	}

	const char *path = argv[1];

	list_op op = parse_list_op(argv[2]);

	pool<examples::pmem_list> pop;

	if (file_exists(path) != 0) {
		pop = pool<examples::pmem_list>::create(
			path, LAYOUT, PMEMOBJ_MIN_POOL, CREATE_MODE_RW);
	} else {
		pop = pool<examples::pmem_list>::open(path, LAYOUT);
	}

	auto q = pop.get_root();
	switch (op) {
		case LIST_INIT:
			std::cout <<"init:" <<std::endl;
			q->init(pop);
			//q->print();
			break;
		case LIST_INSERT:
//			q->insert(pop, atoll(argv[3]));
			std::cout <<"insert: "<<q->insert(pop, atoll(argv[3]))<<std::endl;
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

	pop.close();

	return 0;
}

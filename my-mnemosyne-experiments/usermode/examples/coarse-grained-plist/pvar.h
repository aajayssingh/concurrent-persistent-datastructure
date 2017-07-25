/*!
 * DESCP:     Driver file for coarse grained persistent list implemented using Mnemosyene. The algorithm
 *          used is taken from Art of multiprocessor programming book chapter 9. 
 
 * AUTHOR:      Ajay Singh, IIT Hyderabad
 
 * ORGANIZATION:  LIP6 - INRIA&UPMC.
 * DATE:      Jul 25, 2017.
 */

#ifndef __PVAR_H__
#define __PVAR_H__

#include <stdio.h>
#include <mnemosyne.h>
#include <mtm.h>
#include <assert.h>
#include <pmalloc.h>
#include <pthread.h>
#include <signal.h>

/**************************************************************************************/
//List Global declarations
/**************************************************************************************/
#define MIN_KEY 0
#define MAX_KEY 20
#define NUM_THREADS 1
#define TIME_EVAL
typedef unsigned int uint;

typedef struct _node //the name _node is not meant to be used outside the file
{
    uint key; 
    uint val;
    struct _node *next; 
} mynode_t;

typedef struct _list
{
  uint node_count; //needed to know how many nodes to be recovered, during recovery.
  mynode_t *head;  //TODO: declare them persistent
  mynode_t *tail;
  pthread_mutex_t gmtx; /*list global mutex for coarse grained list.*/  
} list_t;

void init (void);
void recover_init (void );
uint insert (list_t *list, uint key, uint val);
uint del (list_t *list, uint key, uint* val);
uint find (list_t *list, uint key, uint* val);

void print_list(const list_t *list);

#define TM_SAFE __attribute__((transaction_safe))
#define TM_CALL __attribute__((transaction_callable))
#define TM_PURE __attribute__((transaction_pure))
#define TM_ATTR TM_SAFE

#define TM_ATOMIC	__transaction_atomic
#define TM_RELAXED	__transaction_relaxed
#define PTx		TM_RELAXED

TM_PURE extern 
void __assert_fail (const char *__assertion, const char *__file,
                    unsigned int __line, const char *__function)
     __THROW __attribute__ ((__noreturn__));


#ifdef __PVAR_C__

#define PVAR(type, var) \
        MNEMOSYNE_PERSISTENT type var;      \
        TM_ATTR type pset_##var(type __##var)     \
      { return (var = __##var); } \
        TM_ATTR type pget_##var() { return var; } \
        TM_ATTR void* paddr_##var() { return (void*)&var; }

#else /* !__PVAR_C__ */

#define PVAR(type, var) \
        extern MNEMOSYNE_PERSISTENT type var;   \
        extern TM_ATTR type pset_##var(type);   \
        extern TM_ATTR type pget_##var();       \
        extern TM_ATTR void* paddr_##var();

#endif /* __PVAR_C__ */

#define PSET(var, val)  \
        pset_##var(val)
#define PGET(var)       \
        pget_##var()
#define PADDR(var)      \
        paddr_##var()

/* 
 * MENTION PERSISTENT VARIABLES HERE 
 * PVAR(type, variable_name)
 */
PVAR(int, flag);
PVAR(list_t, mylist);

#endif /* __PVAR_H__ */

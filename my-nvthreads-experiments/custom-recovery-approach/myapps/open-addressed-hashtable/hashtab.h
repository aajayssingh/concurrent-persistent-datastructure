
#ifndef _HASH_H_
#define _HASH_H_

#include "nvrecovery.h"

typedef bool bool_t;
typedef int lkey_t;
typedef int  val_t;

void ht_show();
void ht_init();
bool ht_add(int key, int value);
bool ht_lookup(int key, int* value);
bool ht_delete(int key, int* value);
void recover_ht();

#endif
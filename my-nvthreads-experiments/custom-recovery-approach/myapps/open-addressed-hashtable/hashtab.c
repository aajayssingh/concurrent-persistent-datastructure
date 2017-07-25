/*!
 * AUTHOR:      Ajay Singh, IIT Hyderabad
 
 * ORGANIZATION:  LIP6 - INRIA&UPMC.
 * DATE:      Jul 25, 2017.
 */
#include "hashtab.h"

/*#define touch_pages 10
#define table_size 1 * touch_pages
*/
#define HASH_TAB_SIZE 16 //16 //power of 2

//hash table entry
typedef struct hte{
    int key;
    int value;
    bool in_use;
    pthread_mutex_t gmtx;
}hte_t;

//Hash Table
hte_t *ht;
pthread_mutex_t ht_gm; //global lock for coarse grained hash table

void *t(void *args){
    nvcheckpoint();
    pthread_exit(NULL);
}


int ht_hash(int key)
{
    return(key%HASH_TAB_SIZE);
}

//to be called within lock only from add, delete and lookup methods
hte_t* ht_probe(int key, int value)
{
   int hash_offset = ht_hash(key);
   int probe_step = 1;//((hash_offset / HASH_TAB_SIZE) % HASH_TAB_SIZE);
  // probe_step |= 1;  // Force step to be odd. That way the loop below eventually visits every entry in the table!

    for (int i = 0; i < HASH_TAB_SIZE; i++) 
    {
        hte* e = &ht[hash_offset];

        // printf("key= %d & value= %d & in use %d\n", e->key, e->value, (int)e->in_use);
        if (!e->in_use)
           return e;
        if ((e->key == key))
            return e;

        hash_offset = (hash_offset + probe_step) % HASH_TAB_SIZE;  // no match found yet. linear probe move on.
        #ifdef DBG
        printf("next offset %d\n", hash_offset);
        #endif
    }
    return NULL; // oh no, the hash table is full and ascii is 23= ETB end of trans. block
}

bool ht_add(int key, int value)
{

    pthread_mutex_lock(&ht_gm);
    hte* e = ht_probe(key, value);
    
    if(e == NULL)
    {
        printf("so sorry! bob table is full\n");
        pthread_mutex_unlock(&ht_gm);
     
        return false;
    }
    #ifdef DBG
    printf("gonna ADD key= %d & value= %d & in use %d\n", key, value, (int)e->in_use);
    #endif

    if (e != NULL && !e->in_use)
    {
        e->in_use = true;
        e->key = key;        
        e->value = value; 
    #ifdef DBG
    printf("ADDED :) key= %d & value= %d & in use written%d\n", e->key, e->value, (int)e->in_use);
    #endif
    }
    else //key is in use and matches the key in entry overwrite value
    {
        //e->in_use = true;
        //e->key = key; 
        #ifdef DBG
        printf("overwritten key:%d with val:%d\n",key, value);
        #endif       
        e->value = value; //overwrite value because key is same.
    }

    printf("ADD [key: %d, value: %c] \n", e->key, e->value);
    pthread_mutex_unlock(&ht_gm);
    return true;
}

bool ht_lookup(int key, int* value)
{
    bool res = false;
 
    pthread_mutex_lock(&ht_gm);
    hte* e = ht_probe(key, value);
    if((e != NULL)&&(e->in_use))
    {
        *value = e->value;
        res = true;
        printf("LOOKUP [key: %d, value: %c] res:%d\n", key, *value, res);
    }
    else
    {
        res = false;
        printf("LOOKUP [key: %d, value: %c] res:%d\n", key, (e == NULL)?(23):(e->value), res);
    }
    
    pthread_mutex_unlock(&ht_gm);
    return res;
}

bool ht_delete(int key, int* value)
{
    bool res = false;
    pthread_mutex_lock(&ht_gm);
 
    hte* e = ht_probe(key, value);
    if((e != NULL)&&(e->in_use))
    {
        *value = e->value;
        e->value = 36;
        e->key = -1;
        e->in_use = false;
        res = true;
        printf("DELETE [key: %d, value: %c] res:%d\n", key, *value, res);
    }
    else
    {
        res = false;
        printf("DELETE [key: %d, value: %c] res:%d\n", key, (e == NULL)?(23):(e->value), res);
    }
    
    pthread_mutex_unlock(&ht_gm);
    return res;
}

//to be called before thread start
void recover_ht()
{
    struct hte *c = (struct hte*)malloc(sizeof(struct hte)*HASH_TAB_SIZE);
    nvrecover(c, sizeof(struct hte)*HASH_TAB_SIZE, (char*)"ht",0);
    
    for (int i = 0; i < HASH_TAB_SIZE; i++) {
    printf("c[%d] = %c\t", c[i].key, c[i].value);

    }
    printf("\n");

    free(c);
}

void ht_init()
{
    
    //nv malloc hash tab
    ht = (struct hte *)nvmalloc(sizeof(struct hte)*HASH_TAB_SIZE, (char*)"ht");

    //init hash table
    for (int i = 0; i < HASH_TAB_SIZE; i++)
    {
        ht[i].key = -1;
        ht[i].value = 36; //ascii of $
        ht[i].in_use = false;
        //pthread_mutex_init(&(ht[i]->gmtx), NULL); //fine grained mutex
    }

//mutex init for coarse grained hash tab ONLY.
    pthread_mutex_init(&ht_gm, NULL);
}

// to be called with single thread only.
void ht_show()
{
    printf("HAST_TABLE:\n");
    for (int i = 0; i < HASH_TAB_SIZE; i++)
    {
        printf("ht[%d] = %c\t", ht[i].key, ht[i].value);
    }
    printf("\n");
}

// ht_delete()
// {}
#if 0
int main(){
    pthread_mutex_init(&gm, NULL);
    pthread_t tid1;
    
    
    printf("Checking crash status\n");
    if ( isCrashed() ) {
        printf("I need to recover!\n");
        struct hte *c = (struct hte*)malloc(sizeof(struct hte)*HASH_TAB_SIZE);
        nvrecover(c, sizeof(struct hte)*HASH_TAB_SIZE, (char*)"ht",0);
        for (int i = 0; i < HASH_TAB_SIZE; i++) {
            printf("c[%d] = %c\t", c[i].key, c[i].value);
           
        }
        free(c);
    }
    else{    
        printf("Program did not crash before, continue normal execution.\n");
        pthread_create(&tid1, NULL, t, NULL);

        ht = (struct hte *)nvmalloc(sizeof(struct hte)*HASH_TAB_SIZE, (char*)"ht");

        //init hash table
        ht_init();

        ht_add(2, 100);
        ht_show();
        ht_add(2, 101);
        ht_show();
        ht_add(4, 102);
        ht_show();
        ht_add(1, 103);
        ht_show();
        printf("add key 3\n");
        ht_add(3, 104);
        ht_show();

        int val;
        if(ht_lookup(2, &val))
        {
            printf("lookup succeed & value =%c\n", val);            
        }
        else
        {
            printf("failed lookup\n");
        }



        if(ht_delete(3, &val))
        {
            printf("delete succeed & value =%c\n", val);            
        }
        else
        {
            printf("failed delete\n");
        }
        ht_add(3, 105);

        
        // ht_add(5, 105);
        // ht_add(2, 102);
        // ht_add(2, 103);
        // ht_add(2, 106);
        // ht_add(2, 107);
        // ht_add(8, 108);
        // ht_add(2, 109);
        //ht_show();
        
        nvcheckpoint();
        printf("finish writing to values & print HT\n");
        ht_show();

        pthread_join(tid1, NULL);
        printf("internally abort!\n");
        abort(); 
    }

    printf("\n-------------main exits-------------------\n");
    return 0;
}
#endif
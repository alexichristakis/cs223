#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "hash.h"

/*

modified hashtable code from notes

*/

struct elt {
    struct elt *next;
    char *key;
    int value;
};

struct hash {
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    struct elt **table;
};

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

/* dictionary initialization code used in both DictCreate and grow */
Hash
internalHashCreate(int size)
{
    Hash h;
    int i;

    h = malloc(sizeof(*h));

    assert(h != 0);

    h->size = size;
    h->n = 0;
    h->table = malloc(sizeof(struct elt *) * h->size);

    assert(h->table != 0);

    for(i = 0; i < h->size; i++) h->table[i] = 0;

    return h;
}

Hash
HashCreate(void)
{
    return internalHashCreate(INITIAL_SIZE);
}

void
HashDestroy(Hash h)
{
    int i;
    struct elt *e;
    struct elt *next;

    for(i = 0; i < h->size; i++) {
        for(e = h->table[i]; e != 0; e = next) {
            next = e->next;

            free(e->key);
            free(e);
        }
    }

    free(h->table);
    free(h);
}

#define MULTIPLIER (97)

static unsigned long
hash_function(const char *s)
{
    unsigned const char *us;
    unsigned long h;

    h = 0;

    for(us = (unsigned const char *) s; *us; us++) {
        h = h * MULTIPLIER + *us;
    }

    return h;
}

static void
grow(Hash h)
{
    // printf("we're growing\n");
    Hash h2;            /* new dictionary we'll create */
    struct hash swap;   /* temporary structure for brain transplant */
    int i;
    struct elt *e;

    h2 = internalHashCreate(h->size * GROWTH_FACTOR);

    for(i = 0; i < h->size; i++) {
        for(e = h->table[i]; e != 0; e = e->next) {
            /* note: this recopies everything */
            /* a more efficient implementation would
             * patch out the strdups inside HashInsert
             * to avoid this problem */
            HashInsert(h2, e->key);
        }
    }

    /* the hideous part */
    /* We'll swap the guts of d and h2 */
    /* then call DictDestroy on h2 */
    swap = *h;
    *h = *h2;
    *h2 = swap;

    HashDestroy(h2);
}

char *
strsave(const char *src) 
{
    return strcpy(malloc(strlen(src)+1), src); 
}

/* insert a new key-value pair into an existing dictionary */
void
HashInsert(Hash h, const char *key)
{
    struct elt *e;
    unsigned long hash;

    assert(key);

    e = malloc(sizeof(*e));

    assert(e);

    e->key = strsave(key);
    e->value = 1;

    hash = hash_function(key) % h->size;

    e->next = h->table[hash];
    h->table[hash] = e;

    h->n++;

    /* grow table if there is not enough room */
    if(h->n >= h->size * MAX_LOAD_FACTOR) {
        grow(h);
    }
}

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
const int
HashSearch(Hash h, const char *key)
{
    struct elt *e;

    for(e = h->table[hash_function(key) % h->size]; e != 0; e = e->next) {
        if(!strcmp(e->key, key)) {
            /* got it */
            return e->value;
        }
    }

    return 0;
}

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void
HashDelete(Hash h, const char *key)
{
    struct elt **prev;          /* what to change when elt is deleted */
    struct elt *e;              /* what to delete */

    for(prev = &(h->table[hash_function(key) % h->size]); 
        *prev != 0; 
        prev = &((*prev)->next)) {
        if(!strcmp((*prev)->key, key)) {
            /* got it */
            e = *prev;
            *prev = e->next;

            free(e->key);
            free(e);

            return;
        }
    }
}
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "hash.h"

struct elt {
    struct elt *next;
    unsigned int x;
    unsigned int y;
    unsigned int z;
    unsigned char value;
};

struct hash {
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    struct elt **table;
};

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (5)

/* Hashtable initialization code used in both HashCreate and grow */
Hash internalHashCreate(int size) {
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

Hash HashCreate(void) {
    return internalHashCreate(INITIAL_SIZE);
}

void HashDestroy(Hash h) {
    int i;
    struct elt *e;
    struct elt *next;

    for(i = 0; i < h->size; i++) {
        for(e = h->table[i]; e != 0; e = next) {
            next = e->next;
            free(e);
        }
    }

    free(h->table);
    free(h);
}

static unsigned long hash_function(const int x, const int y, const int z) {
	return (x * 13) + (y * 41) + (z * 67);
}

static void grow(Hash h) {
    Hash h2;            /* new Hashionary we'll create */
    struct hash swap;   /* temporary structure for brain transplant */
    int i;
    struct elt *e;

    h2 = internalHashCreate(h->size * GROWTH_FACTOR);

    for(i = 0; i < h->size; i++) {
        for(e = h->table[i]; e != 0; e = e->next) {
            HashInsert(h2, e->x, e->y, e->z, e->value);
        }
    }

    swap = *h;
    *h = *h2;
    *h2 = swap;

    HashDestroy(h2);
}

/* insert a new key-value pair into an existing Hashionary */
void HashInsert(Hash h, const int x, const int y, const int z, const char value) {
    struct elt *e;
    unsigned long hashed;

    // set up new node
    e = malloc(sizeof(*e));
    e->x = x;
    e->y = y;
    e->z = z;
    e->value = value;

    // generate hash code
    hashed = hash_function(x, y, z) % h->size;

    struct elt *temp;
    int boolean = 1;
    for (temp = h->table[hashed]; temp != 0; temp = temp->next) {
    	if (temp->x == x && temp->y == y && temp->z == z) {
    		temp->value = value;
    		free(e);
    		boolean = 0;
    	}
    }

    if (boolean) {
    	e->next = h->table[hashed];
  		h->table[hashed] = e;
    }
   
    h->n++;

    /* grow table if there is not enough room */
    if(h->n >= h->size * MAX_LOAD_FACTOR) {
        grow(h);
    }
}

int HashSearch(Hash h, const int x, const int y, const int z) {
    struct elt *e;

    for (e = h->table[hash_function(x, y, z) % h->size]; e != 0; e = e->next)
        if (e->x == x && e->y == y && e->z == z) return 1;

    return 0;
}

char HashGet(Hash h, const int x, const int y, const int z) {
	struct elt *e;

    for (e = h->table[hash_function(x, y, z) % h->size]; e != 0; e = e->next)
        if (e->x == x && e->y == y && e->z == z) return e->value;

    return 0;
}
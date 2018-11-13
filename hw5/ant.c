#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "ant.h"

void west(Ant *a) {
	a->x--;
}

void south(Ant *a) {
	a->y--;
}

void north(Ant *a) {
	a->y++;
}

void east(Ant *a) {
	a->x++;
}

void up(Ant *a) {
	a->z++;
}

void down(Ant *a) {
	a->z--;
}


void jump(Ant *a) {
	a->x = 2*a->x;
	a->y = 2*a->y;

	
	a->z = 2*a->z;
}

void write(struct ant *a, Hash h) {
	HashInsert(h, a->x, a->y, a->z, a->name);
}

void read(struct ant *a, Hash h) {
	if (!HashSearch(h, a->x, a->y, a->z)) {
		printf(" ");
	} else {
		putchar(HashGet(h, a->x, a->y, a->z));
	}
}
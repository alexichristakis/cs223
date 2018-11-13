#include "hash.h"

typedef struct ant {
	unsigned int x;
    unsigned int y;
    unsigned int z;
    char name;
} Ant;

void west(Ant *a);

void south(Ant *a);

void north(Ant *a);

void east(Ant *a);

void up(Ant *a);

void down(Ant *a);

void jump(Ant *a);

void write(Ant *a, Hash h);

void read(Ant *a, Hash h);
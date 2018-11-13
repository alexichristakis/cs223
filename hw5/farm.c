#include <stdio.h>
#include <stdlib.h>

#include "ant.h"

int main(int argc, char** argv) {
	// set up ant army
	Ant **army = malloc(256*sizeof(Ant));
	for (int i = 0; i < 256; i++) {
		Ant *ant = malloc(sizeof(Ant));
		ant->x = 0;
		ant->y = 0;
		ant->z = 0;
		ant->name = i;
		army[i] = ant;
	}

	Hash universe = HashCreate();
	Ant *current = army[getchar()];

	char c;
	unsigned char newAnt;
	while ((c = getchar()) != EOF) {
		switch (c) {
			case 'h':
				west(current);
				break;
			case 'j':
				south(current);
				break;
			case 'k':
				north(current);
				break;
			case 'l':
				east(current);
				break;
			case '<':
				up(current);
				break;
			case '>':
				down(current);
				break;
			case '*':
				jump(current);
				break;
			case '.':
				write(current, universe);
				break;
			case '?':
				read(current, universe);
				break;
			case '\n':
				newAnt = getchar();
				current = army[newAnt];
				break;
			default:
				break;
		}
	}

	HashDestroy(universe);

	for (int i = 0; i < 256; i++) free(army[i]);
	free(army);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Standard suits and ranks
#define SUITS "CDHS"
#define RANKS "A23456789TJQK"

// A single card
typedef struct card {
    char rank;   /* from RANKS */
    char suit;   /* from SUITS */
} Card;

typedef struct node {
 	struct node *next; // my successor in the linked list
  	Card value; // current card in the stack
} Node;

// A deck of cards
typedef struct deck {
	int size;
	Node *head;
	Node *tail;
} Deck;

Deck *deckCreate(void) {

	Deck *d = malloc(sizeof(Deck));
	for (int suit = 0; suit < 4; suit++) {
		for (int rank = 0; rank < 13; rank++) {
			Card c;
			c.suit = SUITS[suit];
			c.rank = RANKS[rank];

			Node *new = malloc(sizeof(Node));
			new->value = c;

			if (suit == 0 && rank == 0) {
				d->head = new;
				d->tail = new;
			} else {
				Node *old = d->tail;
				old->next = new;
				d->tail = new;
			}
		}
	}

	d->size = 52;
	return d;
}

int deckNotEmpty(const Deck *d) {
	if (d->size > 0) return 1;
	else return 0;
}

Card deckGetCard(Deck *d) {
	assert(d->size > 0);
	Card c = d->head->value;

	Node *old = d->head;
	d->head = d->head->next;
	
	d->size--;
	free(old);

	return c; 
}

void deckDestroy(Deck *d) {
	while (deckNotEmpty(d)) {
		deckGetCard(d);
	}
	free(d);
}

void deckPutCard(Deck *d, Card c) {
	Node *new = malloc(sizeof(Node));
	new->value = c;

	if (d->size == 0) {
		d->head = new;
		d->tail = new;
	} else {
		d->tail->next = new;
		d->tail = new;
	}

	d->size++;
}

void deckSplit(Deck *d, int n, Deck **d1, Deck **d2) {
	Deck *first = malloc(sizeof(Deck));
	Deck *second = malloc(sizeof(Deck));
	first->size = 0;
	second->size = 0;

	if (d->size < n) n = d->size; 
	for (int i = 0; i < n; i++) {
		Card c = deckGetCard(d);
		deckPutCard(first, c);
	}

	second->head = d->head;
	second->tail = d->tail;
	second->size = d->size;
	free(d);

	*d1 = first;
	*d2 = second;
}

Deck *deckShuffle(Deck *d1, Deck *d2) {
	Deck *d = malloc(sizeof(Deck));
	d->size = 0;

	while (deckNotEmpty(d1) && deckNotEmpty(d2)) {
		Card c1 = deckGetCard(d1);
		deckPutCard(d, c1);

		Card c2 = deckGetCard(d2);
		deckPutCard(d, c2);
	}

	if (deckNotEmpty(d1)) {
		if (d->size == 0) d->head = d1->head;
		else d->tail->next = d1->head;
		d->tail = d1->tail;
		d->size += d1->size;
	} else {
		if (d->size == 0) d->head = d2->head;
		else d->tail->next = d2->head;
		d->tail = d2->tail;
		d->size += d2->size;
	}

	free(d1);
	free(d2);

	return d;
}

void deckPrint(const Deck *d, FILE *f) {
	Node *node = d->head;

	for (int i = 0; i < d->size; i++) {
		if (i == d->size - 1) fprintf(f, "%c%c", node->value.rank, node->value.suit);
		else fprintf(f, "%c%c ", node->value.rank, node->value.suit);
		node = node->next;
	}

}


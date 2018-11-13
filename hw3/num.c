#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct num {
	int size;
	int *digits;
};

typedef struct num Num;

Num * numCreate(const char *s) {
	Num *a;
	int length = strlen(s);
	if (length == 1) {
		int *n = malloc(sizeof(int));
		n[0] = s[0] - '0';
		a = malloc(sizeof(Num));
		a->size = 1;
		a->digits = n;
		return a;
	}
	if (length == 0) {
		return (0);
	}

	int *n = malloc(sizeof(int)*length);

	for (int i = length - 1; i >= 0; i--) {
		char val = s[length - i - 1] - '0';
		if (val >= 0 && val <= 9) {
			n[i] = s[length - i - 1] - '0';
		} else {
			free(n);
			return (0);
		}
	}
	while (n[length - 1] == 0) length--;
	n = realloc(n, sizeof(int)*length);

	a = malloc(sizeof(Num));
	a->size = length;
	a->digits = n;
	
	return a;
}


void numDestroy(Num *n) {
	free(n->digits);
	free(n);
}

int numGetDigit(const Num *n, int i) {
	if (i > n->size || i < 0) {
		return 0;
	} else {
		return n->digits[i];
	}
}

Num * numAdd(const Num *x, const Num *y) {
	int longer = (x->size > y->size) ? x->size : y->size;
	int sumSize = longer + 1;
	int *n = malloc(sizeof(int)*sumSize);

	int a, b, s, carry = 0;
	for (int i = 0; i <= longer; i++) {
		if (i < x->size) a = x->digits[i];
		else a = 0;

		if (i < y->size) b = y->digits[i];
		else b = 0;

		s = a + b + carry;
		if (s > 9) {
			n[i] = s%10;
			carry = s/10;
		} else {
			n[i] = s;
			carry = 0;
		}
	}

	if (n[sumSize] == 0) {
		sumSize--;
		n = realloc(n, sizeof(int)*sumSize);
	}

	Num *sum = malloc(sizeof(Num));
	sum->digits = n;
	sum->size = sumSize;

	return sum;
}

Num * numMultiply(const Num *x, const Num *y) {
	int prodSize = x->size + y->size; 
	int *n = malloc(sizeof(int)*(prodSize + 1));

	for (int i = 0; i < prodSize; i++) n[i] = 0;
	for (int i = 0; i < x->size; i++) {
		for (int j = 0; j < y->size; j++) {
			n[i+j] += x->digits[i]*y->digits[j];
		}
	}

	for (int i = 0; i < prodSize; i++) {
		int carry = n[i]/10;
        n[i] = n[i]%10;
        n[i+1] += carry;
	}

	while (n[prodSize - 1] == 0 && prodSize > 1) prodSize--;
	n = realloc(n, sizeof(int)*prodSize);

	Num *prod = malloc(sizeof(Num));
	prod->size = prodSize;
	prod->digits = n;

	return prod; 
}

void numPrint(const Num *n, FILE *f) {
	for (int i = n->size - 1; i >= 0; i--) {
		putc(n->digits[i] + '0', f);
	}
}

#include "array.h"
#include <stdio.h>
#include <assert.h>

struct array {
	size_t size;
	int combined;
	int (*combine)(int, int);
	struct array *left;
	struct array *right;
};


Array *
arrayCreate(int (*combine)(int, int), size_t n)
{
	Array *root = malloc(sizeof(Array));
	root->combine = combine;
	root->size = n;

	if (n <= 1) {
		root->left = 0;
		root->right = 0;
		root->combined = 0;
		return root;
	} else {
		root->left = arrayCreate(combine, n - n/2);
		root->right = arrayCreate(combine, n/2);
		root->combined = combine(root->left->combined, root->right->combined);
		return root;
	}
}

void 
arrayDestroy(Array *root) 
{
	if (root != 0) {
		arrayDestroy(root->left);
		arrayDestroy(root->right);
	}
	free(root);
}

size_t 
arraySize(const Array *root) 
{
	return root->size;
}

int 
arrayGet(const Array *a, size_t i)
{	
	if (i >= a->size || i < 0) return 0;
	if (a->size == 1) {
		return a->combined;
	} else if (i < a->left->size) {
		return arrayGet(a->left, i);
	} else {
		return arrayGet(a->right, i - a->left->size);
	}
}

void 
arraySet(Array *root, size_t i, int v) 
{
	if (i >= root->size || i < 0) return;
	if (root->size == 1) {
		root->combined = v;
		return;
	} else if (i < root->left->size) {
		arraySet(root->left, i, v);
	} else {
		arraySet(root->right, i - root->left->size, v);
	}

	root->combined = root->combine(root->left->combined, root->right->combined);
}

int 
arrayCombine(const Array *root, size_t k) 
{	
	if (k >= root->size || k == 0) {
		return root->combined;
	} else if (k <= root->left->size) {
		return arrayCombine(root->left, k);
	} else {
		return root->combine(root->left->combined, arrayCombine(root->right, k - root->left->size));
	}
}
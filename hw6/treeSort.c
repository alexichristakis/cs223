#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
	int size; // size of tree
	int children; // number of children currently housed
	int maxChildren; // size of child array
	struct node *parent; 
    struct node **child;
};

void 
treeDestroy(struct node *root) 
{
	int i;
	if (root != 0) {
		for (i = 0; i < root->children; i++) {
			treeDestroy(root->child[i]);
		}
		free(root->child);
		free(root);
	}
}

void
treePrint(const struct node *root) 
{
	int i;
	if (root != 0) {
		printf("[");
		for (i = 0; i < root->children; i++) {
			treePrint(root->child[i]);
		}
		printf("]");
	}
}

void
updateTreeSize(struct node **tree) 
{	
	struct node *current;
	current = (*tree)->parent;
	while (current != 0) {
		current->size++;
		current = current->parent;
	}
}

static int
sizeCmp(const void *t1, const void *t2)
{	
	return (*(struct node **)t2)->size - (*(struct node **)t1)->size;
}

void
treeSort(struct node *root)
{
	int i;
	if (root != 0) {
		for (i = 0; i < root->children; i++) {
			treeSort(root->child[i]);
		}
		qsort((void *)root->child, root->children, sizeof(struct node *), sizeCmp);
	}
}

int 
main(int argc, char **argv) 
{
	struct node *tree = malloc(sizeof(struct node));
	tree->size = 1;
	tree->children = 0;
	tree->parent = 0;
	tree->maxChildren = 1;
	tree->child = malloc(sizeof(struct node));

	struct node *current = tree; 

	int completeTree = 0;
	int c = getchar();
	if (c != '[') {
		treeDestroy(tree);
		return 1;
	}
	while ((c = getchar()) != EOF) {

		struct node *new;
		if (c == '[') {
			completeTree++;

			/* set up new node */
			new = malloc(sizeof(struct node));
			new->size = 1;
			new->children = 0;
			new->parent = current; 
			new->maxChildren = 1;
			new->child = malloc(sizeof(struct node));

			/* resize array if necessary */
			if (current->children > current->maxChildren) {
				current->maxChildren *= 2;
				current->child = realloc(current->child, current->maxChildren*sizeof(struct node));
			}
			
			/* add new child and check if that child has children */
			current->child[current->children] = new;

			/* increment number of children */
			current->children++;

			updateTreeSize(&new);

			/* reassign current pointer to its new child */
			current = new;

		} else if (c == ']') {
			completeTree--;
			if (current->parent == 0) {
				break;
			} else {
				current = current->parent;
			}
		} else { 
			treeDestroy(tree); 
			return 1; 
		}
	}

	if (!completeTree) {
		treeDestroy(tree);
		return 1;
	} else {
		treeSort(tree);
		treePrint(tree); 
		treeDestroy(tree);
	}
	
	return 0;
}
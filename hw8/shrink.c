#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

struct node {
	struct node *next;
	char *value;
};

typedef struct node *Node;

void 
destroy(Node stack) 
{
	while (stack->next != 0) {
		free(stack->value);
		Node n;
		n = stack;
		stack = stack->next;
		free(n);
	}
	if (stack) free(stack);
}

void
print(const Node *n)
{
    struct node *e;
    for (e = *n; e->next != 0; e = e->next) {
        printf("%s\n", e->value);
    }
}

int
vowel(const char c)
{
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return 1;
	else return 0;
}

int
match(const char *s, int i, int j) 
{
	if (abs(s[i] - s[j]) <= 5 || (vowel(s[i]) && vowel(s[j]))) return 1;
	else return 0;
}

void
stackpush(Node *n, char *word) 
{
	struct node *new = malloc(sizeof(struct node));
	new->value = strdup(word);
	new->next = *n;
	*n = new;
}

int
aux(Node *stack, Hash visited, char *word, size_t length) 
{	
	if (length == 0) {
		stackpush(stack, word);
		free(word);
		return 1;
	} 

	int value = 0;
	for (int i = 0; i < length; i++) {
		if (match(word, i, i + 1)) {
			char *str = strdup(word);

			strcpy(&str[i], &word[i + 1]);

			if (HashSearch(visited, str)) {
				free(str);
			} else {
				HashInsert(visited, str);
				value = aux(stack, visited, str, length - 1);
				if (value) break;
			}
		}

		if (i + 3 <= length && match(word, i, i + 3)) {
			char *str = strdup(word);

			str[i] = word[i + 3];
			strcpy(&str[i + 3], &word[i + 4]);

			if (HashSearch(visited, str)) {
				free(str);
			} else {
				HashInsert(visited, str);
				value = aux(stack, visited, str, length - 1);
				if (value) break;
			}
		}
	}

	if (value) {
		stackpush(stack, word);
		free(word);
		return 1;
	}  else {
		free(word);
		return 0;
	}

}

Node
create(char *input, Hash visited) 
{
	Node root = malloc(sizeof(struct node));
	root->next = 0;

	char * startword = strdup(input);
	aux(&root, visited, startword, strlen(input) - 1);

	return root;
}


int
main(int argc, char **argv) 
{
	char *input = argv[1];

	Hash visited = HashCreate();
	Node root = create(input, visited);

	// Node *root = malloc(sizeof(Node *));
	// aux(root, visited, input, strlen(input) - 1);

	HashDestroy(visited);
	print(&root);
	destroy(root);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define INITIAL_WORD_LENGTH (2)

char * getWord(void);

int main(int argc, char **argv) {
	int c;
	char *word;
	while ((c = getchar()) != EOF) {
		if (!isalpha(c)) {
			putchar(c);
		} else {
			ungetc(c, stdin);
			word = getWord();
			int length = strlen(word);

			// move the first character to the end
			if (length > 1) {
				char first = word[0];
				memmove(word, word + 1, length - 1);
				if (isupper(first)) {
					word[0] = toupper(word[0]);
				} else {
					word[0] = tolower(word[0]);
				}
				word[length - 1] = tolower(first);
			}

			// add 'o' or 'an'
			if (length > 3) {
				word = realloc(word, length + 1);
				word[length] = 'o';
				word[length + 1] = '\0';
			} else {
				word = realloc(word, length + 2);
				word[length] = 'a';
				word[length + 1] = 'n';
				word[length + 2] = '\0';
			}

			// print the word
			printf(word);

			// free the memory
			free(word);
		}
	}

	return 0;
}

char * getWord(void) {
	char *word;
	int size;
	int length;
	int c;

	size = INITIAL_WORD_LENGTH;
	word = malloc(size);
	assert(word);

	length = 0;
	while ((c = getchar()) != EOF && isalpha(c)) {
		if (length >= size-1) {
			size *= 2;
			word = realloc(word, size);
		}
		word[length++] = c;
	}
	ungetc(c, stdin);
	word[length] = '\0';
	return word;
}

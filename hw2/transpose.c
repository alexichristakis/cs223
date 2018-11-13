#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define INITIAL_STRING_LENGTH (2);

int main(int argc, char **argv) {
	long n = atoi(argv[1]);
	if (argc != 4 || n < 1)	return 1;

	long a = atoi(argv[2]);
	long b = atoi(argv[3]);

	char *string;
    int size;
    int length;
    int c;

    size = INITIAL_STRING_LENGTH;
    string = malloc(size);
    assert(string);

    length = 0;

    while((c = getchar()) != EOF) {
        if(length >= size-1) {
            size *= 2;
            string = realloc(string, size);
        }

        string[length++] = c;
    }

    string[length] = '\0';
	int offset = length % n;
	int blocks = length / n;

	// pad the end of the string with null characters
	if (offset != 0) {
		int buffer = n - offset; 
		string = realloc(string, length + buffer);
		for (int i = 1; i < buffer; i++) {
			string[length + i] = '\0';
		}
		blocks = (length + buffer) / n;
	}

	for (int block = n; block <= blocks * n; block+=n) { 
		for (int i = 0; i < n; i++) { 
			int j = (((a*i + b)%n)+n)%n;
			// printf("block: %d, i: %d, j: %d\n", block, i, j);
			putchar(string[j + block - n]);
		}
	}
	free(string);

	return 0;
}
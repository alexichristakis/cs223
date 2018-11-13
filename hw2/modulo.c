#include <stdio.h>
#include <stdlib.h>

int main() {

	int n = 5;
	int a = -2;
	int b = -3;
	for (int i = 0; i < n; i++) {
		printf("(%d * %d + %d) mod %d = %d\n", a, i, b, n, (((a*i + b)%n)+n)%n);
	}

	n = 5;
	a = 3;
	b = 2;
	for (int i = 0; i < n; i++) {
		printf("(%d * %d + %d) mod %d = %d\n", a, i, b, n, (((a*i + b)%n)+n)%n);
	}



}
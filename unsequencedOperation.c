#include <stdio.h>

int main() {
	int a[] = {10, 20, 30};

	int i = 0;
	int r = 1 * a[i++] + 2 * a[i++] + 3 * a[i++];

	printf("result is %d, index is %d\n", r, i);

	return 0;
}

/**
 * Mac OS X, clang, warning generated, result r = 140, i = 3
 * Windows, gcc, result r = 60, i = 3
 */
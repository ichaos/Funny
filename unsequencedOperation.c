#include <stdio.h>

int main() {
	int a[] = {10, 20, 30};

	int i = 0;
	int r = 1 * a[i++] + 2 * a[i++] + 3 * a[i++];

	printf("result is %d\n", r);

	return 0;
}
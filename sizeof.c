#include <stdio.h>

#define my_size(x) ((char *)(&x + 1) - (char *)&x)

struct A {
	int a;
	char b;
};

int main() {
	struct A a;
	printf("sizeof (struct A): %d:%d\n", my_size(a), sizeof(struct A));
	printf("sizeof 1 : %d\n", sizeof(1));

	int i = 42;
	double dd = 4.2;
	double ee = 4.3;

	printf("double is %f, int is %d, double is %f\n", i, dd, ee);
	return 0;
}
#include <iostream>

struct ABC {
		#define SIZE 128
	int a, b, c;
};

int foo() {
	
	int aa = SIZE;
	return aa;
}

int main() {
	enum e1 {dark, white};
	enum e2 {a = 3, b =9};
	
	enum e3 {min = -1, max = 1000000};
	
	e3 v31 = e3(-100);
	e2 v21 = e2(17);
	
	std::cout << SIZE << std::endl;
	

	
	struct ABC abc;
}

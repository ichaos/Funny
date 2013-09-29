#include <iostream>

using namespace std;

int abc () {
        int b = 2 * 8 + 1;
        return b;
}

int main() {
        cout << "function abc @ " << abc << endl;

        printf("function abc @ %p\n", abc);

        return 0;
}

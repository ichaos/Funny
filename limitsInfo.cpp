/*
 * Try to print kinds of limits of C++ integral types on your machine
 */

#include <limits>
#include <iostream>

int main() {
	/*
	 * Int
	 */
	 std::cout << "The largest int is: " << std::numeric_limits<int>::max() << " 0x" << std::hex << std::numeric_limits<int>::max() << "\n";
	 std::cout << "The largest float is: " << std::dec << std::numeric_limits<float>::max() << " 0x" << std::hex << std::numeric_limits<float>::max() << "\n";
	 std::cout << "The plain char is signed: " << std::dec << std::numeric_limits<char>::is_signed << "\n";
} 

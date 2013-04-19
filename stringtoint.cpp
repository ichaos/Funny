#include <iostream>
#include <sstream>

using namespace std;

int main() {
	string date = "02/12";
	stringstream ss(date);
	int month, day;
	char c;
	ss >> month >> c >> day;
	
	cout << "month: " << month << "and day: " << day;
	
	return 0;
}

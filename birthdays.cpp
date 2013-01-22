#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Birthday {
public:
	Birthday();
	string getNext(string date, vector<string> birthdays);
	
private:

	int dateToDays(int month, int day);
};

Birthday::Birthday(){

 };

int Birthday::dateToDays(int month, int day) {
	static int daysOfMonth[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
	return daysOfMonth[month] + day;
}

string Birthday::getNext(string date, vector<string> birthdays) {
	int month, day;
	char c;
	stringstream ss(date);
	ss >> month >> c >> day;
	int today = dateToDays(month, day);
	int days = 0;
	int distance = 366, index = 0;
	int newdistance = 0;
	for (int i = 0; i < birthdays.size(); i++) {
		stringstream ss(birthdays[i]);
		ss >> month >> c >> day;
		days = dateToDays(month, day);
		if (days >= today)
			newdistance = days - today;
		else
			newdistance = (days - today) + 365;
		if (newdistance < distance) {
			distance = newdistance;
			index = i;
		}
	}
	return birthdays[index].substr(0, 5);
}

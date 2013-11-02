#include <sstream>
#include <string>
#include <math.h>
#include <iostream>
using namespace std;

class LotteryCheating {
public:
LotteryCheating();
int minimalChange(string ID);
int minimalChange2(string ID);
private:
int fnsn(long long n, int digits);
int iSquare(long long m);
};

LotteryCheating::LotteryCheating(){
}

int LotteryCheating::iSquare(long long m) {
	long long sqr = sqrt(m);
	if (sqr * sqr == m)
		return 1;
	else
		return 0;
}

//find nesrest square number,
//digits -- the least digits number we can modify, must be positive
//       -- in this problem, it should be less than 5
//       -- possible value 1,2,3,4
int LotteryCheating::fnsn(long long n, int digits) {
	//try to modify just one digits
	long long m = 0;
	for (int i = 9; i > digits; i--) {
		long long pca = 1;
		for (int j = 0; j < i; j++)
			pca = pca * 10;
		for (int j = 0; j < 10; j++) {
			m = (n % pca) + j * pca; 
			if (m == n)
				continue;
			if (iSquare(m))
				return 1;
		}
	}
	
	return 10;
}

int LotteryCheating::minimalChange2(string ID) {
	istringstream buffer(ID);
	long long value;
	buffer >> value; 
	
	if (value == 0)
		return 0;
		
	long long sqr = sqrt(value);
	cout << sqr << "\n" << sqr * sqr << "\n";
	if (sqr * sqr == value) //odd divisors
		return 0;
		
	//find the minimal change
	int mc = 0;
	long long neighbour = sqr * sqr;
	long long nt = neighbour, vt = value;
	while (vt != 0) {
		if (nt % 10 != vt % 10)
			mc++;
		nt = nt / 10; vt = vt / 10;
	}
	
	int ret = mc;
	mc = 0;
	neighbour = (sqr + 1) * (sqr + 1);
	nt = neighbour, vt = value;
	while (nt != 0)  {//nt >= vt
		if (nt % 10 != vt % 10)
			mc++;
		nt = nt / 10; vt = vt / 10;
	}
	if (mc < ret)
		ret = mc;
	vt = value;
	mc = 0;
	while (vt != 0) {
		if (vt % 10 != 0)
			mc++;
		vt = vt / 10;
	}
	if (mc < ret)
		ret = mc;
		
	if (ret > 1) {
		mc = fnsn(value, ret - 1);
		if (mc < ret)
			ret = mc;
	}	
	return ret;
}

int LotteryCheating::minimalChange(string ID) {
	istringstream buffer(ID);
	long long value;
	buffer >> value; 
	
	if (value == 0)
		return 0;
		
	long sqr = sqrt(value);
	cout << sqr << "\n" << sqr * sqr << "\n";
	if (sqr * sqr == value) //odd divisors
		return 0;
		
	//find the minimal change
	int mc = 0;
	long long neighbour = sqr * sqr;
	long long nt = neighbour, vt = value;
	while (vt != 0) {
		if (nt % 10 != vt % 10)
			mc++;
		nt = nt / 10; vt = vt / 10;
	}
	
	int ret = mc;
	mc = 0;
	neighbour = (sqr + 1) * (sqr + 1);
	nt = neighbour, vt = value;
	while (nt != 0)  {//nt >= vt
		if (nt % 10 != vt % 10)
			mc++;
		nt = nt / 10; vt = vt / 10;
	}
	if (mc < ret)
		ret = mc;
	vt = value;
	mc = 0;
	while (vt != 0) {
		if (vt % 10 != 0)
			mc++;
		vt = vt / 10;
	}
	if (mc < ret)
		ret = mc;
	return ret;
}

int main()
{
	LotteryCheating lc;
	int ret = lc.minimalChange2("7654321"); 
	cout << ret;
}

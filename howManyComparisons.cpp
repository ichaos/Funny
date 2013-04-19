#include <vector>
#include <iostream>

using namespace std;

class MergeSort {
	public:
		int howManyComparisons(vector<int> numbers) {
			int *array = new int[numbers.size()];

			for (int i = 0; i < numbers.size(); i++) {
				array[i] = numbers[i];
				//cout << array[i];				
			}
			//cout << "--\n"; 
			
			int cmp =  mergeSort(array, 0, numbers.size() - 1);
			/*
			for (int i = 0; i < numbers.size(); i++)
				cout << array[i];
			cout << "\n";
			*/
			delete array;
			return cmp;
		}

	private:
		int merge(int *array, int p, int q, int r) {
			int cmp = 0;
			//int copy[q - p + 1] = {0};
			int *copy = new int[q - p + 1];
			for (int i = 0; i < q - p + 1; i++) {
				copy[i] = array[i + p];
			}

			int i = 0; int j = q + 1;
			int k = p;
			while (i < q - p + 1 && j <= r) {
				cmp++;
				if (copy[i] < array[j]) {
					array[k++] = copy[i++];
				} else if (copy[i] > array[j]) {
					array[k++] = array[j++];
				} else {
					array[k++] = array[j++];
					array[k++] = array[i++];
				}
			}
			while (i < q - p + 1) {
				array[k++] = copy[i++];
			} 
			delete copy;
			return cmp;
		}
		int mergeSort(int *array, int p, int r) {
			if (p < r) {
				int q = (p + r - 1) / 2;
				return mergeSort(array, p, q) + mergeSort(array, q + 1, r) + merge(array, p, q, r);
			}

			return 0;
		}
};

int main() {
	MergeSort ms;
	int test [] = { 1, 2, 3, 4 };
	std::vector<int> v;
	//v.insert(v.begin(), test, test + 4);
	v.push_back(2);
	v.push_back(3);
	v.push_back(2);
	//v.push_back(4);
	//v.push_back(5); 
	cout << "comarisons time: " << ms.howManyComparisons(v);
	return 0;
}

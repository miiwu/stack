
#include"stack.hpp"
#include "vector"
#include "iostream"
#include "map"


using namespace std;

int main() {

	vector<int> list;
	
	for (int i = 0; i < 100; i++) {
		list.push_back(i);
	}

	int* ptr = list.data();

	for (int i = 0; i < 100; i++) {
		cout << *(ptr + i) << endl;
	}
}
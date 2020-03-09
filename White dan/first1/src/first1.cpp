//============================================================================
// Name        : first1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> zero_one;
	if(N !=0){
		while (N >=1){
			if (N % 2 == 0) {
				N = N/2;
				zero_one.push_back(0);
			}else {
				N = N/2;
				zero_one.push_back(1);
			}
		}

		for (int i = 0; i < zero_one.size(); ++i)
		{
			cout<< zero_one[zero_one.size() - i-1];
		}
	}
	else cout<< 0;

	return 0;
}

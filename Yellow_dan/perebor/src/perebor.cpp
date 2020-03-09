//============================================================================
// Name        : perebor.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

void printvec(const vector<int>& v){
	bool f = false;
	for(const int& i: v){
		if (!f){
			cout<< i;
			f = true;
			continue;
		}
		cout << " " << i;
	}
	cout << endl;
}

int main() {
	int N;
	cin >> N;
	vector<int> vec;
	for (int i = 0; i<N; ++i){
		vec.push_back(N-i);
	}
	do {
	    printvec(vec);
	} while(prev_permutation(vec.begin(), vec.end()));
	return 0;
}


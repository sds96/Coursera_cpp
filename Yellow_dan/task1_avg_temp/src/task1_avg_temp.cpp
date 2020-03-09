//============================================================================
// Name        : task1_avg_temp.cpp
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
	vector<int> temps;
	int64_t avg=0;
	for (size_t i=0; i<N; i++){
		int t;
		cin >> t;
		temps.push_back(t);
		avg+=t;
	}
	avg = avg/N;
	int k=0;
	for (size_t i = 0; i <temps.size(); ++i){
		if (temps[i]>avg)
			++k;
	}
	cout << k << endl;
	for (size_t i = 0; i <temps.size(); ++i){
		if (temps[i]>avg)
			cout << i <<" ";
	}

	return 0;
}

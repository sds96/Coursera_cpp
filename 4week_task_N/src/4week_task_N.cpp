//============================================================================
// Name        : 4week_task_N.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main() {
	ifstream input("input.txt");
	cout << fixed << setprecision(3);
	string line;
	double num;
	while(getline(input, line)){
		num = stod(line);
		cout << num <<endl;
	}


	return 0;
}

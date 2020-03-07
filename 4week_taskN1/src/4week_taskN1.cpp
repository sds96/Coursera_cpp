//============================================================================
// Name        : 4week_taskN1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	ifstream input("input.txt");
		int line;
		int x, y, tmp = 0;
		input >> x >> y;
		input.ignore(1);
		for (auto i = 0; i < x * y; ++i) {
		    if (tmp < x) {
		    	input >> line;
		    	input.ignore(1);
		    	cout << setw(10) << line << " ";
		    	tmp++;
		    } else if (tmp == x && i != x * y - 1){
			    input >> line;
			    input.ignore(1);
			    cout << setw(10) << line << endl;
			    tmp = 0;
			} else {
			    input >> line;
			    input.ignore(1);
			    cout << setw(10) << line;
		    }
		}

	return 0;
}

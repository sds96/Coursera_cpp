//============================================================================
// Name        : 4week_task_try2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
	string f_name, l_name;
	int day, month, year;
};


int main() {
	int Nstud, Nreq;
	cin >> Nstud;
	vector<Student> studs;
	Student Stmp;
	for (int i = 0; i<Nstud; ++i){
		cin >> Stmp.f_name >> Stmp.l_name >> Stmp.day >> Stmp.month >> Stmp.year;
		studs.push_back(Stmp);
	}
	cin >> Nreq;
	for (int i = 0; i<Nreq; ++i){
		string type_req;
		int num;
		cin>> type_req >> num;
		if(type_req == "name" && (num <= Nstud && num > 0)){
			cout << studs[num-1].f_name << " " << studs[num-1].l_name << endl;
		} else if (type_req == "date" && (num <= Nstud && num > 0)){
			cout << studs[num-1].day << "." << studs[num-1].month << "." << studs[num-1].year << endl;
		} else cout << "bad request" << endl;
	}
	return 0;
}

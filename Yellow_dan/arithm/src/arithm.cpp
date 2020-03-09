//============================================================================
// Name        : arithm.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <deque>

using namespace std;

void addline(deque<string> &d, char c, int num){
	d.push_back(" ");
	d.push_back(string(1,c));
	d.push_back(" ");
	d.push_back(to_string(num));
};

void bracket(deque<string>& d){
	d.push_back(")");
	d.push_front("(");
}

int main() {
	deque<string> d;
	int x;
	cin >> x;
	d.push_back(to_string(x));
	int N;
	cin >> N;
	char oper('*');
	for (int i=0; i<N; ++i){
		char new_oper;
		int num;
		cin >> new_oper >> num;
		if ((new_oper == '*' || new_oper == '/') &&
				(oper == '+' || oper == '-'))
			bracket(d);
		addline(d, new_oper, num);
		oper = new_oper;
	}
	for(const auto& el:d){
		cout<< el;
	}
	return 0;
}

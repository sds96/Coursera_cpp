//============================================================================
// Name        : second_week3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
	int Q;
	cin>> Q;
	string request;
	map<string, vector<string>> buses;
	map<string, vector<string>> stops;

	for (int qi=0; qi < Q; ++qi){
		cin >> request;
		if (request == "NEW_BUS"){
			string bus;
			int stop_count;
			cin >> bus >> stop_count;
			for (int i=0; i<stop_count; ++i){
				string stop;
				cin >> stop;
				buses[bus].push_back(stop);
			}
			for (const auto& j: buses[bus]){
				stops[j].push_back(bus);
			}

		}
		if (request == "BUSES_FOR_STOP"){
			string stop;
			bool flag = false;
			cin>> stop;
			for (const auto& i: stops){
				if (i.first == stop){
					for (const auto& j:i.second)
						cout << j <<" ";
					flag = true;
				}
			}
			if (!flag) cout << "No stop";
			cout << endl;

			/*
			for (const auto& i : buses){
				for(const auto& j : i.second){
					if (j == stop){
						cout << i.first<< " ";
						flag = true;
					}
				}
			}

			cout << endl; */
		}
		if (request == "STOPS_FOR_BUS"){
			string bus;
			cin >> bus;
			if (buses.count(bus) == 0)
				cout << "No bus" << endl;
			else {
				for(const auto& i : buses[bus]){
					cout<< "Stop " << i <<": ";
					bool no_another_bus = true;
					for (const auto& k : stops[i]){
						if (k == bus) continue;
						else {
							cout << k << " ";
							no_another_bus = false;
						}

					}
					if(no_another_bus) cout << "no interchange";
					cout << endl;
				}
			}
		}
		if(request == "ALL_BUSES"){
			if (buses.empty()) cout << "No buses" <<endl;
			else {
				for (const auto& i : buses){
					cout << "Bus " << i.first << ": ";
					for(const auto& j : i.second){
						cout << j << " ";
					}
					cout << endl;
				}
			}
		}
	}
	return 0;
}

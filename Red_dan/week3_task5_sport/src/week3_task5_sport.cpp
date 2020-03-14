//============================================================================
// Name        : week3_task5_sport.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	list<int> players;
	vector<list<int>::iterator> positions(100001, players.end());
	int n;
	cin>>n;
	while(n>0){
		int player_num;
		int pos;
		cin >> player_num >> pos;
		positions[player_num] = players.insert(positions[pos],player_num);
		--n;
	}
	for(const auto& el: players){
		cout << el << " ";
	}

	return 0;
}

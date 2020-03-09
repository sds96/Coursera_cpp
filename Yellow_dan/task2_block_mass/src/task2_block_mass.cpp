//============================================================================
// Name        : task2_block_mass.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdint>
using namespace std;

int main() {
	int N;
	unsigned int Ro;
	cin >> N >> Ro;
	uint64_t total=0;
	uint64_t W,H,D;
	for (int i=0; i<N; ++i){
		cin >> W >> H >> D;
		total += W*H*D*Ro;
	}
	cout << total;
	return 0;
}

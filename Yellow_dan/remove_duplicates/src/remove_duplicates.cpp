//============================================================================
// Name        : remove_duplicates.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements){
	sort(elements.begin(), elements.end());
	auto it = unique(elements.begin(),elements.end());
	elements.erase(it, elements.end());
}

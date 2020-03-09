//============================================================================
// Name        : merge_sort.cpp
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

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	int len = range_end - range_begin;
	if (len < 2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto first = elements.begin() + len/3;
	auto second = elements.begin() + 2* len/3;
	MergeSort(elements.begin(), first);
	MergeSort(first, second);
	MergeSort(second, elements.end());
	vector<typename RandomIt::value_type> temp;
	merge(elements.begin(), first, first, second, back_inserter(temp));
	merge(temp.begin(), temp.end(), second, elements.end(), range_begin);
}
/*
int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 9};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
*/

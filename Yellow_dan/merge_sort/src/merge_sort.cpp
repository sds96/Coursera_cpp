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

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	int len = range_end - range_begin;
	if (len < 2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto middle = elements.begin() + len/2;
	MergeSort(elements.begin(), middle);
	MergeSort(middle, elements.end());

	merge(elements.begin(), middle, middle, elements.end(), range_begin);
	//inplace_merge(range_begin, middle, range_end);
}
/*
int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
*/

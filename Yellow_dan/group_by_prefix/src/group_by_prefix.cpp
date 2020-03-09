//============================================================================
// Name        : group_by_prefix.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
	const string& prefix){
    string newPrefix = prefix;
    if (!prefix.empty()) *prev(newPrefix.end()) = static_cast<char>(*prev(newPrefix.end()) + 1);
    auto beg = lower_bound(range_begin,range_end,prefix);
    auto end = lower_bound(range_begin,range_end,newPrefix);
    return make_pair(beg,end);

}
/*
int main() {
  const vector<string> sorted_strings = {"m","mn", "mo","moscow", "motovilikha", "mp" ,"murmansk"};
  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  cout << (mo_result.first - begin(sorted_strings)) << " " <<
      (mo_result.second - begin(sorted_strings)) << endl;
  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  return 0;
  }
*/

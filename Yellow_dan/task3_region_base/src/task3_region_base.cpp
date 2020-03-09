//============================================================================
// Name        : task3_region_base.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
using namespace std;
/*
enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
*/
bool operator<(const Region& lhs, const Region& rhs){
	auto t1 = make_tuple(lhs.std_name, lhs.parent_std_name,
					lhs.names, lhs.population);
	auto t2 = make_tuple(rhs.std_name, rhs.parent_std_name,
						rhs.names, rhs.population);
	return t1<t2;
}
int FindMaxRepetitionCount(const vector<Region>& regions){
	int n = 1;

	if (regions.empty())
		return 0;

	map<Region,int> regcount;
	for (const auto& elem:regions){
		regcount[elem]++;
	}
	/*
	for (const auto& elem:regions){

	}
	for (size_t i = 0; i< regions.size(); ++i){
		int m = 0;
		auto t1 = make_tuple(regions[i].std_name, regions[i].parent_std_name,
				regions[i].names, regions[i].population);
		for (size_t j = i; j < regions.size(); ++j){
			auto t2 = make_tuple(regions[j].std_name, regions[j].parent_std_name,
					regions[j].names, regions[j].population);
			if (t1 == t2) ++m;
		}
		if (m>n) n =m;
	}*/
	for (const auto& elem: regcount){
		if( elem.second > n) n = elem.second;
	}
	return n;
};
/*
int main() {
	cout << FindMaxRepetitionCount({
	      {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      },
	  }) << endl;

	  cout << FindMaxRepetitionCount({
	      {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Toulouse",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          31
	      },
	  }) << endl;

	  return 0;
}

*/

//============================================================================
// Name        : Second_week.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsPalindrom(string s) {
    for (size_t i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

vector<string> PalindromFilter (vector<string> words, int minLength){
	vector<string> new_words;
	for (auto i: words){
		if(i.size() >= minLength && IsPalindrom(i)) new_words.push_back(i);
	}
	return new_words;
}

int main() {
	vector<string> kek = PalindromFilter({"weew", "bro", "code"}, 4);
	for (auto i : kek) cout << i << " ";
	return 0;
}

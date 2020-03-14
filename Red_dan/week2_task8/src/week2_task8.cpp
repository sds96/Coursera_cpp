//============================================================================
// Name        : week2_task8.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "learner.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}

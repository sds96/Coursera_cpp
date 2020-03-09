// Example program
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> str;
    ifstream input("input.txt");
    if (input){
        string str_temp;
        while (getline(input, str_temp)){
            str.push_back(str_temp);
            }
    }
    ofstream output("output.txt");
    for (const auto& i: str)
        output << i << endl;
        
    
    return 0;
    }
// Example program
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    
    ifstream input("input.txt");
    if (input){
        string str;
        while (getline(input, str)){
            cout << str << endl;
            } 
        }
    
    return 0;
    }
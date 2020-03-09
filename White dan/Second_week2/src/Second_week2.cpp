//============================================================================
// Name        : Second_week2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// Example program
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
int N;
cin >> N;
string command;
string country;
string new_capital;
map<string, string> STRANI;



for (int i = 0; i<N; ++i){
    cin>> command;
    if(command == "CHANGE_CAPITAL"){
        cin>> country >> new_capital;
        if(STRANI.count(country) == 0){
        	STRANI[country] = new_capital;
        	cout << "Introduce new country " << country << " with capital "<<STRANI[country] <<endl;
        	}
        else if (STRANI[country] == new_capital) cout<< "Country " << country <<" hasn't changed its capital" <<endl;
        else {
        	cout<< "Country " << country <<" has changed its capital from " << STRANI[country] <<" to "<< new_capital <<endl;
        	STRANI[country] = new_capital;
        }
    }

    if(command == "RENAME"){
    	string new_country_name;
    	cin >> country >> new_country_name;
    	if (STRANI.count(country) == 0 || STRANI.count(new_country_name) == 1 || (country == new_country_name))
    		cout << "Incorrect rename, skip" << endl;
    	else{
    		STRANI[new_country_name] = STRANI[country];
    		STRANI.erase(country);
    		cout << "Country " << country <<" with capital " << STRANI[new_country_name]
				 << " has been renamed to " << new_country_name << endl;
    	}
    }
    if(command == "ABOUT"){
    	cin >> country;
    	if(STRANI.count(country) == 0)
    		cout << "Country " << country <<" doesn't exist" <<endl;
    	else
    		cout << "Country " << country << " has capital " << STRANI[country] <<endl;
    }
    if(command == "DUMP"){
    	if (STRANI.empty())
    		cout << "There are no countries in the world" <<endl;
    	else
    		for (auto it: STRANI)
    			cout << it.first <<"/" <<it.second <<endl;
    }
}
return 0;
}


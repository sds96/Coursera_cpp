#include <iostream>

using namespace std;

class Animal {
public:
	Animal(const string& str)
	: Name(str){

	}
    const string Name;
};


class Dog: public Animal {
public:
    Dog(const string& str)
	: Animal(str){

    }
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

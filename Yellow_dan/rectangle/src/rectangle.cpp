//============================================================================
// Name        : rectangle.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Rectangle {
public:
    Rectangle(int width, int height) : width_(width), height_(height)
    {
    }

    int GetArea() const {
        return width_ * height_;
    }

    int GetPerimeter() const {
        return 2 * (width_ + height_);
    }

    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }

private:
    int width_, height_;
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

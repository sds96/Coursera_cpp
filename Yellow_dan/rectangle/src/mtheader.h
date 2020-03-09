/*
 * mtheader.h
 *
 *  Created on: 9 окт. 2019 г.
 *      Author: ƒмитрий
 */

#pragma once

class Rectangle{
public:
	Rectangle(int width, int height);
    int GetArea() const;
    int GetPerimeter() const;
    int GetWidth() const;
    int GetHeight() const;
private:
 int width_, height_;
    };

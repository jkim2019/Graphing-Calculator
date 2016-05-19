// File name: Point.cpp
// Author: John Kim
// Email: john.j.kim@vanderbilt.edu
// Description: Definitions of classes in "Point.hpp"
// Last Changed: 05/15/16

#include "Point.hpp"


#include <iostream>
using namespace std;

// default ctor
Point::Point() :
    x(0),
    y(0),
    ch(' ')
{
    // nothing to do
}

// alternate ctor
// pre: int x1, y1
// post: Point created at (x1, y1)
Point::Point(double x1, double y1) :
    x(x1),
    y(y1)
{
    if (x == 0 && y == 0) {
        ch = 'o';
    }
    else {
        ch = ' ';
    }
}

// fillPoint
// post: ch set to x if at origin, else *
void Point::fillPoint()
{
    if (x == 0 && y == 0) {
        ch = 'x';
    }
    else {
        ch = '*';
    }
}

// emptyPoint
// post: ch set to ' '
void Point::emptyPoint() {
    ch = ' ';
}

// getCh
// post: returns ch
char Point::getCh() const {
    return ch;
}

// getX
// post: returns x coordinate of point
int Point::getX() const {
    return x;
}

// getY
// post: returns y coordinate of point
int Point::getY() const {
    return y;
}

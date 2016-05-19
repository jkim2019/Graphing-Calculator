// File name: Point.cpp
// Author: John Kim
// Email: john.j.kim@vanderbilt.edu
// Description: Point object. Each point contains double x,y denoting a coordinate (x,y)
// and a char, holding either ' ' or '*', representing an empty and filled point, respectively
// Last Changed: 05/15/16

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>

class Point {
private:
    // (x,y) coordinate
    double x, y;
    char ch;
public :
    // default ctor
    Point();
    
    // alternate ctor
    // pre: int x1, y1
    // post: Point created at (x1, y1)
    Point(double x1, double y1);
    
    // fillPoint
    // post: ch set to x if at origin, else *
    void fillPoint();
    
    // emptyPoint
    // post: ch set to ' '
    void emptyPoint();
    
    // getCh
    // post: returns ch
    char getCh() const;
    
    // getX
    // post: returns x coordinate of point
    int getX() const;
    
    // getY
    // post: returns y coordinate of point
    int getY() const;
};


#endif /* Point_hpp */

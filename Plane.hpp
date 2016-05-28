// File name: Plane.hpp
// Author: John Kim
// Email: john.j.kim@vanderbilt.edu
// Description: Plane recreates a Cartesian plane. The origin is at (0,0). It can hold integers
// x and y, representing the ordered pair (x, y). An empty point is represented by a ' ', while a
// filled point is represented by a '*'. x_length and y_length are the lengths of the positive x and y axes,
// while xDim and yDim represent the window size of the graph, equivalently (2*x_length + 1) or (2*y_length + 1)
// Last Changed: 05/15/16

#ifndef Plane_hpp
#define Plane_hpp

#include <stdio.h>
#include <string>
#include "Point.hpp"

// Plane recreates a Cartesian plane. The origin is at (0,0). It can hold negative and positive integers for
// x and y (x, y). An empty point is represented by a ' ', while a filled point is represented by a *
// origin is located at (0,0)
// x_length and y_length are the lengths of the positive x and y axes

class Plane {
private:
    size_t x_length, y_length;
    Point **myPlane;
    size_t X_SAMPLES_PER_UNIT;
    size_t Y_SAMPLES_PER_UNIT;
    int xIndices;
    int yIndices;
public:
    
    // default ctor
    // creates a 0 by 0 dimensional Plane
    // pre: obj doesn't exist
    // post: obj exists
    Plane();
    
    // alternate ctor
    // creates an n by n dimensional Plane
    // pre: obj doesn't exist
    // post: n by n Plane exists. All positions are occupied by a ' ', denoting an empty Point
    Plane(size_t x, size_t y, size_t x_samples, size_t y_samples);
    
    // copy ctor
    // copies Plane rhs to new obj
    Plane(const Plane &rhs);
    
    // destructor
    ~Plane();
    
    // assignment operator
    // assigns rhs to this Plane
    const Plane& operator= (const Plane& rhs);
    
    // isEmpty
    // pre: Point is within dimensions of Plane
    // post: returns true if (x,y) contains a Point, else false
    bool isEmpty(int x, int y);
    
    // isEmpty overloaded function
    // pre: Point is within dimensions of Plane
    // post: return strue if Point is filled, else false
    bool isEmpty(Point point);
    
    // addPoint
    // post: adds Point to Plane, if it didn't already exist
    void addPoint(double x, double y);
    
    // addPoint overloaded function
    // pre: Point contains x and y are nonnegative
    // post: Point added to Plane, if it doesn't already exist
    void addPoint(Point point);
    
    // getPoint
    // post: returns Point at x and y. If Point doesn't exist, returns Point(-1, -1)
    Point getPoint(int x, int y);
    
    // distance
    // pre: Points exist
    // post: Returns distance between two points. Throws exception if both points do not exist
    double distance(Point start, Point end);
    
    // getXLength
    // post: returns length of positive x axis
    size_t getXLength() const;
    
    // getYLength
    // post: returns length of positive y axis
    size_t getYLength() const;
    
    // getXSample
    // post: returns X_SAMPLES_PER_UNIT
    size_t getXSample() const;
    
    // getYSample
    // post: returns Y_SAMPLES_PER_UNIT
    size_t getYSample() const;
    
    // print for polynomials
    // post: prints plane
    void print(std::string filename, std::string polynomial);
    
    // print for parametric
    // post: prints plane
    void print(std::string filename, std::string xParam, std::string yParam, double tStart, double tEnd);
    
    // inPlane overloaded function
    bool inPlane(double x, double y);
    
    // toCor helper function
    // pre: index >= 0, axis is either 'x' or 'y'
    // post: returns value of index transferred to coordinate
    double toCor(size_t index, char axis);
    
    // toIndex helper function
    // pre: value within Plane, axis is either 'x' or 'y'
    // post: returns index value equivalent
    int toIndex(double cor, char axis);
    
};


#endif /* Plane_hpp */

// File name: Plane.cpp
// Author: John Kim
// Email: john.j.kim@vanderbilt.edu
// Description: Definitions of classes in "Plane.hpp"
// Last Changed: 05/15/16

#include "Plane.hpp"
#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <cmath>

using namespace std;


// default ctor
// creates a 0 by 0 dimensional Plane
// pre: obj doesn't exist
// post: obj exists
Plane::Plane() :
x_length(0),
y_length(0),
X_SAMPLES_PER_UNIT(1),
Y_SAMPLES_PER_UNIT(1)
{
    myPlane = nullptr;
}


// alternate ctor
// creates an n by n dimensional Plane
// pre: obj doesn't exist
// post: n by n Plane exists. All positions are occupied by a ' ', denoting an empty Point
Plane::Plane(size_t x, size_t y, size_t x_samples, size_t y_samples) :
x_length(x),
y_length(y),
X_SAMPLES_PER_UNIT(x_samples),
Y_SAMPLES_PER_UNIT(y_samples),
xIndices(2*int(x*x_samples) + 1),
yIndices(2*int(y*y_samples) + 1)
{
    
    // create two dimensional myPlane
    // Since x and y denote the length of the positive x and y axes, myPlane must be of size
    // 2x+1 and 2y+1 to account for the negative x and y axes and the origin
    myPlane = new Point*[yIndices];
    for (size_t yCount = 0; yCount < yIndices; yCount++) {
        myPlane[yCount] = new Point[xIndices];
        for (size_t xCount = 0; xCount < xIndices; xCount++) {
            myPlane[yCount][xCount] = *new Point(toCor(xCount, 'x'), toCor(yCount, 'y'));
        }
    }
    
}


// copy ctor
// copies Plane rhs to new obj
Plane::Plane(const Plane &rhs) :
x_length(rhs.x_length),
y_length(rhs.y_length)
{
    // if rhs is empty, set myPlane to nullptr
    if (rhs.myPlane == nullptr) {
        myPlane = nullptr;
    }
    else {
        myPlane = new Point*[yIndices];
        for (size_t yCor = 0; yCor < yIndices; yCor++) {
            myPlane[yCor] = new Point[xIndices];
            for (size_t xCor = 0; xCor < xIndices; xCor++) {
                // copy all Points from rhs.myPlane to myPlane
                myPlane[yCor][xCor] = rhs.myPlane[yCor][xCor];
            }
        }
    }
}


// destructor
Plane::~Plane() {
    for (size_t yCount = 0; yCount < yIndices; yCount++) {
        delete[] myPlane[yCount];
    }
    delete[] myPlane;
    myPlane = nullptr;
}


// assignment operator
// assigns rhs to this Plane
const Plane& Plane::operator= (const Plane& rhs) {
    // check for self assignment
    if (this != &rhs) {
        // call copy ctor and swap all private variables
        Plane temp(rhs);
        std::swap(myPlane, temp.myPlane);
        std::swap(x_length, temp.x_length);
        std::swap(y_length, temp.y_length);
        std::swap(yIndices, temp.yIndices);
        std::swap(xIndices, temp.xIndices);
    }
    return *this;
}


// isEmpty
// pre: Point is within dimensions of Plane
// post: returns true if (x,y) contains a Point, else false
bool Plane::isEmpty(int x, int y) {
    if (myPlane[toIndex(y, 'y')][toIndex(x, 'x')].getCh() == ' ') {
        return true;
    }
    return false;
}


// isEmpty overloaded function
// pre: Point is within dimensions of Plane
// post: returns true if Point is filled, else false
bool Plane::isEmpty(Point point) {
    if (myPlane[toIndex(point.getY(), 'y')][toIndex(point.getX(), 'x')].getCh() == ' ') {
        return true;
    }
    return false;
}


// addPoint
// post: adds Point to Plane, if it didn't already exist
void Plane::addPoint(double x, double y) {
    if (!inPlane(x, y)) {
        // do nothing
    }
    else {
        myPlane[toIndex(y, 'y')][toIndex(x, 'x')].fillPoint();
    }
}


// getPoint
// post: returns Point at x and y. If Point doesn't exist, returns Point(-1, -1)
Point Plane::getPoint(int x, int y) {
    return myPlane[toIndex(y, 'y')][toIndex(x, 'x')];
}


// getXLength
// post: returns length of positive x axis
size_t Plane::getXLength() const {
    return x_length;
}


// getYLength
// post: returns length of positive y axis
size_t Plane::getYLength() const {
    return y_length;
}


// getXSample
// post: returns X_SAMPLES_PER_UNIT
size_t Plane::getXSample() const {
    return X_SAMPLES_PER_UNIT;
}


// getYSample
// post: returns Y_SAMPLES_PER_UNIT
size_t Plane::getYSample() const {
    return Y_SAMPLES_PER_UNIT;
}


// print
// post: prints plane, surrounded with '-' on top and bottom and '|' on sides
void Plane::print(string filename) {
    ofstream outfile;
    outfile.open(filename, ios::ate);
    
    // formatting...
    outfile << "X SCALE: 1 char = " << 1/double(X_SAMPLES_PER_UNIT) << "units." << endl;
    outfile << "Y SCALE: 1 char = " << 1/double(Y_SAMPLES_PER_UNIT) << "units." << endl;
    outfile << "Window: -" << x_length << " < x < " << x_length << " | -" << y_length << " < y < " << y_length << endl << endl;
    
    outfile << "╔";
    for (size_t topBorder = 0; topBorder < xIndices; topBorder++) {
        outfile << "═";
    }
    outfile << "╗\n";
    for (size_t yCol = 0; yCol < yIndices; yCol++) {
        outfile << "║";
        for (size_t xCol = 0; xCol < xIndices; xCol++) {
            outfile << myPlane[yCol][xCol].getCh();
        }
        outfile << "║" << endl;
    }
    outfile << "╚";
    for (size_t bottomBorder = 0; bottomBorder < xIndices; bottomBorder++) {
        outfile << "═";
    }
    outfile << "╝";
    
    outfile.close();
}


// inPlane overloaded function
bool Plane::inPlane(double x, double y) {
    if (toIndex(x, 'x') < 0 || toIndex(x, 'x') > xIndices || toIndex(y, 'y') < 0 || toIndex(y, 'y') > yIndices) {
        return false;
    }
    return true;
}


// toCor helper function
// pre: index >= 0, axis is either 'x' or 'y'
// post: returns value of index transferred to coordinate
double Plane::toCor(size_t index, char axis) {
    if (axis == 'x') {
        return -int(x_length) + double(index)/double(X_SAMPLES_PER_UNIT);
    }
    else if (axis == 'y') {
        return int(y_length) - double(index)/double(Y_SAMPLES_PER_UNIT);
    }
    else {
        throw std::invalid_argument("axis must be either 'x' or 'y'");
    }
}


// toIndex helper function
// pre: value within Plane, axis is either 'x' or 'y'
// post: returns index value equivalent
int Plane::toIndex(double cor, char axis) {
    if (axis != 'x' && axis != 'y') {
        throw std::invalid_argument("axis must be either 'x' or 'y'");
    }
    else if (axis == 'x') {
        return int(std::round(X_SAMPLES_PER_UNIT*cor)) + int(std::round(X_SAMPLES_PER_UNIT*x_length));
    }
    else {
        return int(std::round(Y_SAMPLES_PER_UNIT*y_length)) - int(std::round(Y_SAMPLES_PER_UNIT*cor));
    }
}





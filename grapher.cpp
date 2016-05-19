// File name: grapher.cpp
// Author: John Kim
// Email: john.j.kim@vanderbilt.edu
// Description: Definitions of classes in "Plane.hpp"
// Last Changed: 05/15/16

#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "Plane.hpp"
using namespace std;


// askLength
// prompt user to input x_length
// pre: axis is either 'x' or 'y'
// post: returns length
size_t askLength(const char& axis);

// parsePolynomial
// read polynomial as string and return value at a given xVal
// pre: polynomial in the form Ax^n+Bx^n-1+...+const
// post: return value at given xVal
double parsePolynomial(vector<string> polySplit, double xVal);

// split
// splits string by given value ch
// post: returns pointer to string array containing substrings of original string, split by ch
vector<string> split(string poly);

// hasPow
// post: returns whether str contains '^'
bool hasPow(string term);

// hasX
// post: returns whether str contins 'x'
bool hasX(string term);

// getExp
// pre: term hasPow
// post: returns exponent
int getExp(string term);

// getCoeff
// pre: has coefficient before x term
// post: returns coefficient, or 1 if no coefficient before x term
double getCoeff(string term, double xVal);


int main() {
    
    string outputFile;
    cout << "Enter the name of the output file: ";
    cin >> outputFile;
    cout << endl;
    
    cout << "It is recommended samples_per_unit*window_size <= 100" << endl;
    size_t xSamples, ySamples;
    cout << "X Samples Per Unit: ";
    cin >> xSamples;
    cout << "Y Samples Per Unit: ";
    cin >> ySamples;
    
    int xWindow, yWindow;
    
    cout << "Enter X window size (units): ";
    cin >> xWindow;
    cout << "Enter Y window size (units): ";
    cin >> yWindow;
    
    Plane graph(xWindow, yWindow, xSamples, ySamples);
    
    size_t funcType;
    
    cout << "\n\n1. Polynomial and/or Trigonometric\n2. Parametric" << endl;
    cout << "Enter the type of function you would like to graph (1 or 2): ";
    cin >> funcType;
    cout << "\n\n########################################################" << endl << "INPUT/OUTPUT GUIDELINES: \n1. Function must be of the form Ax^n+Bx^n-1+...\n2. Functions may contain trig functions\n3. Trig functions must be entered as, for example, sin(polynomial)\n4. Parametric functions would be parametrized in terms of x\n5. If combining polynomials and trig functions, trig functions take precedence\n\t\"sin(x^2)*(5x^3+3)\" should be inputted as sin(x^2)5x^3+3\n########################################################\n\n";
    std::cout << "\n\nPress ENTER to continue...";
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    
    switch (funcType) {
        case 1:
        {
            string polynomial;
            cout << "Enter the polynomial with no spaces: f(x) = ";
            cin >> polynomial;
            cout << endl;
            vector<string> polySplit = split(polynomial);
            for (double xVal = -xWindow; xVal <= xWindow; xVal = xVal + 1/double(graph.getXSample())) {
                double yVal = parsePolynomial(polySplit, xVal);
                graph.addPoint(xVal, yVal);
                cout << "(" << xVal << " , " << yVal << ")" << endl;
            }
            graph.print(outputFile);
            break;
        }
        case 2:
        {
            string xParametric, yParametric;
            double tStart, tEnd;
            cout << "a(x) = ";
            cin >> xParametric;
            cout << "b(x) = ";
            cin >> yParametric;
            cout << "Start t = ";
            cin >> tStart;
            cout << "End t = ";
            cin >> tEnd;
            cout << endl;
            vector<string> xParaSplit = split(xParametric);
            vector<string> yParaSplit = split(yParametric);
            for (double tVal = tStart; tVal <= tEnd; tVal = tVal + 1/double(graph.getXSample())) {
                double xtVal = parsePolynomial(xParaSplit , tVal);
                double ytVal = parsePolynomial(yParaSplit, tVal);
                graph.addPoint(xtVal, ytVal);
                cout << "(" << xtVal << " , " << ytVal << ")" << endl;
            }
            graph.print(outputFile);
            break;
        }
        default:
            cout << "Invalid Input" << endl;
            break;
    }
    std::cout << "\n\nPress ENTER to continue...";
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    cout << endl;
    return 0;
}


// askLength
// prompt user to input x_length
// pre: axis is either 'x' or 'y'
// post: returns length
size_t askLength(const char& axis) {
    cout << "Input " << axis << " length: ";
    size_t length;
    cin >> length;
    return length;
}


// parsePolynomial
// return value at a given xVal
// post: return value at given xVal
double parsePolynomial(vector<string> polySplit, double xVal) {
    double yVal = 0.0;
    for (vector<string>::iterator iter = polySplit.begin(); iter < polySplit.end(); iter++) {
        if (hasX(*iter)) {
            if (hasPow(*iter)) {
                yVal += getCoeff(*iter, xVal)*pow(xVal, getExp(*iter));
            }
            else {
                yVal += getCoeff(*iter, xVal)*xVal;
            }
        }
        // if function has power, but no X, check if trig function has power
        else if (hasPow(*iter)) {
            yVal += pow(getCoeff(*iter + "x", xVal), getExp(*iter));
        }
        else {
            // either trig function or constant
            bool isTrig = true;
            size_t count = 0;
            while (!isalpha((*iter)[count])) {
                count++;
                if (count == (*iter).length()) {
                    // is a constant
                    yVal += stod(*iter);
                    isTrig = false;
                }
            }
            if (isTrig) {
                // else trig function
                yVal += getCoeff(*iter + "x", xVal);
            }
        }
        
    }
    return yVal;
}


// split
// splits polynomial by char + or -. Ignores polynomials within trig functions
// post: returns pointer to string array containing each term of polynomial
vector<string> split(string poly) {
    vector<string> polySplit;
    string temp = "";
    bool isNeg = false;
    
    // add first term
    // we start at index 0 if the first term is positive, else we will start at index 1 and search
    // for first occurence of '+' or '-'
    size_t counter = size_t(poly[0] == '-');
    if (counter) {
        temp+= '-';
    }
    while (poly[counter] != '+' && poly[counter] != '-') {
        temp += poly[counter];
        counter++;
        
        if (poly[counter] == '(') {
            while (poly[counter] != ')') {
                temp += poly[counter];
                counter++;
            }
            // add last ')'
            temp += poly[counter];
            counter++;
        }
        // if polynomial has one term
        if (counter == poly.length()) {
            polySplit.push_back(temp);
            return polySplit;
        }
    }
    polySplit.push_back(temp);
    temp = "";
    
    // add middle terms
    for (size_t count = counter + 1; count < poly.length(); count++) {
        if (poly[count] == '+') {
            if (isNeg) {
                polySplit.push_back("-" + temp);
            }
            else {
                polySplit.push_back(temp);
            }
            temp = "";
        }
        else if (poly[count] == '-') {
            if (isNeg) {
                polySplit.push_back("-" + temp);
            }
            else {
                polySplit.push_back(temp);
            }
            isNeg = true;
            temp = "";
        }
        else {
            temp += poly[count];
        }
    }
    
    // add last term
    if (isNeg) {
        polySplit.push_back("-" + temp);
    }
    else {
        polySplit.push_back(temp);
    }
    
    return polySplit;
}


// hasPow
// post: returns whether str contains '^'. Does not include function inside a trig function
bool hasPow(string term) {
    size_t index = term.find(')');
    if (index == -1) { index = 0; }
    for (size_t count = index; count < term.length(); count++) {
        if (term[count] == '^') {
            return true;
        }
    }
    return false;
}


// hasX
// post: returns whether str contins 'x'; 'x' does not include occurrences within a trig function
bool hasX(string term) {
    size_t index = term.find(')');
    if (index == -1) { index = 0; }
    for (size_t count = index; count < term.length(); count++) {
        if (term[count] == 'x') {
            return true;
        }
    }
    return false;
}


// getExp
// pre: hasPow
// post: returns exponent, does not include polynomial in trig function. Returns -1 if not found (should not occur)
int getExp(string term) {
    size_t index = term.find(')');
    if (index == -1) { index = 0; }
    for (size_t count = index; count < term.length(); count++) {
        if (term[count] == '^') {
            return int(count + 1);
        }
    }
    return -1;
}


// getCoeff
// pre: has coefficient before x-term. Coefficient can include trig functions
// post: returns coefficient, or 1 if no coefficient before x term
double getCoeff(string term, double xVal) {
    // set index to end of trig function, if term contains one
    int index = (int)term.find(')');
    // if term contains no trig function, set it to zero
    if (index == -1) { index = 0; }
    
    double coeff;
    while (term[index] != 'x') {
        index++;
    }
    if (term.substr(0, index) == "") {
        return double(1);
    }
    else if (term.substr(0, index) == "-") {
        return double(-1);
    }
    else {
        // check if trig function
        if (term.find('c') == -1 && term.find('s') == -1 && term.find('t') == -1) {
            coeff = stod(term.substr(0, index));
        }
        else {
            // check for correct trig function. term will be of the form const*trig_function(poly)
            size_t trigIndex = 0;
            // ignore coefficient
            while (!isalpha(term[trigIndex])) {
                trigIndex++;
            }
            char ch = term[trigIndex];
            trigIndex += 4;
            // extract polynomial inside trig function
            string trigPoly = term.substr(trigIndex, index - trigIndex - 1);
            
            switch (ch) {
                case 's':
                {
                    coeff = getCoeff(term.substr(0, trigIndex - 4) + "x", xVal)*sin(parsePolynomial(split(trigPoly), xVal));
                    break;
                }
                case 'c':
                {
                    coeff = getCoeff(term.substr(0, trigIndex - 4) + "x", xVal)*cos(parsePolynomial(split(trigPoly), xVal));
                    break;
                }
                case 't':
                {
                    coeff = getCoeff(term.substr(0, trigIndex - 4) + "x", xVal)*tan(parsePolynomial(split(trigPoly), xVal));
                    break;
                }
                default :
                    cout << "Something went wrong..." << endl;
                    break;
            }
        }
    }
    return coeff;
}

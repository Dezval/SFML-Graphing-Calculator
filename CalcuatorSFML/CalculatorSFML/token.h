#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

using namespace std;

class Token                 //parents class to other classes
{
public:
    Token();                //zero parameter constructor
    virtual int GetType();  //returns the type
    int size();             //returns the zise
    virtual void Print();   //displays
    virtual string Data();  //returns data from the token
};

#endif // TOKEN_H

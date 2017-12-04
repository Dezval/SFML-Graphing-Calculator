#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include "token.h"
#include <string>

using namespace std;

class Rightparen: public Token  //child to Token class
{
public:
    Rightparen();               //zero parameter constructor
    Rightparen(string face);    //single parameter constructor
    int GetType();              //returns the type of token it is
    string Data();              //returns the data of the token in string from
    void Print();               //displays the data

    string _face;               //variable non-private
};

#endif // RIGHTPAREN_H

#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include "token.h"
#include <string>

using namespace std;

class Leftparen: public Token   //child class of Token
{
public:
    Leftparen();                //constructor
    Leftparen(string face);     //single var constructor
    int GetType();              //gets the type of Token
    string Data();              //returns the data in the Token
    void Print();               //displays the Token data

    string _face;               //variable, non-private
};

#endif // LEFTPAREN_H

#ifndef OPERATOR_H
#define OPERATOR_H
#include "token.h"
#include <string>

using namespace std;

class Operator: public Token    //child of Token class
{
public:
    Operator();                 //zero parameter constructor
    Operator(string oper);      //single parameter constructor
    int GetType();              //gets the type of token
    int Priority();             //sets priority to all
    void Print();               //displays the data
    string Data();              //returns the data in string form

    string optr;                //variable non-private
};

#endif // OPERATOR_H

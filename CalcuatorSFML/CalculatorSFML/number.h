#ifndef NUMBER_H
#define NUMBER_H
#include "token.h"
#include <string>

using namespace std;

class Number: public Token  //child class of Token
{
public:
    Number();               //zero constructor
    Number(string input);   //single variable constructor
    int GetType();          //returns the type of var
    void Print();           //displays the data
    string Data();          //returns the data

    string num;             //variable non-private


};

#endif // NUMBER_H

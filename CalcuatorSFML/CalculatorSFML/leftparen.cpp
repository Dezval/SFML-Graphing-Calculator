#include "leftparen.h"


Leftparen::Leftparen()              //zero parameter constructor
{
    _face = "(";
}

Leftparen::Leftparen(string face)   //single parameter constructor
{
    _face = face;
}

int Leftparen::GetType()            //gets the type
{
    return 2;
}

string Leftparen::Data()            //gets the data from the token
{
    return _face;
}

void Leftparen::Print()             //displays the data of the token
{
    cout<<_face;
}

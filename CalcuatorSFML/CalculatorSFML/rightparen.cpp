#include "rightparen.h"

Rightparen::Rightparen()            //zero parameter constructor
{
    _face = ")";
}

Rightparen::Rightparen(string face) //single parameter constructor
{
    _face = face;
}

int Rightparen::GetType()           //returns the type
{
    return 3;
}

string Rightparen::Data()           //returns the data of the Token
{
    return _face;
}

void Rightparen::Print()            //displays the data of the Token
{
    cout<<_face;
}

#include "number.h"

using namespace std;

Number::Number()                //zero parameter constructor
{
}

Number::Number(string input)    //single parameter constructor
{
    num = input;
}

int Number::GetType()           //returns the type
{
    return 0;
}

void Number::Print()            //displays the data of the token
{
    cout<<num;
}

string Number::Data()           //returns the data of the Token
{
    return num;
}

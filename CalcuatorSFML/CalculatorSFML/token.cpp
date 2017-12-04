#include "token.h"

Token::Token()          //zero parameter constructor
{
}

int Token::GetType()    //returns the type of the Token
{
    return 0;
}

int Token::size()       //returns the size
{
    int counter = 0;
    return counter;     //returns counter
}

void Token::Print()     //does nothing here, is a virtual function
{
}

string Token::Data()    //does nothing important here, vitrual
{
    return "!";
}

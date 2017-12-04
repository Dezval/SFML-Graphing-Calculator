#include "operator.h"
#include <string>

using namespace std;

Operator::Operator()                        //zero parameter constructor
{
}

Operator::Operator(string oper)             //single parameter constructor
{
    optr = oper;
}

int Operator::GetType()                     //returns the type
{
    return 1;
}

int Operator::Priority()                    //sets priority to all operators
{
    int holder;
    if(optr == "+" || optr == "-")          //gives plus and minus operators the lowest priority
        holder = 1;
    else if(optr == "*" || optr == "/")     //gives multi and divide the second lowest priority
        holder = 2;
    else if(optr == "sin" || optr == "cos"
         || optr == "tan" || optr == "sec"
         || optr == "csc" || optr == "cot"
         || optr == "Max")                  //gives all the tirg functions second highest priority
        holder = 4;
    else if(optr == "^")                    //gives power operator highest priority
        holder = 3;
    return holder;
}

void Operator::Print()                      //displays the data
{
    cout<<optr;
}

string Operator::Data()                     //returns the data of the Token
{
    return optr;
}


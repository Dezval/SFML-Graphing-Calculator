#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include "token.h"
#include "operator.h"
#include "number.h"
#include "operator.h"
#include "leftparen.h"
#include "rightparen.h"
#include <cmath>
#include <sstream>
#include "stringtoken.h"
#include "sfml/Graphics.hpp"

using namespace std;

bool findx(queue<Token*> equation);                 //checks if variable x exists in the equation
double GetValues(queue<Token*> input, bool xtrue, string &equation);  //Used for graphing with SFML
void DisplayQ(queue<Token*> input);                 //displays a queue of token type
queue<Token*> ShuntingYard(queue<Token*> infix);    //shuntingyard
string itos(double number);                            //converts int to string
double TtoD(Token* input);                          //converst Token pointer to a double
double Evaluate(queue<Token*> input, double var);   //Evaluates
double Apply(double X, double Y, string oper);      //applys an operator to two doubles
double Apply2(double X, string oper);               //applys an operator to a single double variable
void DeleteEq(queue<Token*> equation);

int main()
{
    string a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
    a = "(tan(x)/sin(x))+(100-x^2)^(1/2)";
    b = "sin(cos(tan(x)))";
    c = "3*3-5+8*2";
    d = "sin(x)+cos(3*x)";
    e = "Sqrt(1-^2)";
    f = "Sqrt(0.05-(x-0.3)^2)+0.5";
    g = "15*x^2";
    h = "x*sin(1/x)";
    i = "1/(x^3)";
    j = "sin(x+9)+cos(6)^543";
    k = "sin(2*sin(2*sin(2*(sin(x)))))";
    l = "sin(2*sin2*sin(2*sin(x)))";
    m = "(3+5+(9+2)))";
    n = "3.5.6+2";
    o = "3*+5";
    p = "x 5+6";
    double Var, Range1, Range2;
    string equation;
    bool xtrue = false;
    cout<<": ";
    getline(cin, equation);
    while(true)
    {
    xtrue = false;


    if(equation == "1")
        equation = a;
    else if(equation == "2")
            equation = b;
    else if(equation == "3")
            equation = c;
    else if(equation == "4")
            equation = d;
    else if(equation == "5")
            equation = "(1-x^2)^(1/2)";
    else if(equation == "6")
            equation = "(0.05-(x-0.3)^2)+0.5";
    else if(equation == "7")
            equation = g;
    else if(equation == "8")
            equation = h;
    else if(equation == "9")
            equation = i;
    else if(equation == "10")
            equation = j;
    else if(equation == "11")
            equation = k;
    else if(equation == "12")
            equation = l;
    else if(equation == "13")
            equation = m;
    else if(equation == "14")
            equation = n;
    else if(equation == "15")
            equation = o;
    else if(equation == "16")
            equation = p;

    cout<<"Equation: "<<equation<<endl;

    try                                             //try for throw and catch
    {
        if(equation == "")
            continue;
    queue<Token*> Post, Post1;
    Post1 = GetToken(equation);                     //sets Post1 to the tokenized equation

    if(Post1.empty())
        continue;

    if(findx(Post1) == true)                        //checks if there is an x variable present in the equation
    {
        cout<<"found x"<<endl;
        xtrue = true;
    }

    cout<<"Display Infix: ";
    DisplayQ(Post1);
    cout<<endl;

    Post = ShuntingYard(Post1);
    cout<<"Display PostFix: ";
    DisplayQ(Post);
    cout<<endl;
    cout<<endl<<GetValues(Post, xtrue, equation)<<endl;
    DeleteEq(Post);
    }
     catch(string Paren)
    {
        cout<<Paren<<endl;
    }
    }

    return 0;
}

void DeleteEq(queue<Token*> equation)                           //memory management
{
    Token* walker;
    while(!equation.empty())
    {
        walker = equation.front();
        equation.pop();                                         //pops
        delete walker;                                          //then deletes the pointer
    }
}

bool findx(queue<Token*> equation)
{
    queue<Token*> temp = equation;                              //makes a copy of the equation
    Token* walker;                                              //creaters a walker for the queue
    while(!temp.empty())
    {
        walker = temp.front();
        if(walker->Data() == "x" || walker->Data() == "X")      //checks if the data is an x
        {
            return true;
        }
        temp.pop();                                             //if not, pops until it finds an x or the queue becomes empty
    }
    return false;
}



double GetValues(queue<Token*> input, bool xtrue, string &equation)               //graphs if x variable is present
{
    int grid = 1000, xOriginal = 0, yOriginal = 0, CenterX = (grid/2), CenterY = (grid/2);
    double INC = 10,Scaler = 50, PanX = 0, PanY = 0;
    bool Hold = false;
    string SFMLinput;
    if(xtrue)
    {

        sf::RenderWindow window;                                //SFML
        window.create(sf::VideoMode(grid,grid),
                      "Graphing Calculator");                   //creates a window with SFML with 'grid' by 'grid' pixel dimension
        sf::VertexArray Line1(sf::LinesStrip, 2);               //init a Line

        while(window.isOpen())
        {
            sf::Event event;
            while(window.pollEvent(event))                      //waits for an event to happen
            {
                switch(event.type)                              //checks for the type of event
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::MouseWheelMoved:            //will check for mouse scrolling
                        INC+=event.mouseWheel.delta;
                        if(Scaler == 1 && event.mouseWheel.delta <=-1)      //will not allow Scaler to become 0
                            Scaler = -1;
                        else if(Scaler == -1 && event.mouseWheel.delta >=1) //will not allow Scaler to become 0
                            Scaler = 1;
                        if(event.mouseWheel.delta<0)
                        Scaler-=Scaler*0.1;
                        if(event.mouseWheel.delta>0)
                        Scaler+=Scaler*0.1;
                        cout<<"Wheel moved "<<Scaler<<endl;
//                        if(Scaler <= 1)
//                        {
//                            Scaler = 1.01;
//                            cout<<"Furthest Zoom Achieved."<<endl;
//                        }

                        break;
                    case sf::Event::MouseButtonPressed:
                        xOriginal = event.mouseButton.x;
                        yOriginal = event.mouseButton.y;
                        Hold = true;
                        break;
                    case sf::Event::MouseMoved:
                        if(Hold)
                        {
                        PanX = event.mouseMove.x - xOriginal;
                        PanY = event.mouseMove.y - yOriginal;
                        CenterX+=PanX;
                        CenterY+=PanY;
                        xOriginal = event.mouseMove.x;
                        yOriginal = event.mouseMove.y;
                        }
                        break;
                    case sf::Event::MouseButtonReleased:
                        Hold = false;
                        break;
                    case sf::Event::TextEntered:
                        if(event.text.unicode != 8 && event.text.unicode != 13)
                        SFMLinput+=(char)event.text.unicode;

                        if(event.text.unicode == 8)
                        {
                            SFMLinput = SFMLinput.substr(0,SFMLinput.size()-1);
                        }
                        if(event.text.unicode == 13)
                        {
                            equation = SFMLinput;
                            window.close();
                        }



                }
            }

            window.clear(sf::Color::Black);

            Line1[0].position = sf::Vector2f(CenterX, (0));                    //creates the y axis
            Line1[1].position = sf::Vector2f(CenterX, (grid));                 // ''
            window.draw(Line1);                                             //draws the y axis
            Line1[0].position = sf::Vector2f((0), CenterY);                    //creates the x axis
            Line1[1].position = sf::Vector2f((grid), CenterY);                 //''
            window.draw(Line1);                                             //draws teh x axis


            sf::Font font;                                                  //init a font
            if(!font.loadFromFile("arial.ttf"))                             //loads the font from the files specified
                cout<<"Did not load font."<<endl;                           //if error, tell me
            sf::Text text;                                                  //init text
            text.setFont(font);                                             //sets text's font to the one specified

            text.setColor(sf::Color::White);                                //sets text color to white
            text.setCharacterSize((25));                                    //sets text size to 25 pixels

            double FScaler = Scaler;

            while(grid/FScaler > 20)
            {
                FScaler *= 2;
            }

            for(double i = 0; i<=(grid/2)+(-1*(CenterX-grid/2)); i+=FScaler)    //creates the Positive X numbers on the grid
            {
                    text.setString(itos(i/Scaler));
                    text.setPosition((i+CenterX),CenterY);
                    window.draw(text);
            }
            for(double i = 0; i>=-grid/2+(-1*(CenterX-grid/2)); i-=FScaler)     //creates the Negative X numbers on the grid
            {
                    text.setString(itos(i/Scaler));
                    text.setPosition((i+CenterX),CenterY);
                    window.draw(text);
            }
            for(double i = 0; i<=grid/2+(CenterY-grid/2); i+=FScaler)           //creates the Positive Y numbers on the grid
            {
                    text.setString(itos(i/Scaler));
                    text.setPosition(CenterX,CenterY-i);
                    window.draw(text);
            }
            for(double i = 0; i>=-grid/2+(CenterY-grid/2); i-=FScaler)          //creates the Negative Y numbers on the grid
            {
                    text.setString(itos(i/Scaler));
                    text.setPosition(CenterX,CenterY-i);
                    window.draw(text);
            }

            for(double i = 0; i <= grid/2+(CenterX-grid/2); i+=FScaler)                          //creates the lines by the numbers Negative X grid
            {
                 Line1[0].position = sf::Vector2f(CenterX-i, CenterY-(10));
                 Line1[1].position = sf::Vector2f(CenterX-i, CenterY+(10));
                 window.draw(Line1);
            }
            for(double i = 0; i <= grid/2+(-1*(CenterX-grid/2)); i+=FScaler)                          //creates the lines by the numbers Positive X grid
            {
                 Line1[0].position = sf::Vector2f(CenterX+i, CenterY-(10));
                 Line1[1].position = sf::Vector2f(CenterX+i, CenterY+(10));
                 window.draw(Line1);
            }
            for(double i = 0; i <= grid/2+(-1*(CenterY-grid/2)); i+=FScaler)                          //creates the lines by the numbers
            {
                 Line1[0].position = sf::Vector2f(CenterX-(10),CenterY+i);
                 Line1[1].position = sf::Vector2f(CenterX+(10),CenterY+i);
                 window.draw(Line1);
            }
            for(double i = 0; i <= grid/2+(CenterY-grid/2); i+=FScaler)                          //creates the lines by the numbers
            {
                 Line1[0].position = sf::Vector2f(CenterX-(10),CenterY-i);
                 Line1[1].position = sf::Vector2f(CenterX+(10),CenterY-i);
                 window.draw(Line1);
            }


            cout<<"1: "<<((-grid/2+(-1*(CenterX-grid/2)))/Scaler) << " : "<<((grid/2+(-1*(CenterX-grid/2)))/Scaler)

                <<" comp: " << (grid/2+(-1*(CenterX-grid/2))/Scaler)*2/(1/Scaler)

                << "Scaler: "<<Scaler<<endl;

            for(double i = ((-grid/2+(-1*(CenterX-grid/2)))/Scaler); i < ((grid/2+(-1*(CenterX-grid/2)))/Scaler); i +=1/Scaler)                  //draws the graph in increments of 0.1
            {

                Line1[0].position = sf::Vector2f(   (i*Scaler+CenterX),         (Evaluate(input, i)*Scaler*-1+CenterY)      );
                Line1[1].position = sf::Vector2f(   ((i+1/Scaler)*Scaler+CenterX),    (Evaluate(input, i+1/Scaler)*Scaler*-1+CenterY)   );
                window.draw(Line1);
            }
            window.display();                                               //displays everything drawn
        }

    }else
        cout<<Evaluate(input, 1)<<endl;
}



void DisplayQ(queue<Token*> input)                  //displayes the input queue of token type
{
    while(!input.empty())
    {
        input.front()->Print();
        input.pop();
    }
}

queue<Token*> ShuntingYard(queue<Token*> infix)     //shunting yard
{
    stack<Token*> Stack;
    queue<Token*> PostFix;
    Token* walker;

    while(!infix.empty())
    {
        walker = infix.front();
        int type = walker->GetType();
        switch(type)
        {
        case 0 :PostFix.push(infix.front());                               //if type 0, push it into the postfix queue
                infix.pop();                                                //and pop if from the infix queue
                break;
        case 1 : while(!Stack.empty() && Stack.top()->GetType() == 1 &&     //checks if it is an operator and whether or not
                       static_cast<Operator*>(Stack.top())->Priority() >=   //there is an operator in the stack
                       static_cast<Operator*>(infix.front())->Priority())   //if so, compares them
                {
                    PostFix.push(Stack.top());
                    Stack.pop();
                }
                Stack.push(infix.front());
                infix.pop();
                break;
        case 2 : Stack.push(infix.front());                                 //if type 2, pushes into stack
                infix.pop();
                break;
        case 3 : if (!Stack.empty())
                {
                while(Stack.top()->GetType() != 2)        //if type 3, keeps doing the following until it finds a type 2
                    {
                        if (!Stack.empty())
                        {
                            PostFix.push(Stack.top());                              //pushed into postfix queue
                            Stack.pop();
                        }
                        if(Stack.empty())
                        {
                            string Paren("Too Many Parenthasis!!!!!!");
                            throw(Paren);
                        }

                    }
                }
                if(!Stack.empty() && Stack.top()->GetType() == 2)
                {
                    Stack.pop();
                    infix.pop();
                    break;
                }

                if(Stack.empty())
                {
                    string Paren("Too Many Parenthasis!!!!!!");
                    throw(Paren);
                }

                    infix.pop();                                                //pops from stack
                break;
        default :
            cout<<"Error 404."<<endl;                                       //default
            exit(0);
        }
    }
    while(!Stack.empty())                                                   //if the stack is not empty
    {
        if(Stack.top()->GetType() == 2)
            Stack.pop();
        else{
        PostFix.push(Stack.top());                                          //pushes everything into the postfix queue
        Stack.pop();                                                        //pops everything remaining
        }
    }
    //1CheckPoints(PostFix);
    //CheckOper(PostFix);
    return PostFix;
}

string itos(double number)         //converts from int to string
{
   stringstream ss;             //create a stringstream
   string str;
   ss << number;                //add number to the stream
   ss >> str;                   //push the contents onto a string
   return str;                  //return the string
}

double TtoD(Token* input)       //converts from Token pointer to double
{
    stringstream ss;
    double x;

    ss<<input->Data();
    ss>>x;

    return x;
}

double Evaluate(queue<Token*> input, double var)                    //evaluates the input
{
    stack<double> Stack;
    Token* walker;
    string oper;
    double i, X, Y, Ans;

    while(!input.empty())                                           //while the input is not empty
    {
        walker = input.front();
        int type = walker->GetType();
        switch(type)                                                //checks for the type for the switch
        {
        case 0 : if(((StrFind(walker->Data(), 'x') > -1) && walker->Data().size() == 1) ||
                    ((StrFind(walker->Data(), 'X') > -1) && walker->Data().size() == 1)) //checks if X variable
                {
                    Stack.push(var);
                    input.pop();
                    break;
                }else
                if (((StrFind(walker->Data(), 'x') > -1) && walker->Data().size() > 1) ||
                    ((StrFind(walker->Data(), 'X') > -1) && walker->Data().size() > 1))
                {
                    string Paren("Error! 'x' is next to a number.");
                    throw(Paren);
                }

                i = TtoD(input.front());                            //case 0, pushed the number into stack
                Stack.push(i);
                input.pop();
                break;
        case 1 : oper = walker->Data();
                if(oper == "+" || oper == "-" || oper == "*" ||
                   oper == "/" || oper == "^" || oper == "Max")     //performs apply with two doubles on these operators
                {
                    if(Stack.empty())
                    {
                        string Paren("Error! Not Enough Numbers!");
                        throw(Paren);
                    }
                    Y = Stack.top();
                    Stack.pop();
                    if(Stack.empty())
                    {
                        string Paren("Error! Not Enough Numbers!");
                        throw(Paren);
                    }
                    X = Stack.top();
                    Stack.pop();
                    Stack.push(Apply(X, Y, oper));                  //Apply does the actual math
                    input.pop();
                }else if(oper == "cos" || oper == "sin" ||
                         oper == "tan" || oper == "sec" ||
                         oper == "csc" || oper == "cot")            //trig functions
                {
                    if(Stack.empty())
                    {
                        string Paren("Error! Not Enough Numbers!");
                        throw(Paren);
                    }
                    X = Stack.top();
                    Stack.pop();
                    Stack.push(Apply2(X, oper));                    //Apply2 takes care of the trig functions
                    input.pop();
                }
                break;
        }
    }
    Ans = Stack.top();
    Stack.pop();
    return Ans;
}

double Apply(double X, double Y, string oper)       //apply takes care of the math using cmath
{
    double Answer;

    if(oper == "+")
    {
        Answer = X + Y;                             //adds the two doubles
        return Answer;
    }
    if(oper == "-")
    {
        Answer = X - Y;                             //subtracts the two doubles
        return Answer;
    }
    if(oper == "*")
    {
        Answer = X * Y;                             //multiplies the two doubles
        return Answer;
    }
    if(oper == "/")
    {
        if(Y == 0)                                  //if dividing by 0
        {
            string Paren("Can't Divide by 0!");
            throw(Paren);                        //throws an exception
        }
        Answer = X / Y;                             //divides the two doubles
        return Answer;
    }
    if(oper == "^")
    {
        Answer = pow(X, Y);                         //raises the base double to the power of the second double
        return Answer;
    }
    if(oper == "Max")
    {
        if(X > Y)                                   //checks which double is greater
            return X;
        else
            return Y;
    }
    cout<<"Operator Error 404."<<endl;
    exit(0);
    return 0;
}

double Apply2(double X, string oper)                //does the math for the trig functions
{
    double Answer;
    if(oper == "sin")
    {
        Answer = sin(X);
        return Answer;
    }
    if(oper == "cos")
    {
        Answer = cos(X);
        return Answer;
    }
    if(oper == "tan")
    {
        Answer = tan(X);
        return Answer;
    }
    if(oper == "sec")
    {
        Answer = (1/cos(X));
        return Answer;
    }
    if(oper == "csc")
    {
        Answer = (1/sin(X));
        return Answer;
    }
    if(oper == "cot")
    {
        Answer = (1/tan(X));
        return Answer;
    }
    cout<<"Trig Error 404."<<endl;
    exit(0);
    return 0;
}


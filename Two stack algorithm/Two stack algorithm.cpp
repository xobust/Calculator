// Two stack algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
#include <conio.h> //getch()

#include <ctype.h>

#define cts(x) string(1,x)
//char till sträng


using namespace std;

std::stack<char> oper; //operator staken
std::stack<double> vals; //numer stacken för uträkningen
std::queue<string> output; //resultatet i reverse polish


bool String2Double(const std::string& str, double& result) // bra string to nummer funktion från the interwebs
{
    std::istringstream ss(str);
    ss.imbue(std::locale::classic());
    ss >> result;
    return !ss.fail() && ss.eof();
}

bool IsRight(char o){  // höger eller vänster asosiatív
       return o == '^';
}

bool IsLeft(char o){
       return !IsRight(o); //hackat
}

int Precedence(char o){ //operator rank (ordning)
	switch (o)
	{
	case '+':
		return 1;
	case '-':
		return 1;
	case '/':
		return 2;
	case '*':
		return 2;
	case '^':
		return 3;
	}
    
	return 0;
}

//räknar ut resultatet av en operation
//och lägger tillbaka det på värdes stacken
bool domath()
{
	// popa operatorn och de senaste värdena
	char c = output.front()[0];
	output.pop();

	cout << c << " ";

	double a, b;

	if(vals.empty())
		return false;

	b = vals.top(); // numren kommer i omvänd ordning 
	vals.pop();


	if(vals.empty()) // fix för negativa tal i början av en uträkning men inte senare
		if(c=='-') 
			a=0;
		else
			return false;
	else
	{
		a = vals.top();
		vals.pop();
	}


	switch(c)
	{
	case '*':
		vals.push(a*b);
		break;
	case '+':
		vals.push(a+b);
		break;
	case '-':
		vals.push(a-b);
		break;
	case '/':
		vals.push(a/b);
		break;
	case '^':
		vals.push(pow(a,b));
		break;
	}


	return true;
}

//Infix till omvänd polsk notation
int ToReversePolish(string exp)
{

	exp.erase(remove_if(exp.begin(), exp.end(), isspace), exp.end());

	for(int i = 0; i < exp.length(); i++)
	{
		if(isalpha(exp[i]))
		{
			if(i+1 < exp.length() && exp.substr(i,2) == "pi")
			{	
				output.push("3.14159265359"); 
				i+=2; //gå förbi på
			}
			else
			{
				cout<<"unknown character detected: "<<exp[i]<<"\n";
				break;
			}
			//todo implementera variabler och funktioner

			if(i>=exp.length()) //om utrycket tar slut efter variabeln
				break;

		}

		if (isdigit(exp[i]))
		{
			string temp="";
			
			for(int j = i; j < exp.length(); j++)
			{
				 if(isdigit(exp[j]) || exp[j] == '.')
				 {
					 temp += exp[j];
					 i = j;
				 }
				 else 
				 {
					break;
				 }
			}

			output.push(temp);

		}else
		{
			if(exp[i] == '(')
				oper.push('(');
			else if( exp[i] == ')')
			{
				while(oper.top() != '(')
				{
					output.push(cts(oper.top()));
					oper.pop();
				}
				oper.pop();

			}else
			{
				char o1 = exp[i];
				while (oper.size() > 0)
				{
					char o2 = oper.top();
					if((IsLeft(o1)  && Precedence(o1) <= Precedence(o2))
                       ||  (IsRight(o1) && Precedence(o1) <  Precedence(o2)))
					{
					   output.push(cts(o2));
					   oper.pop();
					  
					}else
					{
						break;
					}
				}

				 oper.push(o1);

			}
		}
		
	}

	while(oper.size() > 0)
	{
		output.push(cts(oper.top()));
		oper.pop();
	}

	return 1;
}

//Räknar ut den omvända polska notationen
double calculate(string str)
{
	ToReversePolish(str);

	cout << "Reverse polish result: ";

	while(output.size() > 0)
	{
		string s = output.front();
		if(s.length() > 1 || isalnum(s[0])) // om det är ett nummer lägg det på nummer stacken
		{
			double d = 0;
			String2Double(s,d);
			vals.push(d);
			output.pop();

			cout<< d << " ";
		}else //annars gör en operation 
		{
			if(!domath())
				cout<< "syntax error\n";
		}
	}

	cout << "= \n";
	
	return vals.top();
}


int main(int argc, _TCHAR* argv[])
{
	string s;
	cin>>s;
	cout << calculate(s); 

	getch();

	return 0;
}
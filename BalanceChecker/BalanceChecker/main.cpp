//
//  main.cpp
//  BalanceChecker
//
//  Created by Anish on 13/03/15.
//  Copyright (c) 2015 Anish. All rights reserved.
//
#include<iostream>
#include<stack>
#include<string>

using namespace std;

bool isPair(char opening,char closing);

bool isBalanced(string exp)
{
    stack<char>  s;
    
    for(int i =0;i<exp.length();i++)
    {
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
            s.push(exp[i]);
        else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
        {
            if(s.empty() || !isPair(s.top(),exp[i]))
                return false;
            else
                s.pop();
        }
    }
    
    if(s.empty())
        return true;
    else
        return false;
}

bool isPair(char open,char close)
{
    if(open == '(' && close == ')')
        return true;
    else if(open == '{' && close == '}')
        return true;
    else if(open == '[' && close == ']')
        return true;
    return false;
}

int main()
{
    
    string exp;
    
    cout<<"Enter an expression:  ";
    
    cin>>exp;
    
    if(isBalanced(exp))
        cout<<"Expression is Balanced" << endl;
    else
        cout<<"Expression is Not Balanced\n"<< endl;
}
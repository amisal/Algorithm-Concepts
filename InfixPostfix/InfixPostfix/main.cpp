//
//  main.cpp
//  InfixPostfix
//
//  Created by Anish on 12/03/15.
//  Copyright (c) 2015 Anish. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isOperator(char c);
bool isOperand(char c);
int OperatorRank(char op);
int PrecedenceCheck(char op1, char op2);
int IsRightAssociative(char op);
string PosttoInEval(string input);

string PosttoInEval(string input)
{
    
    stack<string> s;
    
    
    string output="";
    string operator1="";
    string operator2="";
    
    
    for(int i=0; i<input.length();i++)
    {
        if(isOperator(input[i]))
        {
            string temp;
            operator1=s.top();
            s.pop();
            operator2=s.top();
            s.pop();
            
            temp="("+ operator2 + input[i] + operator1+")";
            //cout<< temp<<endl;
            s.push(temp);
            
        }
        else if(isOperand(input[i]))
        {
            output=input[i];
            //cout<< output;
            s.push(output);
        }
    }
    
    while(!s.empty())
    {
        output= s.top();
        s.pop();
    }
    
    
    return output;
}

void displayStack(stack<string> *s)
{
    while (!s->empty()) {
        cout<< s->top();
    }
}

string IntopostEval(string input)
{
    stack<char> s;
    string output="";
    for(int i=0; i<input.length();i++)
    {
        if(isOperator(input[i]))
        {
            while(!s.empty() && s.top() != '(' && PrecedenceCheck(s.top(), input[i]))
            {
                output += s.top();
                s.pop();
                
            }
            s.push(input[i]);
        }
        else if (isOperand(input[i]))
        {
            output += input[i];
        }
        else if (input[i] == '(')
        {
            s.push(input[i]);
        }
        
        else if(input[i] == ')')
        {
            while(s.top() != '(')
            {
                
                output += s.top();
                s.pop();
                
            }
            s.pop();
        }
        
    }
    
    while(!s.empty()) {
        output += s.top();
        s.pop();
    }
    
    return output;
}


bool isOperand(char c)
{
    if(c >= '0' && c <= '9') return true;
    if(c >= 'a' && c <= 'z') return true;
    if(c >= 'A' && c <= 'Z') return true;
    return false;
}


bool isOperator(char c)
{
    switch (c) {
            
        case '^':
            return true;
        case '*':
            return true;
        case '/':
            return true;
        case '-':
            return true;
        case '+':
            return true;
        default:
            return false;
            
    }
    
}

int OperatorRank(char op)
{
    int rank = -1;
    switch(op)
    {
            
        case '^':
            return rank = 3;
        case '*':
            return rank = 2;
        case '/':
            return rank = 2;
        case '+':
            return rank = 1;
        case '-':
            return rank = 1;
        default:
            return rank = 0;
            
    }
    
}

int PrecedenceCheck(char op1, char op2)
{
    int op1Wt = OperatorRank(op1);
    int op2Wt = OperatorRank(op2);
    
    if(op1Wt == op2Wt)
    {
        if(IsRightAssociative(op1))
            return false;
        else
            return true;
    }
    if(op1Wt > op2Wt)
        return true;
    else
        return false;
}

int IsRightAssociative(char op)
{
    if(op == '^')
        return true;
    else
        return false;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    string ip;
    cout << "-----------------------------------------"<<endl;
    cout << "Enter an Infix Expression: "<<endl;
    cout << "-----------------------------------------"<<endl;
    cout << "Infix to Postfix Converter ->"<<endl;
    cin >> ip;
    cout << IntopostEval(ip)<< endl;
    cout << "-----------------------------------------"<<endl;
    cout << "Postfix to Infix Converter ->"<<endl;
    cout << PosttoInEval(IntopostEval(ip))<< endl;
    cout << "-----------------------------------------"<<endl;
    
    return 0;
}

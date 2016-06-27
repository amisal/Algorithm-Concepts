//
//  main.cpp
//  GcdAlgorithm
//
//  Created by Anish on 13/02/15.
//  Copyright (c) 2015 Anish. All rights reserved.
//

#include <iostream>
using namespace std;

class GCD{
    
private:
    
    int gcd=0;
    bool a_evenFlag=true;
    bool b_evenFlag=true;
    
public:
    
    int calGCD(int a, int b)
    {
        int temp=0;
        
        if (a<b)
        {
            temp=a;
            a=b;
            b=temp;
        }
        
        if((a%2==0) && (b%2==0))
        {
            gcd=(2*calGCD(a/2, b/2));
        }
        else if ((a%2==0) && (b%2!=0))
        {
            gcd=(calGCD(a/2, b));
        }
        else if ((a%2!=0) && (b%2==0))
        {
            gcd=(calGCD(a, b/2));
        }
        else if ((a%2!=0) && (b%2!=0))
        {
           
            if(a==1 || b==1)
            {
                gcd=1;
            }
            else if(a==b)
            {
                gcd=a;
            }
            else
            {
                gcd=(calGCD((a+b)/2, (a-b)/2));
            }
            
            
        }
        
        return gcd;
    }
    
    int realGCD(int m, int n)
    {
        while (n!=0) {
            
            int rem=m%n;
            m=n;
            n=rem;
        }
        
        
        return m;
    }

};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    int value1=0, value2=0;
    cout<<"Hello, This is program to calculate GCD!"<< endl;
    
    GCD g;
    int newGCD=0;
    int realGCD=0;
    
    printf("Enter Two intergers:\n");
    scanf("%d %d",&value1,&value2);
    
    
    newGCD=g.calGCD(value1, value2);
    realGCD=g.realGCD(value1, value2);
    
    printf("GCD of %d and %d is %d\n",value1,value2,newGCD);
    printf("Real GCD of %d and %d is %d\n",value1,value2,realGCD);
    if(newGCD==realGCD)
    {
        printf("<<<<<<<<<SUCCESS>>>>>>>>>>>\n");
    }
    return 0;
}

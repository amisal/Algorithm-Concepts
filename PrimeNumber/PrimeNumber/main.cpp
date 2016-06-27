//
//  main.cpp
//  PrimeNumber
//
//  Created by Anish on 13/02/15.
//  Copyright (c) 2015 Anish. All rights reserved.
//

#include <iostream>
#include <math.h>


class isPrime
{
   
    private:
    bool primeFlag=false;
    
    public:
    bool noIsPrime(int n)
    {
    
        for(int i=2;i<= (int)sqrt(n);i++)
        {
            //printf("%d\n",(int)sqrt(n));
            if(n%i==0)
            {
                primeFlag=true;
            }
        }
        
        if(!primeFlag)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
        
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int no=0;
    isPrime prime;
    printf("To Find a number N is prime\n");
    printf("Enter a Number:\n");
    scanf("%d",&no);
    
    if(prime.noIsPrime(no))
    {
        printf("Number %d is a Prime Number\n",no);
    }
    else
    {
        printf("Number %d is NOT a Prime Number\n",no);
    }
    
    return 0;
}

//
//  main.cpp
//  Recursion
//
//  Created by Anish on 08/02/15.
//  Copyright (c) 2015 Anish. All rights reserved.
//

#include <iostream>
using namespace std;

class Binary{
    
public:
    
    int numberOfOnes(const int &n){
        
        int ones=0;
        if (n==1 || n==2)
        {
            ones=1;
        }
        else if ((n%2)!=0)
        {
            //if n is odd
            ones=numberOfOnes(n/2)+1;
        }
        else
        {
            // if n is even
            ones=numberOfOnes(n/2);
        }
        
        return ones;
    }


    
};
int main(int argc, const char * argv[]) {
    
    // insert code here...
    int num=0;
    int integer=0;
    Binary bn;
   
    printf("Enter an integer:\n");
    scanf("%d", &integer);
    num=bn.numberOfOnes(integer);
    printf("Number of ones in Binary representation of %d in %d\n",integer,num);
    
    return 0;
}

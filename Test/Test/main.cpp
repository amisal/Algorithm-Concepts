//
//  main.cpp
//  Test
//
//  Created by Anish on 20/04/15.
//  Copyright (c) 2015 Anish. All rights reserved.
//


#include "AVLTree.cpp"
#include "BinarySearchTree.cpp"
#include "SplayTree.cpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <math.h>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    BSTmain();
    AVLmain();
    Splaymain();
    
    return 0;
}

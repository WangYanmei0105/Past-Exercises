//
//  main.cpp
//  7
//
//  Created by Amy Wang on 2020/9/7.
//  Copyright © 2020 Amy Wang. All rights reserved.
//

#include <iostream>
using namespace std;

int foo(int a, double b, int c){
    while ( c <= 1) c++;
    cout << (a/b);
    return (a/c);
}

int main () {
    foo (1, 2, 0);
    return 0;
}





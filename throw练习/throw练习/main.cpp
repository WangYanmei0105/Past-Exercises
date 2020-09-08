//
//  main.cpp
//  throw练习
//
//  Created by Amy Wang on 2019/9/3.
//  Copyright © 2019 Amy Wang. All rights reserved.
//

#include <iostream>
/*
#include <stdexcept>
int main(){
    int input1;
    int input2;
    std::cin>>input1;
    std::cout<<"you have entered: "<<input1<<std::endl;
    std::cin>>input2;
    std::cout<<"you have entered: "<<input2<<std::endl;
    
    if(input1==input2){
        return 0;
    }else{
        throw runtime_error("wrong!");
        return -1;
    }
    
}
 */
using namespace std;

int f(x,y,i) {
    
    if x =0 ; then return i;
    
    if x>=y; then
    
    return f(x-1,y,i);
    
    else
        
        return f(y,x,i+1);
    
    end if
        
        }
int main(){
    int x;
    cin>>x;
    cout<<foo(x)<<endl;
    return 0;
}



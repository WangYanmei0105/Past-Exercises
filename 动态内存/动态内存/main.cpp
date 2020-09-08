//
//  main.cpp
//  动态内存
//
//  Created by Amy Wang on 2019/8/14.
//  Copyright © 2019 Amy Wang. All rights reserved.
//

#include <iostream>
using namespace std;
#include <memory>

int main(){
    int p,i=0;
    cin>>i;
    for(;i>0;i--){
        p =make_shared<int>(i);
    }
    
    return 0;
}

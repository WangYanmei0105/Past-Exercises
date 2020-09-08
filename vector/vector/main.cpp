//
//  main.cpp
//  vector
//
//  Created by Amy Wang on 2019/8/15.
//  Copyright © 2019 Amy Wang. All rights reserved.
//

#include <iostream>
using namespace std;
#include<string>
#include<vector>

int main(){
    /*
    vector<int> result;
    for(int i=0;i<5;i++){
        result.push_back(i);
    }
    for(auto c:result){
        cout<<c<<endl;
    }
    return 0;
    */
    /*
    vector<int> scores(11,0);
    unsigned grade;
    while(cin>>grade){
        if(grade<=100){
            ++scores[grade/10];
        }
    }
    for(auto c:scores){
        cout<<c<<" ";
    }
    return 0;
    */
    
    string s="1234567890";
    for(auto &c:s){
        cout<<&c<<endl;//瞧瞧我发现了什么好玩的东西
        }
    
    return 0;
}

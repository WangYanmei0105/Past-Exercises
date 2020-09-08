//
//  main.cpp
//  正则练习
//
//  Created by Amy Wang on 2019/8/13.
//  Copyright © 2019 Amy Wang. All rights reserved.
//

#include <iostream>
using namespace std;

#include<string>


int main(){
    string s1[5];
    
    for(int i=0;i<5;i++){
        cin>>s1[i];
    }
    
    cout<<"________________"<<endl;
    
    for(int i=4;i>=0;i--){
        cout<<"s1["<<i<<"] is "<<s1[i]<<endl;
    }
    
    return 0;
}

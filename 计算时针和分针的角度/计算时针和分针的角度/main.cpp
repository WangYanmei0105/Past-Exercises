//
//  main.cpp
//  计算时针和分针的角度
//
//  Created by Amy Wang on 2019/8/11.
//  Copyright © 2019 Amy Wang. All rights reserved.
//
/*
#include <iostream>
using namespace std;

int main(){
Input:
    cout<<"请输入时刻：（例：12:30）" <<endl;
    int hours=0;
    int minutes=0;
    char sig;

    cin>>hours;
    
    cin>>minutes;
    
    if(hours>=24){
        cout<<" 输入错误，请重试！" <<endl;
        goto Input;
    }

    return 0;
 */

#include <iostream>
using namespace std;

int main() {
    //...
    char input;
Input:
    cin>>input;
    switch(input){
        case'y':
            goto Input;
            break;
        case'n':
            return 0;
            break;
        default:
            cout<<"wrong"<<endl;
            break;
    }
    return 0;
}


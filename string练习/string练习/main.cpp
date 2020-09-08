//
//  main.cpp
//  string练习
//
//  Created by Amy Wang on 2019/8/13.
//  Copyright © 2019 Amy Wang. All rights reserved.
//

#include <iostream>
using namespace std;

#include<string>
#include<algorithm>
#include <sstream>//字符串转数字

int main(){
    /*
    string s1[5];
    for(int i=0;i<5;i++){
    Input:
        getline(cin, s1[i]);
        if(s1[i].empty()){//如果字符串是空行，重新输入
            cout<<"Wrong!!!"<<endl;
            goto Input;
        }
    }
    
    cout<<"________________"<<endl;
    
    for(int i=4;i>=0;i--){
        cout<<"s1["<<i<<"] is '"<<s1[i]<<"'"<<endl;
        cout<<sizeof(s1[i])<<endl;//这是干什么的？？？
        
        cout<<s1[i].length()<<endl;
        cout<<s1[i].size()<<endl;
        cout<<s1[i][0]<<endl;//输出第一个字符
        cout<<"-------"<<endl;
    }
    
    
    string str(5,'c');
    cout<<str+s1[4]<<endl;
    
    */
    
    /*
    //作业3.2.2，3.4
    string s[2];
    cin>>s[0];
    cin>>s[1];
    //字符大小比较
    if(s[0]==s[1]){
        cout<<"s[0] equals to s[1]."<<endl;
    }else if(s[0]>s[1]){
        cout<<"s[0] is larger than s[1]."<<endl;
    }else{
        cout<<"s[0] is smaller than s[1]."<<endl;
    }
    //字符串长度比较
    if(s[0].length()==s[1].length()){
        cout<<"The two strings are equal in length."<<endl;
    }else if(s[0].length()>s[1].length()){
        cout<<s[0]<<endl;
    }else{
        cout<<s[1]<<endl;
    }
    */
    
    /*
    //以下是cin和getline的区别（关于空格的处理）
    string s[3];
    cin>>s[0];
    cin>>s[1];
    cin>>s[2];
    
    cout<<s[0]<<endl;
    cout<<s[1]<<endl;
    cout<<s[2]<<endl;
    */
    
    /*
    //注意范围for：for(declarition: expression){ statement } 的用法
    string s="hello";
    for(auto m:s){//auto：自动判断类型？？？
        cout<<m<<endl;
    }
     */
    
    /*
    //注意decltypeh关键字和cctype头文件中isxxx函数的用法
    string s;
    getline(cin, s);
    decltype(s.size()) alpha_Num=0;//但是为什么这里要用decltype？？？
    for(auto c:s){
        if(isalpha(c)){//如果是字母
            alpha_Num++;
        }
    }
    cout<<alpha_Num<<" letters in "<<s<<"!"<<endl;
    
    if(!s.empty()){
        for(auto c:s){
            c=toupper(c);//变作大写
            cout<<c;
        }
    }
    cout<<endl;
    
    if(!s.empty()){
        s[0]=toupper(s[0]);//第0个元素变作大写
        for(auto c:s){
            cout<<c;
        }
    }
    cout<<endl;
    
    if(!s.empty()){
        for(decltype(s.size()) index=0; index < s.size() && !isspace(s[index]); index++){
            s[index]=toupper(s[index]);
        }
        for(auto c:s){
            cout<<c;
        }
    }
    */
    
    //进制转换
    const string H="0123456789ABCDEF";//定义十六进制s基础数组
    cout<<"Please enter numbers:"<<endl;
    string result, error, s;
    string::size_type n;//size_type类型：P79
    int judge=0;
    
    while(cin>>n){//当输入时（需要以空格相隔，字母作结）
        if(n<H.size()){//检验是否在0-15内
            result+=H[n];//通过下标读取16进制s字符
            result+=" ";
        }else{
            stringstream ss;//必须每使用一次就定义一遍
            judge++;
            ss<<n;//流！
            ss>>s;//这样就转换了字符串和数字
            error+=s;
            error+=" ";
            result+="*";//在result里用*表示
            result+=" ";

        }
    }
    cout<<"The result is: "<<result<<endl;
    if(judge>0){
        cout<<"You seem to have entered "<<judge<<" wrong numbers:"
        <<error<<endl;
    }
    return 0;
     /*
    //测试
    int n[3];
    string error;
    for(int i=2;i>=0;i--){
        stringstream ss;
        string s;
        cin>>n[i];
        ss<<n[i];
        ss>>s;
        cout<<"*"<<s<<endl;
        error+=s;
        error+=" ";
    }
    cout<<error;
    */
}

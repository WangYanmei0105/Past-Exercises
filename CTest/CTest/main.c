#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MYHEADER.h"

#define MAX_LINE 1024
double rec(char formula[200]);
struct varibles{
    char var_name[256];
    double var;
}varible[256];

int check_include(char line[MAX_LINE]);

int main()
{
    strncpy(varible[0].var_name, "ans", 3);varible[0].var=0;
    int i=1;
    char buf_t[MAX_LINE];  /*buffer area*/
    FILE *fp;            /*file pointer*/
    long len=0;             /*number of the chars of the line*/
    if((fp = fopen("in3.txt","r")) == NULL)
    {
        perror("fail to read");
        exit (1) ;
    }
    while(fgets(buf_t,MAX_LINE,fp) != NULL)
    {
        len = strlen(buf_t);
        if (buf_t[len-1]=='\n') buf_t[len-1] = '\0';
        if (buf_t[len-2]=='\r') buf_t[len-2] = '\0';  /*去掉换行符*/
        if (buf_t[0]=='\n') continue;
        ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
        /*remove space*/
        char buf[MAX_LINE]={""};
        for (int n=0, i=0;i<=len-1;i++){
            if (buf_t[i]!=' '){
                buf[n]=buf_t[i];
                n++;
            }
        }
        len = strlen(buf);
        ////////////////////////////////////////////////////////////////////////
        //*是否有 ；？/
        int fenhao=0;
        if (buf[len-1]==';'){
            fenhao=1;
            buf[len-1]='\0';
        }
        int check_2=0;
        ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
        /*如果是输出语句*/
        if (buf[0]=='f' && buf[1]=='p' && buf[2]=='r' && buf[3]=='i' && buf[4]=='n' && buf[5]=='t' && buf[6]=='f' && buf[7]=='('){
            char expression[256]={""};
            int changeline=0;
            for (long m=strlen(buf_t)-1; m>=0; m--){//get expression
                if (buf_t[m]=='"'){
                    strncat(expression, buf_t+(strchr(buf_t, '"')-&buf_t[0])+1, m-(strchr(buf_t, '"')-&buf_t[0])-1);
                    break;
                }
            }
            if (*(strchr(expression, '\\')+1)=='n'){
                changeline=1;
                *(strchr(expression, '\\')+1)='\0';
                *strchr(expression, '\\')='\0';
            }
            for (long n=strlen(expression)-1; n>=0; n--){//find varibles
                if (expression[n]=='%' && expression[n+1]=='f'){
                    char var[256]={""};
                    char part1[256]={""}, part2[256]={""};
                    strncpy(part1, expression, &expression[n]-&expression[0]);
                    strncpy(part2, expression+strlen(part1)+2, strlen(expression)-strlen(part1)-2);
                    for (long m=strlen(buf)-1; m>=0; m--){
                        if (buf[m]==','){
                            buf[m]=' ';
                            char var_t[256]={""};
                            for (int c=0; c<256; c++) var[c]='\0';
                            strncpy(var_t, buf+m+1, strchr(buf, ')')-&buf[0]-m-1);
                            for (int k=0, n=0; k<256; k++){
                                if (! isspace(var_t[k])) var[n++]=var_t[k];
                            }
                            for (long k=m; k<=strchr(buf, ')')-&buf[0]-1; k++) buf[k]=' ';
                            break;
                        }
                    }
                    ////compute
                    for (long k=0; k<=strlen(var)-1; k++){//check varible names
                        if (isdigit(var[k])==0 && var[k]!='\0' && var[k]!='.' &&var[k]!='+'&&var[k]!='-'&&var[k]!='*'&&var[k]!='/'&&var[k]!='^'&&var[k]!='('&&var[k]!=')'){
                            int check_1=0, length=0;
                            long begin=k;
                            check_2=1;
                            while (var[k]!='+'&&var[k]!='-'&&var[k]!='*'&&var[k]!='/'&&var[k]!='^'&&var[k]!='\0') {
                                length++;k++;//name length
                            }
                            char name_t[256]={""}, partr[256]={""}, partl[256]={""};
                            strncpy(name_t, var+begin, length);//name
                            strncpy(partl, var, begin);//left part
                            strncpy(partr, var+begin+length, strlen(var)-begin-length);//right part
                            for (int j=0; j<=i; j++){
                                if(strcmp(varible[j].var_name, name_t)==0){//get value
                                    sprintf(name_t, "%lf" ,varible[j].var);
                                    strcat(name_t, partr);
                                    strcat(partl, name_t);
                                    check_1=1;
                                }
                            }
                            if(check_1==0){
                                printf("Warning: undeclared varible \"%s\"\n", name_t);
                                exit(1);
                            }
                            if (check_2==1) strncpy(var, partl, strlen(partl));
                        }
                    }
                    ////get full expression
                    char val[256]={""};
                    sprintf(val, "%f",rec(var));
                    strcat(val, part2);
                    strcat(part1, val);
                    for (int n=0; n<=255; n++) expression[n]='\0';
                    strncpy(expression, part1, strlen(part1));
                }
            }
            if (changeline==1 && fenhao==0) printf("%s\n", expression);
            else if(fenhao==0) printf("%s", expression);
        }
        ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
        /*如果是赋值语句*/
        else if (strchr(buf, '=')){
            check_2=0;
            char *equal=strchr(buf, '=');
            char var_name[256]={""}, var[256]={""};
            strncpy(var_name, buf, equal-&buf[0]);//get name
            strncpy(var, equal+1, &buf[len-1]-equal);//get expression
            for (long k=0; k<=strlen(var)-1; k++){//check varible names
                if (isdigit(var[k])==0 && var[k]!='\0' && var[k]!='.' &&var[k]!='+'&&var[k]!='-'&&var[k]!='*'&&var[k]!='/'&&var[k]!='^'&&var[k]!='('&&var[k]!=')'){
                    int check_1=0, length=0;
                    long begin=k;
                    check_2=1;
                    while (var[k]!='+'&&var[k]!='-'&&var[k]!='*'&&var[k]!='/'&&var[k]!='^'&&var[k]!='\0') {
                        length++;k++;//name length
                    }
                    char name_t[256]={""}, partr[256]={""}, partl[256]={""};
                    strncpy(name_t, var+begin, length);//name
                    strncpy(partl, var, begin);//left part
                    strncpy(partr, var+begin+length, strlen(var)-begin-length);//right part
                    for (int j=0; j<=i; j++){
                        if(strcmp(varible[j].var_name, name_t)==0){//get value
                            sprintf(name_t, "%lf" ,varible[j].var);
                            strcat(name_t, partr);
                            strcat(partl, name_t);
                            check_1=1;
                        }
                    }
                    if(check_1==0){
                        printf("Warning: undeclared varible \"%s\"\n", name_t);
                        exit(1);
                    }
                    if (check_2==1) strncpy(var, partl, strlen(partl));
                }
            }
            int check=0;
            for (int j=0; j<=i; j++){
                if (strcmp(varible[j].var_name, var_name)==0){
                    varible[j].var=rec(var);
                    check=1;
                    break;
                }
            }
            if(check==0){// no old varible, create a new one
                strncpy(varible[i].var_name, var_name, equal-&buf[0]);
                varible[i].var=rec(var);
                i++;
            }
            if (fenhao==0) printf("%s =\n \t%lf\n", var_name, rec(var));
        }
        /*赋值语句结束*/
        ////////////////////////////////////////////////////////////////////////////////
        else{
            char var[256]={""};
            strncpy(var, buf, len);
            for (long k=0; k<=strlen(var)-1; k++){//check varible names
                if (isdigit(var[k])==0 && var[k]!='\0' && var[k]!='.' &&var[k]!='+'&&var[k]!='-'&&var[k]!='*'&&var[k]!='/'&&var[k]!='^'&&var[k]!='('&&var[k]!=')'){
                    int check_1=0, length=0;
                    long begin=k;
                    check_2=1;
                    while (var[k]!='+'&&var[k]!='-'&&var[k]!='*'&&var[k]!='/'&&var[k]!='^'&&var[k]!='\0') {
                        length++;k++;//name length
                    }
                    char name_t[256]={""}, partr[256]={""}, partl[256]={""};
                    strncpy(name_t, var+begin, length);//name
                    strncpy(partl, var, begin);//left part
                    strncpy(partr, var+begin+length, strlen(var)-begin-length);//right part
                    for (int j=0; j<=i; j++){
                        if(strcmp(varible[j].var_name, name_t)==0){//get value
                            sprintf(name_t, "%lf" ,varible[j].var);
                            strcat(name_t, partr);
                            strcat(partl, name_t);
                            check_1=1;
                        }
                    }
                    if(check_1==0){
                        printf("Warning: undeclared varible \"%s\"\n", name_t);
                        exit(1);
                    }
                    if (check_2==1) strncpy(var, partl, strlen(partl));
                }
            }
            strncpy(varible[0].var_name, "ans", 3);
            varible[0].var=rec(var);
            if (fenhao==0) printf("ans =\n \t%lf\n", rec(var));
        }
        for (int n=0; n<=1023; n++) buf[n]='\0';
    }
    ////////////////////////////////////////////////////////////////////////////////
    //print varibles
    //for (i--;i>=0;i--)printf("name: %s, value: %lf\n", varible[i].var_name, varible[i].var);
    return 0;
}

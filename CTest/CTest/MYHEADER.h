#ifndef __MYHEADER_H__
#define __MYHEADER_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

double rec(char formula[200]){

    //first deal with ()
    for (long i=strlen(formula); i>=0; i--){//to make sure that all () are paired
        if (formula[i]=='('){
            long j=0;
            char part1[200]={""}, part2[200]={""}, part3[200]={""};
            for (j=i; j<=strlen(formula); j++){
                if (formula[j]==')'){
                    strncpy(part3, formula+i+1, j-i-1);
                    break;
                }
            }
            strncpy(part1, formula, i);
            strncpy(part2, formula+j+1, strlen(formula)-j-1);
            sprintf(formula, "%lf", rec(part3));
            strcat(formula, part2);
            strcat(part1, formula);
            for (int i=0; i<200; i++) formula[i]='\0';
            strncpy(formula, part1, strlen(part1));
        }
    }
    
    for (long i=strlen(formula); i>=0; i--){
        if (formula[i]=='+'){
            char part1[200]={""}, part2[200]={""};
            strncpy(part1, formula, i);
            strncpy(part2, formula+i+1, strlen(formula)-i-1);
            for (int i=0; i<200; i++) formula[i]='\0';
            sprintf(formula, "%lf", rec(part1)+rec(part2));
        }
    }
    for (long i=strlen(formula); i>=0; i--){
        if (formula[i]=='-' && strchr(formula, '+')==0){
            char part1[200]={""}, part2[200]={""};
            strncpy(part1, formula, i);
            strncpy(part2, formula+i+1, strlen(formula)-i-1);
            for (int i=0; i<200; i++) formula[i]='\0';
            sprintf(formula, "%lf", rec(part1)-rec(part2));
        }
    }
    for (long i=strlen(formula); i>=0; i--){
        if (formula[i]=='*' && strchr(formula, '+')==0 && strchr(formula, '-')==0){
            char part1[200]={""}, part2[200]={""};
            strncpy(part1, formula, i);
            strncpy(part2, formula+i+1, strlen(formula)-i-1);
            for (int i=0; i<200; i++) formula[i]='\0';
            sprintf(formula, "%lf", rec(part1)*rec(part2));
        }
    }
    for (long i=strlen(formula); i>=0; i--){
        if (formula[i]=='/' && strchr(formula, '+')==0 && strchr(formula, '-')==0 && strchr(formula, '*')==0){
            char part1[200]={""}, part2[200]={""};
            strncpy(part1, formula, i);
            strncpy(part2, formula+i+1, strlen(formula)-i-1);
            for (int i=0; i<200; i++) formula[i]='\0';
            sprintf(formula, "%lf", rec(part1)/rec(part2));
        }
    }
    
    for (long i=strlen(formula)-1; i>=0; i--){
        if ((formula[i]=='^' && strchr(formula, '/')==0 && strchr(formula, '+')==0 && strchr(formula, '*')==0) && (strchr(formula, '-')==0 || strchr(formula, '*')+1==strchr(formula, '-') || strchr(formula, '/')+1==strchr(formula, '-') || strchr(formula, '^')+1==strchr(formula, '-'))){
            char part1[200]={""}, part2[200]={""};
            strncpy(part1, formula, i);
            strncpy(part2, formula+i+1, strlen(formula)-i-1);
            for (int i=0; i<200; i++) formula[i]='\0';
            sprintf(formula, "%lf", pow(rec(part1), rec(part2)));
        }
    }
    return atof(formula);
}

#endif

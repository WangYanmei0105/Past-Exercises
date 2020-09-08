#include<stdio.h>
#include <string.h>
/*
int main() {
    double num = 0;
    int sum = 0;//prime must be an int
    printf("Please input:\n");
    scanf("%lf", &num);//lf for double
    for (int i = 2; i <= num; i++) {
        int temp = i;//save i for loop
        int neg = 0;//see if it is a prime
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                neg = 1;
            }
        }
        if (neg == 0) {
            printf("%d\n", i);
            while (i > 10) {
                sum += i % 10;
                i =(i-i%10)/10;
            }
            sum += i;
            i = temp;
        }
    }
    printf("The digit sum is: %d.\n", sum);
    return 0;
}

*/
int main(){
    char ss[10]="12345678";
    long i=strlen(ss);
    
    
    return 0;
}




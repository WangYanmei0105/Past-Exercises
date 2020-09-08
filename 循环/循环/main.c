//
//  main.c
//  循环
//
//  Created by Amy Wang on 2019/8/18.
//  Copyright © 2019 Amy Wang. All rights reserved.
//

#include <stdio.h>

int main() {
//...
    
    while(1)
    {
        char in='y';
        scanf("%c",&in);
        if(in=='n')
            break;
    }
    return 0;
}

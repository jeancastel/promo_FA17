//
//  main.c
//  ex_10.3
//
//  Created by Maxime Renusson on 11/18/14.
//  Copyright (c) 2014 Maxime Renusson. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int i = 0;
    printf("Please input number to FACT :\n");
    scanf("%d",&i);
    int fact(int fact);
    printf("%d! = %d\n",i,fact(i));
    return 0;
}

int fact (int i){
    if (i==0) return 1;
    return i*fact(i-1);
}
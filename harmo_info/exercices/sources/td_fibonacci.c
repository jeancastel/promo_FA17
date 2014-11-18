//
//  main.c
//  td_fibonacci
//
//  Created by Maxime Renusson on 11/18/14.
//  Copyright (c) 2014 Maxime Renusson. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    printf("N ?\n");
    long int n = 0;
    scanf("%ld", &n);
    long int fibonacci (long int n);
    printf("%ld", fibonacci(n));
    return 0;
}

long int fibonacci (long int n){
    if (n<=0) return 0;
    if (n==1) return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}
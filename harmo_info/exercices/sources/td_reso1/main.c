//
//  main.c
//  td_reso1
//
//  Created by Maxime Renusson on 11/19/14.
//  Copyright (c) 2014 Maxime Renusson. All rights reserved.
//

#include <stdio.h>
#include "td_reso1_functions.h"

int main(int argc, const char * argv[]) {
    
    int a = 0;
    int b = 0;
    double x = 0;
    a = 5; b= 3;
    switch (reso1(a, b, &x)) {
        case 0:
            printf("There are no solution : INFINITE\n");
            break;
        case 1:
            printf("There are no solution : NULL\n");
            break;
        case 2:
            printf("There's one solution : %lf\n",x);
        default:
            break;
    }
    return 0;
}

int reso1(int a, int b, double * _px){
    if (a==0){
        if (b==0){
            return 0;                   //Infinite solutions
        }else
            return 1;                   //0 solutions
    }else{
        *_px = (double)(-b)/(double)a;  //ATTENTION : cast obligatoire pour résiltats OK
        return 2;                       //1 solution
    }

}
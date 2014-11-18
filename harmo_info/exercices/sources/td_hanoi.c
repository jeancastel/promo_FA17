//
//  main.c
//  td_hanoi
//
//  Created by Maxime Renusson on 11/18/14.
//  Copyright (c) 2014 Maxime Renusson. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    void hanoi(int n, int i, int j);
    
    hanoi(3,1,3);
    return 0;
}

void hanoi (int n, int i, int j){
    if (n>0){
        hanoi(n-1, i, 6-i-j);
        printf("%d -> %d\n",i,j);
        hanoi(n-1, 6-i-j, j);
    }

}
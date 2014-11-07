#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n = 0;
    int max = 0;
    while(n != -1){
        printf("\nPlease input a number (-1 to stop) : ");
        scanf("%d",&n);
        if (n>max){
            max = n;
	}
    }
    printf("\nThe max is : %d", max);
    return 0;
}

#include <stdio.h>

int main(int argc, const char * argv[]) {
    printf("N ?\n");
    long int n = 0;
    int i;
    scanf("%ld", &n);

    printf("\n\n");

    for(i = 0; i <= n; i++){
        long int fibonacci (long int i);
        printf("%d : %ld\n", i, fibonacci(i));
    }
    return 0;
}

long int fibonacci (long int n){
    if (n<=0) return 0;
    if (n==1) return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}

#include <stdio.h>
int main() {
int n=5;
double x=5.0;
printf("\nEssais de largeurs\n");
printf("%5d\n",n);
printf("%10d\n",n);
printf("%15d\n",n);
printf("\nEssais de précisions\n");
printf("%10.2f\n",x);
printf("%10.4f\n",x);
printf("%10.6f\n",x);
printf("\nEssais de justifications\n");
printf("%-10.2f\n",x);
printf("%+10.4f\n",x);
printf("%+10.4f\n",x);
printf("%010.4f\n",x);
printf("%+010.4f\n",x);
printf("\nEssais de notations scientifiques\n");
printf("%e\n",x);
printf("%10.2e\n",x);
printf("%10.2f\n",x);
printf("%10.2g\n",x);
printf("%10.2f\n",x);
printf("%10.2g\n",x);
printf("%10.2g\n",x);
printf("%010.2g\n",x);
return 0;
}

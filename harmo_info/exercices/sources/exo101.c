#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <tgmath.h>                                                 //nécessaire pour atan2

int main(int argc, const char * argv[]) {
    double rho = 0;                                                 //initialisation des var
    double theta = 0;
    double *prho = &rho;
    double *ptheta = &theta;
    double x = 0;
    double *px = &x;
    double y = 0;
    double *py = &y;
    int menuChoice = 0;
    void carToPol(double x,double y,double *prho,double *ptheta);   //init des fonctions de pointeurs
    void polToCar(double rho,double theta, double *px,double *py);
    printf("Please choose :\n");
    printf("1 - Cartesian to polar ? \n2 - Polar to Cartesian ?\n");
    scanf("%d", &menuChoice);
    switch (menuChoice) {
        case 1:
            printf("\nPlease input x : ");
            scanf("%lf", &x);
            printf("\nPlease input y : \n");
            scanf("%lf", &y);
            carToPol(x, y, prho, ptheta);
            printf("Rho : %f \nTheta : %f\n", rho, theta);
            break;
        case 2:
            printf("\nPlease input Rho : ");
            scanf("%lf", &rho);
            printf("\nPlease input Theta : \n");
            scanf("%lf", &theta);
            polToCar(rho, theta, px, py);
            printf("x : %f \ny : %f \n",x,y);
            break;
        default:
            printf("\nYou didn't choose either 1 or 2 !!!\nPlease try again !");
            break;
    }
    
}

void carToPol(double x,double y,double *prho,double *ptheta){
    *prho = sqrt(pow(x, 2.0)+pow(y, 2.0));
    *ptheta = atan2(x,y);
}

void polToCar(double rho,double theta,double *px,double *py){
    *px = rho * cos(theta);
    *py = rho * sin(theta);
}

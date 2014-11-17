#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <tgmath.h>                                                 //nécessaire pour atan2

int main(int argc, const char * argv[]) {
    double _rho = 0;                                                 //initialisation des var
    double _theta = 0;
    double _x = 0;
    double _y = 0;
    int menuChoice = 0;
    double rho(double _x,double _y);   //init des fonctions de pointeurs
    double theta(double _x,double _y);
    double x(double _rho,double _theta);
    double y(double _rho,double _theta);
    printf("Please choose :\n");
    printf("1 - Rho from cartesian ? \n2 - Theta from Cartesian ?\n3 - X from Polar ? \n4 - Y from Polar ?\n");
    scanf("%d", &menuChoice);
    switch (menuChoice) {
        case 1:
            printf("\nPlease input x : \n");
            scanf("%lf", &_x);
            printf("\nPlease input y : \n");
            scanf("%lf", &_y);
            printf("Rho : %lf \n",rho(_x,_y));
            break;
        case 2:
            printf("\nPlease input x : \n");
            scanf("%lf", &_x);
            printf("\nPlease input y : \n");
            scanf("%lf", &_y);
            printf("Theta : %lf \n",theta(_x,_y));
            break;
        case 3:
            printf("\nPlease input Rho : ");
            scanf("%lf", &_rho);
            printf("\nPlease input Theta : \n");
            scanf("%lf", &_theta);
            printf("x : %lf \n", x(_rho, _theta));
            break;
        case 4:
            printf("\nPlease input Rho : ");
            scanf("%lf", &_rho);
            printf("\nPlease input Theta : \n");
            scanf("%lf", &_theta);
            printf("y : %lf \n",y(_rho, _theta));
            break;
        default:
            printf("\nYou didn't choose either 1 or 2 or 3 or 4!!!\nPlease try again !");
            break;
    }
    
}

double rho(double x,double y){
    return sqrt(pow(x, 2.0)+pow(y, 2.0));
}
double theta(double x,double y){
    return atan2(x,y);
}
double x(double rho,double theta){
    return rho * cos(theta);
}
double y(double rho,double theta){
    return rho * sin(theta);
}

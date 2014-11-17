#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "header/lexical.h"
#include "header/declaration.h"
void MintoUpper (char * expression)
{ //Fonction qui passe les lettres minuscules en majuscules.
    int i;
    for (i = 0; expression[i] != '\0'; i++)
    {
        if((expression[i] > 96) && (expression[i] < 123))
        {
            expression[i] -= 32;
        }
    }
}
objet Analyse (char * expression)
{
    objet JetonActuel = (objet) malloc(sizeof(ana));
    objet premier = JetonActuel; // racine de la liste chaînée.
    int taille = strlen(expression);
    int i;
    objet fils = NULL;
    //parcours la chaine entrée par l'utilisateur.
    for (i = 0;i <= taille;i++)
    {
        //test sur chaque caractère de la chaîne.
        switch (expression[i])
        {
            // si le caractère est + alors lexem est associé à OPERATEUR et la valeur du jeton est PLUS
            case '+' :
                {
                    JetonActuel->jeton.lexem =OPERATEUR;
                    JetonActuel->jeton.valeur.operateur = PLUS;
                    fils = (objet) malloc(sizeof(ana));
                    JetonActuel->suiv=fils;
                    JetonActuel=fils;
                    break;
                }
                // Si c'est un espace passe au prochain caractère directement.
            case' ' :
                {
                    break;
                }
                // Même chose qu'avec le + mais ici avec *
            case '*' :
                {
                    JetonActuel->jeton.lexem =OPERATEUR;
                    JetonActuel->jeton.valeur.operateur = FOIS;
                    fils = (objet) malloc(sizeof(ana));
                    JetonActuel->suiv=fils;
                    JetonActuel=fils;
                    break;
                }
            case '-' :
                {
                    JetonActuel->jeton.lexem =OPERATEUR;
                    JetonActuel->jeton.valeur.operateur = MOINS;
                    fils = (objet) malloc(sizeof(ana));
                    JetonActuel->suiv=fils;
                    JetonActuel=fils;
                    break;
                }
            case '/' :
                {
                    JetonActuel->jeton.lexem =OPERATEUR;
                    JetonActuel->jeton.valeur.operateur = DIV;
                    fils = (objet) malloc(sizeof(ana));
                    JetonActuel->suiv=fils;
                    JetonActuel=fils;
                    break;
                }
            case '%' :
                {
                    JetonActuel->jeton.lexem =OPERATEUR;
                    JetonActuel->jeton.valeur.operateur = PUIS;
                    fils = (objet) malloc(sizeof(ana));
                    JetonActuel->suiv=fils;
                    JetonActuel=fils;
                    break;
                }
                //Parenthèse fermante , pas de valeur spéciale pour le jeton.
            case ')' :
                {
                    JetonActuel->jeton.lexem =PAR_FERM;
                    fils = (objet) malloc(sizeof(ana));
                    JetonActuel->suiv=fils;
                    JetonActuel=fils;
                    break;
                }
            case '(' :
                {
                    JetonActuel->jeton.lexem =PAR_OUV;
                    fils = (objet) malloc(sizeof(ana));
                    JetonActuel->suiv=fils;
                    JetonActuel=fils;
                    break;
                }
                /* Caractère qui signifie la fin de la chaîne.
                   valeur fin pour le jeton et NULL pour son fils.*/
            case '\0' :
                {
                    JetonActuel->jeton.lexem =FIN;
                    JetonActuel->suiv = NULL;
                    //JetonActuel->jeton.valeur = NULL;
                    break;
                }
                // Même cas que pour le caractère \0
            case '\n' :
                {
                    JetonActuel->jeton.lexem =FIN;
                    JetonActuel->suiv = NULL;
                    //JetonActuel->jeton.valeur = NULL;
                    break;
                }
                // Cas de la variable , aucune valeur pour le jeton.
            case 'X' :
                {
                    JetonActuel->jeton.lexem =VARIABLE;
                    //JetonActuel->jeton.valeur = NULL;
                    fils = (objet) malloc(sizeof(ana));
                    JetonActuel->suiv=fils;
                    JetonActuel=fils;
                    break;
                }
                // Si le caractère est un S
            case 'S' :
                {
                    // Teste si les deux suivant sont IN pour la fonction SIN , lexem associé à fonction et valeur à sin.
                    if(expression[i+1] == 'I' && expression[i+2] == 'N')
                    {
                        JetonActuel->jeton.lexem =FONCTION;
                        JetonActuel->jeton.valeur.operateur = SIN;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i +=2; //on passe directement au caractère N , pour que la boucle passe au prochain caractère avec l'auto incrémentation.
                    }
                    //Deuxième possibilité la fonction SQRT même travail.
                    else if (expression[i+1] == 'Q' && expression[i+2] == 'R' && expression[i+3] == 'T')
                    {
                        JetonActuel->jeton.lexem =FONCTION;
                        JetonActuel->jeton.valeur.operateur = SQRT;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i +=3; //De même le compteur est placé directement sur la dernière lettre.
                    }
                    /*Si la suite des caractères ne ressemblent pas à IN ou QRT alors c'est une erreur.
                      lexem est associé à erreur la valeur de l'erreur est FONC pour fonction. */
                    else
                    {
                        JetonActuel->jeton.lexem =ERREUR;
                        JetonActuel->jeton.valeur.erreur = FONC;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i=taille; // On sort directement de la boucle.
                        JetonActuel->jeton.lexem =FIN; // Le fils de l'erreur est la fin de chaîne.
                        JetonActuel->suiv = NULL;
                    }
                    break;
                }
            case 'C' :
                {
                    //même chose que pour SIN mais ici avec cos.
                    if(expression[i+1] == 'O' && expression[i+2] == 'S')
                    {
                        JetonActuel->jeton.lexem =FONCTION;
                        JetonActuel->jeton.valeur.operateur = COS;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i +=2;
                    }
                    //même chose si il y a une erreur , fils = fin et sorti de la boucle. qui sera le même scénario pour chaque fonction.
                    else
                    {
                        JetonActuel->jeton.lexem =ERREUR;
                        JetonActuel->jeton.valeur.erreur = FONC;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i=taille;
                        JetonActuel->jeton.lexem =FIN;
                        JetonActuel->suiv = NULL;
                    }
                    break;
                }
            case 'T' :
                {
                    if(expression[i+1] == 'A' && expression[i+2] == 'N')
                    {
                        JetonActuel->jeton.lexem =FONCTION;
                        JetonActuel->jeton.valeur.operateur = TAN;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i +=2;
                    }
                    else
                    {
                        JetonActuel->jeton.lexem =ERREUR;
                        JetonActuel->jeton.valeur.erreur = FONC;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i=taille;
                        JetonActuel->jeton.lexem =FIN;
                        JetonActuel->suiv = NULL;
                    }
                    break;
                }
            case 'E' :
                {
                    if(expression[i+1] == 'X' && expression[i+2] == 'P')
                    {
                        JetonActuel->jeton.lexem =FONCTION;
                        JetonActuel->jeton.valeur.operateur = EXP;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i +=2;
                    }
                    else
                    {
                        JetonActuel->jeton.lexem =ERREUR;
                        JetonActuel->jeton.valeur.erreur = FONC;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i=taille;
                        JetonActuel->jeton.lexem =FIN;
                        JetonActuel->suiv = NULL;
                    }
                    break;
                }
            case 'L' :
                {
                    if(expression[i+1] == 'O' && expression[i+2] == 'G')
                    {
                        JetonActuel->jeton.lexem =FONCTION;
                        JetonActuel->jeton.valeur.operateur = LOG;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i +=2;
                    }
                    else
                    {
                        JetonActuel->jeton.lexem =ERREUR;
                        JetonActuel->jeton.valeur.erreur = FONC;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i=taille;
                        JetonActuel->jeton.lexem =FIN;
                        JetonActuel->suiv = NULL;
                    }
                    break;
                }
            case 'A' :
                {
                    if(expression[i+1] == 'B' && expression[i+2] == 'S')
                    {
                        JetonActuel->jeton.lexem =FONCTION;
                        JetonActuel->jeton.valeur.operateur = ABS;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i +=2;
                    }
                    else
                    {
                        JetonActuel->jeton.lexem =ERREUR;
                        JetonActuel->jeton.valeur.erreur = FONC;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv=fils;
                        JetonActuel=fils;
                        i=taille;
                        JetonActuel->jeton.lexem =FIN;
                        JetonActuel->suiv = NULL;
                    }
                    break;
                }
                //Si le caractère n'est pas le premier caractère d'une fonction ou un opérateur ou une paranthèse ou alors une variable.
            default :
                {
                    //Si le caractère est chiffre.
                    if(expression[i]>47 && expression[i] < 58)
                    {
                        char tab[20];//Tableau qui recevra le nombre.
                        int compteur=0;
                        int point = 0;
                        // Parcours la chaîne jusqu'a trouvé le dernier chiffre, prise en compte du point pour les décimaux.
                        while(expression[i] > 47 && expression[i] < 58 || expression[i] == 46)
                        {
                            tab[compteur]=expression[i];
                            compteur++;
                            i++;
                            if(expression[i] ==46) // Compte le nombre de point dans la chaîne.
                                point++;
                        }
                        i--;
                        tab[compteur+1]='\0'; // Place le caractère de fin de chaîne sur le nouveau tableau.
                        if(point == 1) // Si le nombre de point est de 1
                        {
                            JetonActuel->jeton.valeur.reel = atof(tab); // Convertir la chaîne en float.
                            if(JetonActuel->jeton.valeur.reel < 0) { // Si le nombre est négative.
                                JetonActuel->jeton.lexem = VAL_NEG;
                            }
                            //Si le chiffre est positif.
                            else {
                                JetonActuel->jeton.lexem =REEL;
                                fils = (objet) malloc(sizeof(ana));
                                JetonActuel->suiv=fils;
                                JetonActuel=fils;
                            }
                            //Si le dernier chiffre du nombre est le dernier caractère de la chaîne. Fin de la liste chaînée.
                            if(i==taille) {
                                JetonActuel->jeton.lexem = FIN;
                                JetonActuel->suiv = NULL;
                            }
                        }
                        else if (point == 0) // Si le chiffre est un entier on place un point pour avoir un flottant.
                        {
                            tab[compteur]= '.';
                            tab[compteur +1 ]= '0';
                            tab[compteur +2 ]= '\0';
                            JetonActuel->jeton.valeur.reel = atof(tab);
                            if(JetonActuel->jeton.valeur.reel < 0) {
                                JetonActuel->jeton.lexem = VAL_NEG;
                            }
                            else {
                                JetonActuel->jeton.lexem = REEL;
                                fils = (objet) malloc(sizeof(ana));
                                JetonActuel->suiv = fils;
                                JetonActuel = fils;
                            }
                            if(i==taille) {
                                JetonActuel->jeton.lexem = FIN;
                                JetonActuel->suiv = NULL;
                            }
                        }
                        else // Si le nombre a plus de 1 point alors on passe dans une erreur.
                        {
                            JetonActuel->jeton.lexem =ERREUR;
                            JetonActuel->jeton.valeur.erreur = DOUBLE_POINTS;
                            fils = (objet) malloc(sizeof(ana));
                            JetonActuel->suiv=fils;
                            JetonActuel=fils;
                            JetonActuel->jeton.lexem =FIN;
                            JetonActuel->suiv = NULL;
                        }
                    }
                    //Si le caractère n'est pas pris en compte par aucun des test alors c'est une erreur.
                    else
                    {
                        JetonActuel->jeton.lexem =ERREUR;
                        JetonActuel->jeton.valeur.erreur = CARACTERE_INCONNU;
                        fils = (objet) malloc(sizeof(ana));
                        JetonActuel->suiv = fils;
                        JetonActuel = fils;
                        i=taille;
                        JetonActuel->jeton.lexem = FIN;
                        JetonActuel->suiv = NULL;
                    }
                    break;
                }
        }
    }
    return (premier); //Retourne la racine de la chaîne.
}
int main() {
    char chaine[100];
    objet monana = NULL;
    printf("Veuillez entrer une fonction : ");
    scanf("%s", chaine);
    monana = Analyse(chaine);
    return 0;
}

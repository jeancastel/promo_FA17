#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/declaration.h"
#include "lexical.c"
#include "syntaxique.c"
#include "evaluateur.c"
//#include "graph.c"
#define NB_MAX_CARACTERES 50

void affichageLigneVide()
{
    int a = 0;
    printf("\t");
    while(a < 62)
    {
        printf("*");
        a++;
    }
    printf("\n");
}

void affichageLigne(char * ligne)
{
    // 1 ligne - 78 caractères
    int a = 0, nbEspace = (60 - strlen(ligne)) / 2;
    printf("\t*");
    while(a < nbEspace)
    {
        printf(" ");
        a++;
    }
    printf(ligne);
    a = 0;
    //printf("\n\t*");
    while(a < nbEspace)
    {
        printf(" ");
        a++;
    }
    if(strlen(ligne)%2 != 0)
    {
        printf(" ");
    }
    printf("*\n");
}

void AfficherLISTE(objet p)
{
    while(p!=NULL)
    {
        printf("%d", p->jeton.lexem);
        if(p->jeton.lexem == REEL)
        {
            printf("%f", p->jeton.valeur.reel);
        }
        p = p->suiv;
    }
}

int main(int ac,char *av[])
{
    char reponse[NB_MAX_CARACTERES] = {0}, reponseSANSespace[NB_MAX_CARACTERES] = {0};
    char delimiteur[] = { ' ', '\n' };
    char * result = NULL;
    float borneInf, borneSup, pas;
    int choix, codeVerif = 0;
	objet liste_lexicale = NULL ;

    while(strcmp(reponseSANSespace, "FIN"))
    {
        // Effaçage de la console
        system("CLS");

        printf("\n\n");
        affichageLigneVide();
        affichageLigne("TB7 - GRAPHEUR EXPRESSION SYNTAXIQUE");
        affichageLigneVide();
        affichageLigne("");
        affichageLigne("Menu Principal");
        affichageLigne("");
        affichageLigneVide();
        affichageLigne("");
        affichageLigne("Veuillez rentrez votre expression : ");
        affichageLigne("");
        printf("\t\t\t");
        fgets(reponse, NB_MAX_CARACTERES, stdin);

        result = strtok(reponse, delimiteur);
        while(result != NULL)
        {
            strcat(reponseSANSespace, result);
            result = strtok(NULL, delimiteur);
        }

            // SI EXPRESSION RENTREE -> TRAITEMENT
			if((strcmp(reponseSANSespace, "FIN")) && (strcmp(reponseSANSespace, "")))
            {

            // MODULE 1 - ANALYSE LEXICALE
            MintoUpper(reponseSANSespace);
            liste_lexicale = Analyse(reponseSANSespace);

            // MODULE 2 - ANALYSE SYNTAXIQUE

            // RECHERCHE ERREUR
            codeVerif = verificationSyntaxique(liste_lexicale);

                // AFFICHAGE DE L'ERREUR SI IL Y A
                if(codeVerif != 0)
                {
                    affichageLigne("");
                    affichageLigne(tabERREUR[codeVerif]);
                    affichageLigne("");
                    printf("\t\t     ");
                    system("pause");
                } else {
                    // PAS D'ERREUR, ON GENERE L'ARBRE POUR L'EVALUATEUR
                    arbre aGenere = inserer(liste_lexicale);

                    affichageLigne("");
                    affichageLigne("Veuillez rentrez vos bornes pour visualiser la fonction");
                    affichageLigne("");
                    affichageLigne("Borne Inferieure :");
                    printf("\t\t\t\t     ");
                    scanf("%g", &borneInf);
                    affichageLigne("");
                    affichageLigne("Borne Superieure :");
                    printf("\t\t\t\t     ");
                    scanf("%g", &borneSup);
                    affichageLigne("");
                    affichageLigne("Pas de Calcul :");
                    printf("\t\t\t\t     ");
                    scanf("%g", &pas);
                    affichageLigne("");
                    affichageLigneVide();
                    affichageLigne("");
                    affichageLigne("Sous-Menu");
                    affichageLigne("");
                    affichageLigne("1 - Visualisez un tableau de Valeur");
                    affichageLigne("2 - Visualisez la courbe représentative");
                    affichageLigne("");
                    affichageLigne("0 pour Quitter");
                    affichageLigne("");
                    printf("\t\t\tVeuillez rentrez un choix : ");
                    scanf("%d", &choix);

                    if(choix != 0)
                    {
                        // CALCUL DES IMAGES DES POINTS ENTRE LES BORNES
                        couple tab = Ajouter_Valeurs(aGenere, borneInf, borneSup, pas);
						if(tab != NULL)
						{
							switch(choix)
							{
								case 1 :
                                    // AFFICHAGE DU TABLEAU DE POINTS
                                    affichage(tab);
                                    affichageLigne("");
                                    printf("\t\t   ");
                                    system("pause");
                                    break;
								case 2 :
                                    // COURBE
									GraphFinal(tab) ;
									InitGraph(ac,av,borneInf,borneSup,pas,"TRAÇAGE de la courbe", 1024, 720 ,myDraw ,myKey);
                                    break;
							}
						}

                    }
                }
                    choix = 0;
                    while(choix < NB_MAX_CARACTERES)
                    {
                        reponse[choix] = '\0';
                        reponseSANSespace[choix] = '\0';
                        choix++;
                    }
                    fflush(stdin);
            }
    }
    affichageLigne("");
    affichageLigneVide();
    return 0;
}

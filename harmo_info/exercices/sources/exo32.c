#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SECRET 100
#define MAX_TENTATIVES 12
int nombreSecret;
// le nombre à deviner
int nbJoueur;
// le nombre proposé par le joueur à chaque tour
int borneSup,borneInf; // les 2 bornes délimitant à chaque tour l'intervalle de recherche du joueur
int fini,gagne; // booleen : 0 pour false, 1 pour true. le joueur a-t-il fini, a-t-il gagné?

int main() {
	int i;
	/* tirage aleatoire d'un entier entre 0 et MAX_SECRET */
	srand(time(NULL));
	nombreSecret = rand()%MAX_SECRET;
	/* initilisation des variables d'etat */
	fini=0;
	gagne=0;
	i=0;
	borneSup=MAX_SECRET;
	borneInf=0;
	/* boucle interactive de saisie */
	while (!fini) {
		/* Affichage d'une invite proposant au
		   joueur d'entrer un nombre entre la borne inferieure
		   et la borne superieure */
		printf("\nVeuillez entrer un nombre entre %d et %d : ", borneInf, borneSup); 
		/*Saisie de la valeur choisie par le joueur
		   dans la variable nbJoueur */
		scanf("%d", &nbJoueur);
		/* comparaison */
		if (nombreSecret<nbJoueur) {
			i=i+1;
			borneSup=nbJoueur;
		printf("\nTROP GRAND !"); 
		}
		else if (nombreSecret>nbJoueur) {
			i=i+1;
			borneInf=nbJoueur;
		printf("\nTROP PETIT !"); 
		} else if (nombreSecret==nbJoueur) {
			gagne=1;
			fini=1;
		printf("\nGAGNE !"); 
		}
		if (i==MAX_TENTATIVES) {
			fini=1;
			gagne=0;
		}
	}
	if (!gagne) {
		/* affichage du message PERDU! suivi du nombre a deviner */
		printf("\nDesole, le nombre a deviner etait : %d\n",nombreSecret);
	}
	return 0;
}

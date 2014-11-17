#include "stdafx.h"
#include "evaluateur.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


Case* bloc, *preums;

void initialiser(){
	bloc = (Case*)malloc(sizeof(Case));
	preums = bloc;
}

//crée une pile à partir de l'arbre pour arriver à une expression postfixé
void empiler(feuille* racine){
	if (racine != NULL){
		empiler(racine->fils_g);
		empiler(racine->fils_d);
		ajouterListe(racine);
	}
}

//ajoute le type jeton à la liste et passe à la Case suivante
void ajouterListe(feuille* racine){

	bloc->jeton = racine->jeton;
	Case* newBloc = (Case*)malloc(sizeof(Case));
	// marque le fin de la liste par un NULL
	newBloc->next = NULL;
	bloc->next = newBloc;
	bloc = bloc->next;
}

//déroule la liste et affiche chacune des cases
void afficher_Liste(Case* first){
	Case* tmp = NULL;
	tmp = first;
	while (tmp->next != NULL){
		printf("%f", tmp->jeton.valeur.reel);
		tmp = tmp->next;
	}
}

void afficherListeTracage(list_tracage* tab){
	list_tracage* tmp = NULL;
	tmp = tab;
	while (tmp->suiv != NULL){
		printf("%lf = %lf \n", tmp->abscisse , tmp->ordonnee);
		tmp = tmp->suiv;
	}
}

int main(){
	typejeton jg, jd, jr;
	feuille g, d, racine;
	//creer les jetons 
	jg.lexem = REEL;
	jd.lexem = REEL;
	jr.lexem = OPERATEUR;
	jg.valeur.reel = 3;
	jd.valeur.reel = 4;
	jr.valeur.operateur = PLUS;
	// Feuille gauche
	g.jeton = jg;
	g.fils_d = NULL;
	g.fils_g = NULL;
	//feuille Droite
	d.jeton = jd;
	d.fils_d = NULL;
	d.fils_g = NULL;
	//créer le jeton racine
	racine.jeton = jr;
	racine.fils_d = &d;
	racine.fils_g = &g;
	racine.jeton = jr;
	initialiser();
	empiler(&racine);
	afficher_Liste(preums);
	list_tracage* res = calculer(preums, 1, 3, 10);
	afficherListeTracage(res);

	// permet de laisser la console ouverte
	int b = scanf("%lf", &b);

}


list_tracage* calculer(Case* instruct, int range, int min, int max)
{
	Case* debut = instruct;
	double gauche =0 , droit = 0;  // déclaration des 2 valeurs gauche et droit
	int x = 0;
	list_tracage* liste = (list_tracage*)malloc(sizeof(list_tracage)); //créé le premier maillon de la liste chainée liste
	list_tracage* premier = liste; //valeur pour conserver le premier maillon de la chaine
	if (range == 0){
		printf("ERREUR, RANGE != 0");
		exit(1);
	}

	int nbCalc = 0;
	//calcule le nombre de case
	nbCalc = (max - min) / range;

	//creation d'un tableau pour les résultats
	/*double** returnTab = (double**)malloc(sizeof(double*)*nbCalc);
	for (int i = 0; i < nbCalc; i++){
		returnTab[i] = (double*)malloc(sizeof(double) * 2);
	}*/

	//Calcul pour chacune des cases du tableau
	for (int idx = 0; idx < nbCalc; idx++)
	{
		// réinit valeurs
		gauche = 0;
		droit = 0;
		instruct = debut;
		x = idx*range;
		x = x + min;

		// boucle tant qu'on est pas à la derniére instruction du calcul
		while (instruct!= NULL)
		{
			if (instruct->jeton.lexem == VARIABLE)
			{
				if (gauche != 0)
				{
					droit = x;
				}
				else
				{
					gauche = x;
				}
			}

			if (instruct->jeton.lexem == REEL)    // récuperer la valeur de gauche ou de droite
			{
				if (gauche != 0)
				{
					droit = instruct->jeton.valeur.reel;
				}
				else
				{
					gauche = instruct->jeton.valeur.reel;
				}
			}

			if (instruct->jeton.lexem == OPERATEUR)   // faire le calcule si operateur
			{
				switch (instruct->jeton.valeur.operateur)
				{
				case PLUS:
					gauche = gauche + droit;
					break;
				case MOINS:
					gauche = gauche - droit;
					break;
				case FOIS:
					gauche = gauche * droit;
					break;
				case DIV:
					gauche = gauche / droit;
					break;
				case PUIS:
					gauche = pow(gauche, droit);
					break;
				}
			}
			if (instruct->jeton.lexem == FONCTION)        // faire le calcule si fonction ( en radian ? )
			{
				switch (instruct->jeton.valeur.fonction)
				{
				case ABS:
					gauche = abs(gauche);
					break;
				case SIN:
					gauche = sin(gauche);
					break;
				case SQRT:
					gauche = sqrt(gauche);
					break;
				case LOG:
					gauche = log(gauche);
					break;
				case COS:
					gauche = cos(gauche);
					break;
				case TAN:
					gauche = tan(gauche);
					break;
				case EXP:
					gauche = exp(gauche);
					break;
				}
			}
			instruct = instruct->next;
		}
		// ranger le résultat dans le tableau
		/*returnTab[idx][1] = gauche;
		returnTab[idx][0] = x;
		*/
		//Ranger dans la liste chainé
		liste->abscisse = x;
		liste->ordonnee = gauche;
		liste->suiv = (list_tracage*)malloc(sizeof(list_tracage));
		liste = liste->suiv;
		liste->suiv = NULL;
	}
	return premier;
}




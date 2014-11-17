#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "header/syntaxique.h"
#include "header/declaration.h"

int erreur;

arbre inserer(objet p)
{
	objet element = p,
		 finpar = NULL;
	arbre rac = NULL,
		  temp = NULL;
	int nbPar = 1,
		jetonPrec = -1;
		erreur = -1;

	// TANT QU'ON N'EST PAS ARRIVE A LA FIN
    while (element->jeton.lexem != FIN)
    {
			switch(element->jeton.lexem)
			{
				case OPERATEUR :
					// ON CHECKE LE PRECEDENT
					if(jetonPrec == -1 || ((jetonPrec == REEL) || (jetonPrec == PAR_FERM) || (jetonPrec == VARIABLE) || (jetonPrec == FIN)))
					{
						if(rac != NULL)
						{
							temp = rac;
							rac = NULL;
						}

						rac = (arbre) malloc(sizeof(feuille));
						rac->jeton.lexem = OPERATEUR;
                        rac->jeton.valeur.operateur = element->jeton.valeur.operateur;
                        rac->fils_d = NULL;	

						if(temp != NULL)
						{
							rac->fils_g = temp;
							temp = NULL;
						}
					} else {
						switch(jetonPrec)
						{
							case OPERATEUR : //DOUBLE OPERATEUR
								erreur = 10;
								break;
							case FONCTION : //FONCTION SUIVI D'UN OPERATEUR
								erreur = 11;
								break;
							case PAR_OUV : //PARENTHÈSE SUIVIE D'UN OPERATEUR
								erreur = 12;
								break;
							default: 
								erreur = 100;
								break;
						}
				}
				break;
			case FONCTION :
				// ON CHECKE LE PRECEDENT
				if(jetonPrec == -1 || ((jetonPrec == OPERATEUR) || (jetonPrec == PAR_OUV)  || (jetonPrec == FIN)))
				{
						rac = (arbre) malloc(sizeof(feuille));
						rac->jeton.lexem = FONCTION;
						rac->jeton.valeur.fonction = element->jeton.valeur.fonction;
						rac->fils_g = NULL;
						rac->fils_d = NULL;


						// DÉTERMINATION DE LA PARENTHESE FERMANTE CORRESPONDANTE
						finpar = element->suiv->suiv;
						while ((nbPar != 0) && (finpar->jeton.lexem != FIN)){
							if(finpar->jeton.lexem == PAR_OUV){
								nbPar = nbPar + 1 ;
							}
							if(finpar->jeton.lexem == PAR_FERM){
								nbPar = nbPar - 1 ;
							}
							if (nbPar != 0){
								finpar = finpar->suiv ;
							}
						}
						if(nbPar != 0)
						{
							//NOMBRE DE PARENTHESES INCORRECTES
							erreur = 101;
							break;
						} else {
							nbPar++;
							finpar->jeton.lexem = FIN;

							//PASSAGE DU SOUS-ARBRE AU FILS GAUCHE
							rac->fils_g = inserer(element->suiv->suiv);
							element = finpar;
						}
					} else {
						switch(jetonPrec)
						{
						case REEL : //REEL SUIVI PAR UNE FONCTION
							erreur = 20;
							break;
						case FONCTION : //FONCTION SUIVIE d'UNE FONCTION
							erreur = 21;
							break;
						case PAR_FERM : //PARENTHÈSE FERMANTE SUIVIE D'UNE FONCTION
							erreur = 22;
							break;
						case VARIABLE : //VARIABLE SUIVIE D'UNE FONCTION
							erreur = 23;
							break;
						default: 
								erreur = 100;
								break;
						}
					}
					break;
			case PAR_OUV :
				// ON CHECKE LE PRECEDENT
				if(jetonPrec == -1 || ((jetonPrec == OPERATEUR) || (jetonPrec == FONCTION) || (jetonPrec == PAR_OUV)  || (jetonPrec == FIN)))
				{
						// DÉTERMINATION DE LA PARENTHESE FERMANTE CORRESPONDANTE
						finpar = element->suiv;
						while ((nbPar != 0) && (finpar->jeton.lexem != FIN)){
							if(finpar->jeton.lexem == PAR_OUV){
								nbPar = nbPar + 1 ;
							}
							if(finpar->jeton.lexem == PAR_FERM){
								nbPar = nbPar - 1 ;
							}
							if (nbPar != 0){
								finpar = finpar->suiv ;
							}
						}
						if(nbPar != 0)
						{
							//NOMBRE DE PARENTHESES INCORRECTES
							erreur = 101;
							break;
						} else {
							nbPar++;
							finpar->jeton.lexem = FIN;

							if(rac == NULL)
							{
								rac = inserer(element->suiv);
							} else {
								rac->fils_d = inserer(element->suiv);
							}
						element = finpar;
						}
					} else {
						switch(jetonPrec)
						{
						case REEL : //REEL SUIVI PAR UNE PARENTHÈSE
							erreur = 30;
							break;
						case PAR_FERM : //PARENTHESE FERMANTE SUIVIE PAR UNE PARENTHESE OUVRANTE
							erreur = 31;
							break;
						case VARIABLE : //VARIABLE SUIVIE D'UNE PARENTHESE OUVRANTE
							erreur = 32;
							break;
						default: 
								erreur = 100;
								break;
						}
					}
				break;
			case FIN :
				// ON CHECKE LE PRECEDENT
				switch(jetonPrec)
						{
						case OPERATEUR : //OPERATEUR SUIVI DE LA FIN DE L'EXPRESSION
							erreur = 40;
							break;
						case FONCTION : //FONCTION SUIVIE DE LA FIN DE L'EXPRESSION
							erreur = 41;
							break;
						case PAR_OUV : //PARENTHÈSE OUVRANTE SUIVIE DE LA FIN DE L'EXPRESSION
							erreur = 42;
							break;
						default:
							erreur = 0;
							break;
						}
				break;
			case PAR_FERM :
					//NOMBRE DE PARENTHESES INCORRECTES
					erreur = 101;
					break;
			case REEL :
				// ON CHECKE LE PRECEDENT
				if(jetonPrec == -1 || ((jetonPrec == OPERATEUR) || (jetonPrec == PAR_OUV) || (jetonPrec == FIN)))
				{					
						if(rac != NULL)
						{
							temp = rac;
							rac = NULL;
						}

						rac = (arbre) malloc(sizeof(feuille));
						rac->jeton.lexem = REEL;
                        rac->jeton.valeur.reel = element->jeton.valeur.reel;
						rac->fils_g = NULL;
                        rac->fils_d = NULL;	

						if(temp != NULL)
						{
							temp->fils_d = rac;
							rac = temp;
							temp = NULL;
						}
				} else {
						switch(jetonPrec)
						{
						case REEL : //DEUX REELS QUI SE SUIVENT
							erreur = 50;
							break;
						case FONCTION: //FONCTION SUIVI D'UN REEL
							erreur = 51;
							break;
						case PAR_FERM : //PARENTHESE FERMANTE SUIVIE D'UN REEL
							erreur = 52;
							break;
						case VARIABLE : //REEL SUIVIE D'UNE VARIABLE
							erreur = 53;
							break;
						default: 
								erreur = 100;
								break;
						}
				}
				break;
			case VARIABLE :
				// ON CHECKE LE PRECEDENT
				if(jetonPrec == -1 || ((jetonPrec == OPERATEUR) || (jetonPrec == PAR_OUV) || (jetonPrec == FIN)))
				{	
						
				if(rac != NULL)
						{
							temp = rac;
							rac = NULL;
						}

						rac = (arbre) malloc(sizeof(feuille));
						rac->jeton.lexem = VARIABLE;
						rac->fils_g = NULL;
                        rac->fils_d = NULL;	

						if(temp != NULL)
						{
							temp->fils_d = rac;
							rac = temp;
							temp = NULL;
						}
				} else {
						switch(jetonPrec)
						{
						case REEL : //VARIABLE SUIVIE D'UN REEL
							erreur = 60;
							break;
						case FONCTION: //FONCTION SUIVI D'UNE VARIABLE
							erreur = 61;
							break;
						case PAR_FERM : //PARENTHESE FERMANTE SUIVIE D'UNE VARIABLE
							erreur = 62;
							break;
						case VARIABLE : //DEUX VARIABLE QUI SE SUIVENT
							erreur = 63;
							break;
						default: 
								erreur = 100;
								break;
						}
				}
				break;
			}
		if(erreur != -1)
		{
			element->jeton.lexem = FIN;
		} else {
			jetonPrec = element->jeton.lexem;
			element = element->suiv;
		}
	}
	if(erreur == -1)
	{	
		return rac;
	} else {
		return NULL;
	}
}

void Affichage(arbre p)
{
    if(p != NULL)
    {
        Affichage(p->fils_g);
        printf("%d", p->jeton.lexem);
        Affichage(p->fils_d);
    }
}



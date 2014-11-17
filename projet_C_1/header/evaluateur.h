#include "declaration.h"
//fonction qui prend en entré l'arbre et le resort sous forme d'un tableau trié de jeton
void empiler(feuille* racine);
void ajouterListe(feuille* racine);

void afficherTableau(double ** tab);
typedef struct Case
{
	typejeton jeton;
	struct Case* next;
} Case;
double** calculer(Case* instruct, int range, int min, int max);
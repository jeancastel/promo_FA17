/**************************
 * Includes
 *
 **************************/

#include <stdlib.h>//pour le random
#include "header/graph.h"
#include "math.h"
#include "header/glut.h"
#include "stdio.h"
#include "string.h"
#include <time.h>//pour le random en fonction du temps


char bascule=0;
float x = 0.7;//MAx du graph


double Xmax = 10;
double Xmin = -Xmax;
double Ymin = -Xmax;
double Ymax = Xmax;

double graduation = 1.0;

double zoom = 1;

double DecalageX = 0;
double DecalageY = 0;


typedef struct tracage
{
	double abscisse;
	double ordonnee;
	tracage * suiv;
} list_tracage;

typedef list_tracage * couple;


couple tab[100];// Tableau de valeurs aleatoires pour tracer une fonction aleatoire


void myKey(int c)
{
  switch(c)
  {
    case 'q':
      bascule=c;
      break;

	case 's':
		bascule=c;
		break;

	case 'd':
		bascule=c;
		break;

	case 'z':
		bascule=c;
		break;

	case 't':
		bascule=c;
		break;

	case 'e':
		bascule=c;
		break;

	case 'a':
		bascule=c;
		break;
	case 'r':
		bascule=c;
		break;
  }
}

void Tracer(couple prm)
{	
	double abs1,ordo1,abs2,ordo2;
	
	couple temp = prm;
	
	abs2 = prm->abscisse; //recupération du 1er point
	ordo2 = prm->ordonnee;
		
	temp = temp->suiv;

	if(temp != NULL)
	{
		while(temp != NULL)
		{
			abs1 = abs2;
			ordo1 = ordo2;

			abs2 = temp->abscisse;
			ordo2 = temp->ordonnee;		
			
			setcolor(1.0F,0.0F,0.0F); // met en couleur la courbe

			line((abs1*x)*zoom + DecalageX,(ordo1*x)*zoom + DecalageY,(abs2*x)*zoom + DecalageX,(ordo2*x)*zoom+DecalageY);//on multiplie par x pour la longueur max

			temp = temp->suiv;
		}
	}
	else
	{
		//si il n'y a qu'un point
		glBegin(GL_POINTS);
		glVertex2f(abs2*x,ordo2*x);
		glEnd();
	}
}


void myDraw(void)
{

  setcolor(1.0F,1.0F,1.0F);
  

  switch (bascule)
  {
    /* Trace un rectangle rouge a l'ecran si active
     * par appui de la touche 'a' */
	  
    /*setcolor(1.0F,0.0F,0.0F);
    bar(-0.5F,-0.5F,0.5F,0.5F);*/	  

  case'a':
	  zoom*=1.1;
	break;

  case'r':
	  zoom*=0.9;
	break;

  case't':
	  //Tracer(tab[0]);
	break;

  case'z':
	   DecalageY -= graduation*x*0.1; 
	break;

  case'q':
	   DecalageX += graduation*x*0.1;
	break;

  case's':
	   DecalageY += graduation*x*0.1;
	break;

  case'd':
	   DecalageX -= graduation*x*0.1;
	break;
  }

  if(bascule != 'e')
  {
	  Tracer(tab[0]);
  }

  setcolor(1.0F,1.0F,0.0F);
  outtextxy(-1.0,0.94,"a : Agrandir"); 
  outtextxy(-0.8,0.94,"/   r : Retrecir"); 
  outtextxy(-0.15,0.94,"t : Tracer");
  outtextxy(0.03,0.94,"/   e : Effacer");
  outtextxy(0.5,0.94,"z : Haut");
  outtextxy(-1.0,0.84,"s : Bas"); 
  outtextxy(-0.15,0.84,"q : Gauche");
  outtextxy(0.5,0.84,"d : Droite");  

  char g[10];
  sprintf(g,"%.2f",graduation);
  char aff[23] = "graduation : ";

  strcat(aff, g);

  outtextxy(0.6,-0.9, aff); 

  /*Tracage des axes*/
  
  
  setcolor(1.0F,1.0F,1.0F); // met en couleur la courbe

    double abs = fabs(Ymin)/(Ymax-Ymin);
  abs= -x+abs*x*2;

  line((-1*x)*zoom + DecalageX,(abs)*zoom + DecalageY,(1*x)*zoom + DecalageX,(abs)*zoom + DecalageY);//abscisse

  double ordo = fabs(Xmin)/(Xmax-Xmin);  
  ordo = -x+ordo*x*2;

  line((ordo)*zoom + DecalageX,(-1*x)*zoom + DecalageY,(ordo)*zoom + DecalageX,(1*x)*zoom + DecalageY);//ordonné


  double test1 = (Xmax-Xmin)/graduation;
  double pasX = x*2/test1;

  
  double test2 = (Ymax-Ymin)/graduation;
  double pasY = x*2/test2;

  
  for(float i=0;i<=(x*2);i+=pasX)
  {
	line((-x+i)*zoom + DecalageX,(-0.01+abs)*zoom + DecalageY,(-x+i)*zoom + DecalageX,(0.01+abs)*zoom + DecalageY);//grad abscisse
  }

  for(float i=0;i<=(x*2);i+=pasY)
  {
	line((-0.01+ordo)*zoom + DecalageX,(-x+i)*zoom + DecalageY,(0.01+ordo)*zoom + DecalageX,(-x+i)*zoom + DecalageY);// grad ordonnées
  }
  
  outtextxy(ordo-0.05 + DecalageX,abs-0.05+DecalageY,"0");

}

int main(int ac,char *av[])
{

	printf("Veuillez choisir une graduation (0 pour arrêter) : ");
	scanf("%lf",&graduation);

	/*********************************************** Debut a commenter *******************************************************************/

	double nb_alea = 0;

	double xmax = 10;
	int ymax = 10;

	int i = 0;

	for(i = 0; i <100;i++)
	{
		tab[i] = new list_tracage();
	}
	
	srand(time(NULL)); // initialisation de rand

	double abscisses = 0.0;

	for(i = 0; i <99;i++)
	{		
		nb_alea = (rand()% (ymax*2 +1)) - ymax;//aléa de -5 a 5

		tab[i]->abscisse = (-xmax + abscisses);
		tab[i]->ordonnee = (nb_alea);
		tab[i]->suiv = tab[i+1];

		abscisses += (xmax*2)/100;

		/*   //Fonction cosinus pour test

		tab[i]->abscisse = -10 + abscisses;
		tab[i]->ordonnee = cos(tab[i]->abscisse);
		tab[i]->suiv = tab[i+1];

		abscisses += (xmax*2)/100;
		*/

	}

	
	/*nb_alea = (rand()%(ymax*2 +1)) - ymax;//aléa de -5 a 5

	tab[99]->abscisse = xmax;	
	tab[99]->ordonnee = nb_alea;
	tab[99]->suiv = NULL;*/

	tab[99]->abscisse = xmax;	
	tab[99]->ordonnee = cos(tab[99]->abscisse);
	tab[99]->suiv = NULL;


	//Le tableau est plein	

	couple temp = tab[0];
	
	/**************************************************************** Fin de commentaire ********************************************************************/


	// on recherche ici les min et max

	double Xextremum, Yextremum;
	
	couple tempp;//tableau temporaire pour recuperer la premier adresse de temp
	tempp = temp;

	if(temp != NULL)
	{
		/******************************************** Recherche des extremums pour X et Y ********************************************/
		Xextremum = temp->abscisse;
		Yextremum = temp->ordonnee;

		while(temp != NULL)
		{
			if(Xextremum < fabs(temp->abscisse))
			{
				Xextremum = fabs(temp->abscisse);
			}

			if(Yextremum < fabs(temp->ordonnee))
			{
				Yextremum = fabs(temp->ordonnee);
			}

			temp = temp->suiv;
		}
		/************************************************* Fin de recherche des extremums ********************************************************/

		temp = tempp;// reaffectation de la premiere adresse de la chaine

		while(temp != NULL)
		{
			//division des x et y pour concoreder avec l'affichage dont le max est a 1
			temp->abscisse /= Xextremum;
			temp->ordonnee /= Yextremum;

			temp = temp->suiv;
		}

	}
	
	Xmin = -Xextremum;
	Xmax = Xextremum;
	Ymin = -Yextremum;
	Ymax = Yextremum;

	InitGraph(ac,av,"Essai Glut",960,800,myDraw,myKey);

	
	return 0;
}



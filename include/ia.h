#ifndef IA
#define IA

#include "humain.h"
float calculDistance (J joueur[],int p, int x0, int y0);
float calculDistance2 (char tableau[25][18], char *cibleActuelle, int k, int l);
void choixFinPartieIa (char tableau[25][18], J joueur[6], int p, char **pionSelectionne, char **cibleSelectionnee);
void meilleureCible (char tableau[25][18], J joueur[6], int p,char *orgine, char *pionSelectionne, char **cibleActuelle, float *valeurmin, int *idSaut, char *possibilite[24*16], int *q);
void initiliaserTableauDePointeur (char *tableau[]);
void initialiserTableauDePointeur2 (char *tableau[]);
char* choixIa (char tableau[25][18], J joueur[], int p, char *pionSelectionne, char **cibleSelectionnee, int *idSaut);
void ia (char tableau[25][18], J joueur[6], int p);

#endif

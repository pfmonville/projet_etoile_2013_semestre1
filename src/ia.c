#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "superviseur.h"
#include "pion.h"
#include "ia.h"

void initialiserTableauDePointeur (char *tableau[])  // est capable d'initialiser n'importe quel tableau de pointeur à une dimension
{
    int i;

    for (i=0; i<24*16; i++)
    {
//        if (tableau[i] == '\0') return;
        tableau[i] = NULL;
    }
}

void initialiserTableauDePointeur2 (char *tableau[])  // est capable d'initialiser n'importe quel tableau de pointeur à une dimension
{
    int i;

    for (i=0; i<9; i++)
    {
        tableau[i] = NULL;
    }
}

char afficherCibleIA (char *pionSelectionne, int idSaut, char *selection[10], int p)
{
	int k = 0;
	
    if (*(pionSelectionne-38) == '-' && *(pionSelectionne-19) != '-' && *(pionSelectionne-19) != ' ' && (p != 1) && ( p != 0)) //saut haut gauche
    	{*(pionSelectionne-38) = k+48; if (selection != NULL) selection[k] = pionSelectionne-38; k++;}
	if (*(pionSelectionne-72) == '-' && *(pionSelectionne-36) != '-' && *(pionSelectionne-36) != ' ' && (p != 1) && (p != 2)) //saut gauche
    	{*(pionSelectionne-72) = k+48; if (selection != NULL) selection[k] = pionSelectionne-72; k++;}
	if (*(pionSelectionne-34) == '-' && *(pionSelectionne-17) != '-' && *(pionSelectionne-17) != ' ' && (p != 3) && (p != 2)) //saut bas gauche
    	{*(pionSelectionne-34) = k+48; if (selection != NULL) selection[k] = pionSelectionne-34; k++;}
	if (*(pionSelectionne+38) == '-' && *(pionSelectionne+19) != '-' && *(pionSelectionne+19) != ' ' && (p != 3) && (p != 4)) //saut bas droite
        {*(pionSelectionne+38) = k+48; if (selection != NULL) selection[k] = pionSelectionne+38; k++;}
	if (*(pionSelectionne+72) == '-' && *(pionSelectionne+36) != '-' && *(pionSelectionne+36) != ' ' && (p != 4) && (p != 5)) //saut droite
        {*(pionSelectionne+72) = k+48; if (selection != NULL) selection[k] = pionSelectionne+72; k++;}
	if (*(pionSelectionne+34) == '-' && *(pionSelectionne+17) != '-' && *(pionSelectionne+17) != ' ' && (p != 0) && (p != 5)) //saut haut droite
        {*(pionSelectionne+34) = k+48; if (selection != NULL) selection[k] = pionSelectionne+34; k++;}
        
	if (idSaut == 0)	//premier tour on test les cases adjacentes
	{
		if (*(pionSelectionne-19) == '-' && (p != 1) && ( p != 0))
			{*(pionSelectionne-19) = k+48; if (selection != NULL) selection[k] = pionSelectionne-19; k++;}	//case en haut à gauche
		if (*(pionSelectionne-36) == '-' && (p != 1) && (p != 2))
			{*(pionSelectionne-36) = k+48; if (selection != NULL) selection[k] = pionSelectionne-36; k++;}	//case à gauche
		if (*(pionSelectionne-17) == '-' && (p != 3) && (p != 2))
			{*(pionSelectionne-17) = k+48; if (selection != NULL) selection[k] = pionSelectionne-17; k++;}	//case en bas à gauche
		if (*(pionSelectionne+19) == '-' && (p != 3) && (p != 4))
			{*(pionSelectionne+19) = k+48; if (selection != NULL) selection[k] = pionSelectionne+19; k++;}	//case en bas à droite
		if (*(pionSelectionne+36) == '-' && (p != 4) && (p != 5))
			{*(pionSelectionne+36) = k+48; if (selection != NULL) selection[k] = pionSelectionne+36; k++;}	//case à droite
		if (*(pionSelectionne+17) == '-' && (p != 0) && (p != 5))
			{*(pionSelectionne+17) = k+48; if (selection != NULL) selection[k] = pionSelectionne+17; k++;}	//case en haut à droite
	}
	
    return k;
}

void choixCibleIa (char tableau[25][18], int p, char *pionSelectionne, char **cibleSelectionnee, int *idSaut)
{
	int k;
	char *selectionCible[10];
	k = afficherCibleIA(pionSelectionne, *idSaut, selectionCible,  p);
    if(k != 0)
    {
        int choixCible = (int)rand()%k;
        *cibleSelectionnee = selectionCible[choixCible];
    }
    (*idSaut)++;
    nettoyerCible (tableau);
}

char* choixPionIa (char tableau[25][18], J joueur[], int p, char* pionSelectionne)
{
	int k;
    char *selectionPion[10];

    printf("Tour du Bot %c\n", joueur[p].pion);
    printf("\n");
    
    k = pionId(tableau, joueur, p, selectionPion);

    if(k != 0)
    {

        do
        {       
        	int choixPion= (int)rand()%k;
        	pionSelectionne = selectionPion[choixPion];
        }while(pionPlace(tableau, p, pionSelectionne));
    }
    nettoyerPion(tableau, joueur, p);
    return pionSelectionne;
}



void ia (char tableau[25][18], J joueur[6], int p)
{
	system("clear");
    int idSaut = 0;
    char *pionSelectionne = NULL, *cibleSelectionnee = NULL;
    changementBut(tableau, joueur, p);
    pionSelectionne = choixPionIa (tableau, joueur, p, pionSelectionne);
    choixCibleIa (tableau, p, pionSelectionne, &cibleSelectionnee, &idSaut);
    if (cibleSelectionnee != NULL)
    {

        deplacerPion(pionSelectionne, cibleSelectionnee);
    }
        	pionSelectionne = cibleSelectionnee;
    while(saut(pionSelectionne, cibleSelectionnee) && idSaut < 5)
    {

    	choixCibleIa(tableau, p, pionSelectionne, &cibleSelectionnee, &idSaut);
    	deplacerPion(pionSelectionne, cibleSelectionnee);
    	pionSelectionne = cibleSelectionnee;
    }
    
    afficherTableau(tableau);
    //sleep(1);
}

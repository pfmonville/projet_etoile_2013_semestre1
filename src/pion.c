#include <stdio.h>
#include <stdlib.h>

#include "superviseur.h"
#include "pion.h"


char testerPion (char *pionSelectionne)
{
	int k = 0;
    
	if((*(pionSelectionne-19) == '-') //la case en haut à gauche
       ||(*(pionSelectionne+19) == '-')  //la case en bas à droite
       ||(*(pionSelectionne-36) == '-')  //la case à gauche
       ||(*(pionSelectionne+36) == '-')  //la case à droite
       ||(*(pionSelectionne-17) == '-')  //la case en bas à gauche
       ||(*(pionSelectionne+17) == '-')  //la case en haut à droite
       ||(*(pionSelectionne-38) == '-' && *(pionSelectionne-19) != '-' && *(pionSelectionne-19) != ' ')  //saut en haut a gauche
       ||(*(pionSelectionne+38) == '-' && *(pionSelectionne+19) != '-' && *(pionSelectionne+19) != ' ')  //saut en bas a droite
       ||(*(pionSelectionne-72) == '-' && *(pionSelectionne-36) != '-' && *(pionSelectionne-36) != ' ')  //saut a gauche
       ||(*(pionSelectionne+72) == '-' && *(pionSelectionne+36) != '-' && *(pionSelectionne+36) != ' ')  //saut a droite
       ||(*(pionSelectionne-34) == '-' && *(pionSelectionne-17) != '-' && *(pionSelectionne-17) != ' ')  //saut en bas a gauche
       ||(*(pionSelectionne+34) == '-' && *(pionSelectionne+17) != '-' && *(pionSelectionne+17) != ' ')) //saut en haut a droite
		k = 1;
    
	return k;
}


int pionId (char tableau[][18], J joueur[], int p, char *selection[10])
{
	int i = 0,j = 0;
	char k = '0';
	
	nettoyerCible (tableau);
	for (j=0; j<18; j++)
	{
		for (i=0; i<25; i++)
		{
			if (tableau[i][j] == joueur[p].pion)
			{
				if (testerPion (&tableau[i][j]) != 0)
				{
					tableau[i][j] = k;
					if (selection != NULL)
	                    selection[k-48] = &tableau[i][j];  //permet d'enregistrer la position de chaque pion possible
                    k++;
				}
			}
		}
	}
    
    return k-48;
}


//renvoie 1 si le pion se trouve dans un camp adjacent
int campAdjacent (char tableau[25][18], int p, char *pionSelectionne)
{
    if ((p == 0 || p == 3) && pionPlace(tableau, 4, pionSelectionne) && pionPlace(tableau, 5, pionSelectionne) && pionPlace(tableau, 1, pionSelectionne) && pionPlace(tableau, 2, pionSelectionne))
        return 1;
    if ((p == 1  || p == 4) && pionPlace(tableau, 3, pionSelectionne) && pionPlace(tableau, 2, pionSelectionne) && pionPlace(tableau, 5, pionSelectionne) && pionPlace(tableau, 0, pionSelectionne))
        return 1;
    if ((p == 2 || p == 5) && pionPlace(tableau, 4, pionSelectionne) && pionPlace(tableau, 3, pionSelectionne) && pionPlace(tableau, 1, pionSelectionne) && pionPlace(tableau, 0, pionSelectionne))
        return 1;
    
    return 0;
}


static int pA = 0;
static int pB = 0;
static int pC = 0;
static int pD = 0;
static int pE = 0;
static int pF = 0;

int pionPlace (char tableau[25][18], int p, char *pionSelectionne) //renvoie 1 si pionSelectionne est dans le camp adverse
{
	if (p == 3)	//but joueur D (camp A)
	{
		if      (&tableau[12][0] == pionSelectionne && pA == 0){ ++pA; return 1;}
		else if (&tableau[11][1] == pionSelectionne && pA == 1){ ++pA; return 1;}
		else if (&tableau[13][1] == pionSelectionne && pA == 2){ ++pA; return 1;}
		else if (&tableau[10][2] == pionSelectionne && pA == 3){ ++pA; return 1;}
		else if (&tableau[12][2] == pionSelectionne && pA == 4){ ++pA; return 1;}
		else if (&tableau[14][2] == pionSelectionne && pA == 5){ ++pA; return 1;}
		else if (&tableau[9][3]  == pionSelectionne && pA == 6){ ++pA; return 1;}
		else if (&tableau[11][3] == pionSelectionne && pA == 7){ ++pA; return 1;}
		else if (&tableau[13][3] == pionSelectionne && pA == 8){ ++pA; return 1;}
		else if (&tableau[15][3] == pionSelectionne && pA == 9){ ++pA; return 1;}
	}
	
	if (p == 4) //but joueur E (camp B)
	{
		if      (&tableau[0][4] == pionSelectionne && pB == 0){ ++pB; return 1;}
		else if (&tableau[2][4] == pionSelectionne && pB == 1){ ++pB; return 1;}
		else if (&tableau[1][5] == pionSelectionne && pB == 2){ ++pB; return 1;}
		else if (&tableau[4][4] == pionSelectionne && pB == 3){ ++pB; return 1;}
		else if (&tableau[3][5] == pionSelectionne && pB == 4){ ++pB; return 1;}
		else if (&tableau[2][6] == pionSelectionne && pB == 5){ ++pB; return 1;}
		else if (&tableau[6][4] == pionSelectionne && pB == 6){ ++pB; return 1;}
		else if (&tableau[5][5] == pionSelectionne && pB == 7){ ++pB; return 1;}
		else if (&tableau[4][6] == pionSelectionne && pB == 8){ ++pB; return 1;}
		else if (&tableau[3][7] == pionSelectionne && pB == 9){ ++pB; return 1;}
	}
    
	if (p == 5) //but joueur F (camp C)
	{
		if      (&tableau[0][12] == pionSelectionne && pC == 0){ ++pC; return 1;}
		else if (&tableau[2][12] == pionSelectionne && pC == 1){ ++pC; return 1;}
		else if (&tableau[1][11] == pionSelectionne && pC == 2){ ++pC; return 1;}
		else if (&tableau[4][12] == pionSelectionne && pC == 3){ ++pC; return 1;}
		else if (&tableau[3][11] == pionSelectionne && pC == 4){ ++pC; return 1;}
		else if (&tableau[2][10] == pionSelectionne && pC == 5){ ++pC; return 1;}
		else if (&tableau[6][12] == pionSelectionne && pC == 6){ ++pC; return 1;}
		else if (&tableau[5][11] == pionSelectionne && pC == 7){ ++pC; return 1;}
		else if (&tableau[4][10] == pionSelectionne && pC == 8){ ++pC; return 1;}
		else if (&tableau[3][11] == pionSelectionne && pC == 9){ ++pC; return 1;}
	}
	
	if (p == 0) //but joueur A (camp D)
	{
		if      (&tableau[12][16] == pionSelectionne && pD == 0){ ++pD; return 1;}
		else if (&tableau[11][15] == pionSelectionne && pD == 1){ ++pD; return 1;}
		else if (&tableau[13][15] == pionSelectionne && pD == 2){ ++pD; return 1;}
		else if (&tableau[10][14] == pionSelectionne && pD == 3){ ++pD; return 1;}
		else if (&tableau[12][14] == pionSelectionne && pD == 4){ ++pD; return 1;}
		else if (&tableau[14][14] == pionSelectionne && pD == 5){ ++pD; return 1;}
		else if (&tableau[9][13]  == pionSelectionne && pD == 6){ ++pD; return 1;}
		else if (&tableau[11][13] == pionSelectionne && pD == 7){ ++pD; return 1;}
		else if (&tableau[13][13] == pionSelectionne && pD == 8){ ++pD; return 1;}
		else if (&tableau[15][13] == pionSelectionne && pD == 9){ ++pD; return 1;}
	}
	
	if (p == 1) //but joueur B (camp E)
	{
		if      (&tableau[24][12] == pionSelectionne && pE == 0){ ++pE; return 1;}
		else if (&tableau[22][12] == pionSelectionne && pE == 1){ ++pE; return 1;}
		else if (&tableau[23][11] == pionSelectionne && pE == 2){ ++pE; return 1;}
		else if (&tableau[20][12] == pionSelectionne && pE == 3){ ++pE; return 1;}
		else if (&tableau[21][11] == pionSelectionne && pE == 4){ ++pE; return 1;}
		else if (&tableau[22][10] == pionSelectionne && pE == 5){ ++pE; return 1;}
		else if (&tableau[18][12] == pionSelectionne && pE == 6){ ++pE; return 1;}
		else if (&tableau[19][11] == pionSelectionne && pE == 7){ ++pE; return 1;}
		else if (&tableau[20][10] == pionSelectionne && pE == 8){ ++pE; return 1;}
		else if (&tableau[21][9]  == pionSelectionne && pE == 9){ ++pE; return 1;}
	}
    
	if (p == 2) //but joueur C (camp F)
	{
		if      (&tableau[24][4] == pionSelectionne && pF == 0){ ++pF; return 1;}
		else if (&tableau[22][4] == pionSelectionne && pF == 1){ ++pF; return 1;}
		else if (&tableau[23][5] == pionSelectionne && pF == 2){ ++pF; return 1;}
		else if (&tableau[20][4] == pionSelectionne && pF == 3){ ++pF; return 1;}
		else if (&tableau[21][5] == pionSelectionne && pF == 4){ ++pF; return 1;}
		else if (&tableau[22][7] == pionSelectionne && pF == 5){ ++pF; return 1;}
		else if (&tableau[18][4] == pionSelectionne && pF == 6){ ++pF; return 1;}
		else if (&tableau[19][5] == pionSelectionne && pF == 7){ ++pF; return 1;}
		else if (&tableau[20][6] == pionSelectionne && pF == 8){ ++pF; return 1;}
		else if (&tableau[21][7] == pionSelectionne && pF == 9){ ++pF; return 1;}
	}
	
    return 0;
}

char afficherCible (char *pionSelectionne, int idSaut, char *selection[10])
{
	int k = 0;
	
    if (*(pionSelectionne-38) == '-' && *(pionSelectionne-19) != '-' && *(pionSelectionne-19) != ' ') //saut haut gauche
    	{*(pionSelectionne-38) = k+48; if (selection != NULL) selection[k] = pionSelectionne-38; k++;}
	if (*(pionSelectionne-72) == '-' && *(pionSelectionne-36) != '-' && *(pionSelectionne-36) != ' ') //saut gauche
    	{*(pionSelectionne-72) = k+48; if (selection != NULL) selection[k] = pionSelectionne-72; k++;}
	if (*(pionSelectionne-34) == '-' && *(pionSelectionne-17) != '-' && *(pionSelectionne-17) != ' ') //saut bas gauche
    	{*(pionSelectionne-34) = k+48; if (selection != NULL) selection[k] = pionSelectionne-34; k++;}
	if (*(pionSelectionne+38) == '-' && *(pionSelectionne+19) != '-' && *(pionSelectionne+19) != ' ') //saut bas droite
        {*(pionSelectionne+38) = k+48; if (selection != NULL) selection[k] = pionSelectionne+38; k++;}
	if (*(pionSelectionne+72) == '-' && *(pionSelectionne+36) != '-' && *(pionSelectionne+36) != ' ') //saut droite
        {*(pionSelectionne+72) = k+48; if (selection != NULL) selection[k] = pionSelectionne+72; k++;}
	if (*(pionSelectionne+34) == '-' && *(pionSelectionne+17) != '-' && *(pionSelectionne+17) != ' ') //saut haut droite
        {*(pionSelectionne+34) = k+48; if (selection != NULL) selection[k] = pionSelectionne+34; k++;}
        
	if (idSaut == 0)	//premier tour on test les cases adjacentes
	{
		if (*(pionSelectionne-19) == '-')
			{*(pionSelectionne-19) = k+48; if (selection != NULL) selection[k] = pionSelectionne-19; k++;}	//case en haut à gauche
		if (*(pionSelectionne-36) == '-')
			{*(pionSelectionne-36) = k+48; if (selection != NULL) selection[k] = pionSelectionne-36; k++;}	//case à gauche
		if (*(pionSelectionne-17) == '-')
			{*(pionSelectionne-17) = k+48; if (selection != NULL) selection[k] = pionSelectionne-17; k++;}	//case en bas à gauche
		if (*(pionSelectionne+19) == '-')
			{*(pionSelectionne+19) = k+48; if (selection != NULL) selection[k] = pionSelectionne+19; k++;}	//case en bas à droite
		if (*(pionSelectionne+36) == '-')
			{*(pionSelectionne+36) = k+48; if (selection != NULL) selection[k] = pionSelectionne+36; k++;}	//case à droite
		if (*(pionSelectionne+17) == '-')
			{*(pionSelectionne+17) = k+48; if (selection != NULL) selection[k] = pionSelectionne+17; k++;}	//case en haut à droite
	}
	
    return k;
}



void deplacerPion (char *pionSelectionne,char *cibleSelectionnee)
{
	if (cibleSelectionnee != NULL)  //si une cible a été choisie (sera faux lorsque le joueur voudra passer)
    {
        *cibleSelectionnee = *pionSelectionne;		//cible prend le caractère de la case pion
        *pionSelectionne = '-';						//nécessairement la case pion redevient un '-'
    }
}


int saut (char *pionSelectionne, char *cibleSelectionnee)
{
    if ((cibleSelectionnee == (pionSelectionne-72) || cibleSelectionnee == (pionSelectionne+72) || cibleSelectionnee == (pionSelectionne-38) || cibleSelectionnee == (pionSelectionne+38) || cibleSelectionnee == (pionSelectionne-34) || cibleSelectionnee== (pionSelectionne+34)))
        return 1;
    return 0;
}

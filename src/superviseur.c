#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sstdin.h"
#include "superviseur.h"
#include "sauvegarde.h"


void initialiserJoueur (J joueur[6])
{
	joueur[0].pion = 'A';
	joueur[0].butx = 12;
	joueur[0].buty = 16;
    joueur[0].butox = 12;
	joueur[0].butoy = 16;
	joueur[0].humain = 0;
	
	joueur[1].pion = 'B';
	joueur[1].butx = 24;
	joueur[1].buty = 12;
    joueur[1].butox = 24;
	joueur[1].butoy = 12;
	joueur[1].humain = 0;
	
	joueur[2].pion = 'C';
	joueur[2].butx = 24;
	joueur[2].buty = 4;
    joueur[2].butox = 24;
	joueur[2].butoy = 4;
	joueur[2].humain = 0;
	
	joueur[3].pion = 'D';
	joueur[3].butx = 12;
	joueur[3].buty = 0;
    joueur[3].butox = 12;
	joueur[3].butoy = 0;
	joueur[3].humain = 0;
	
	joueur[4].pion = 'E';
	joueur[4].butx = 0;
	joueur[4].buty = 4;
    joueur[4].butox = 0;
	joueur[4].butoy = 4;
	joueur[4].humain = 0;
	
	joueur[5].pion = 'F';
	joueur[5].butx = 0;
	joueur[5].buty = 12;
    joueur[5].butox = 0;
	joueur[5].butoy = 12;
	joueur[5].humain = 0;
}



void initialiserTableau(char tableau[][18])
{
	int i, j; /* index des boucles for */
	char c; /* caractère lu */
    FILE* fichier = NULL; /* pointeur sur le fichier du plateau */

	fichier = fopen("tableau.txt", "r");
	if (fichier != NULL)
    {
		for (j = 0; j < 18; j++)
        {
			for (i = 0; i < 25; i++)
            {
				do
                {
					c = fgetc(fichier);
				}while(c == '\n');
				tableau[i][j] = c;
			}
		}
		fclose(fichier);
	}
	else
    {
        printf("Erreur dans l'ouverture du fichier du plateau\n");
	}
}


void afficherTableau(char tableau[][18])
{
	int i, j; /* index des boucles for */

	for (i = 0; i < 18; i++)
	{
		for (j = 0; j < 25; j++)
		{
			printf("%c", tableau[j][i]);
		}
        printf("\n");
	}
}


void menu(char tableau[25][18], int *nombreJoueur, J joueur[6], int *p)
{
	char saisie [20];
    char lettre_joueur[] = {'A', 'B', 'C', 'D', 'E', 'F'}; /* ordre de jeu */
	int identifiant_joueur[] = {0, 1, 2, 3, 4, 5}, suite[] = {1,3,5,2,4,6}; /* identifiant correspondant aux joueurs dans l'ordre */
	int i, j, k;

	/* affichage du menu */
	printf("Dames chinoises\n");
	printf("par Alexandre Le Roy et Pierre-Francois Monville\n");
	printf("\n");

	/* saisie du nombre de joueurs par l'utilisateur */
	do {
		printf("Sélection du nombre de joueurs : 1 - 6\n");
		printf(">> ");
        *nombreJoueur = readInt();
        if (*nombreJoueur == 42)    
        {
            printf("vous ne pouvez pas quitter maintenant\n");
        }
        else if (*nombreJoueur == 43)
        {
            printf("vous ne pouvez pas revenir en arrière maintenant\n");
        }
        else if (*nombreJoueur == 44)
        {
            printf("vous ne pouvez pas passer maintenant\n");
        }
        else if (*nombreJoueur == 45)
        {
            charger(tableau, joueur, p, nombreJoueur);
            if (*nombreJoueur != 45)    //si le fichier c'est ouvert normalement on passe à la suite
                return;
           
        }

    } while (*nombreJoueur != 1
		&& *nombreJoueur != 2
		&& *nombreJoueur != 3
		&& *nombreJoueur != 4
		&& *nombreJoueur != 5
		&& *nombreJoueur != 6);

	/* traitement de la saisie */
	for (i = 0; i < 6; i++)
	{
		system("clear");
        printf("\n\n");
		afficherTableau(tableau);

		/* saisie de la nature du joueur */
        if (suite[i] <= *nombreJoueur)
        {
            printf("Joueur %c humain ? o/n\n", lettre_joueur[i]);
            printf(">> ");
            readStr(saisie, 20);
        
            if (saisie[0] == 'o' || saisie[0] == 'O')
            {
                joueur[identifiant_joueur[i]].humain = 1;
            }
        }
	}
    /*on supprime le camp d'un joueur si le nombre de joueurs est impair*/
    if (*nombreJoueur == 1)
        k = 3;
    else if (*nombreJoueur == 3)
        k = 4;
    else if (*nombreJoueur == 5)
        k = 5;
    else
        k = 0;
    
	if (k != 0)
    {
        for (j = 0; j < 18; j++)
        {
            for (i = 0; i < 25; i++)
            {
                if (tableau[i][j] == joueur[k].pion)
                    tableau[i][j] = '-';
            }
        }
    }
    
    *p = 0; //on définit le premier joueur
}

void changementBut(char tableau[25][18], J joueur[6], int p)
{
	if (p == 3)	//but joueur D (camp A)
	{
		if (tableau[12][0] == '-') {joueur[3].butx = 12; joueur[3].buty = 0;}
		else if (tableau[11][1] == '-') {joueur[3].butx = 11; joueur[3].buty = 1;}
		else if (tableau[13][1] == '-') {joueur[3].butx = 13; joueur[3].buty = 1;}
		else if (tableau[10][2] == '-') {joueur[3].butx = 10; joueur[3].buty = 2;}
		else if (tableau[12][2] == '-') {joueur[3].butx = 12; joueur[3].buty = 2;}
		else if (tableau[14][2] == '-') {joueur[3].butx = 14; joueur[3].buty = 2;}
		else if (tableau[9][3]  == '-') {joueur[3].butx = 9 ; joueur[3].buty = 3;}
		else if (tableau[11][3] == '-') {joueur[3].butx = 11; joueur[3].buty = 3;}
		else if (tableau[13][3] == '-') {joueur[3].butx = 13; joueur[3].buty = 3;}
		else if (tableau[15][3] == '-') {joueur[3].butx = 15; joueur[3].buty = 3;}
	}
	
	if (p == 4) //but joueur E (camp B)
	{
		if (tableau[0][4] == '-') {joueur[4].butx = 0; joueur[4].buty = 4;}
		else if (tableau[2][4] == '-') {joueur[4].butx = 2; joueur[4].buty = 4;}
		else if (tableau[1][5] == '-') {joueur[4].butx = 1; joueur[4].buty = 5;}
		else if (tableau[4][4] == '-') {joueur[4].butx = 4; joueur[4].buty = 4;}
		else if (tableau[3][5] == '-') {joueur[4].butx = 3; joueur[4].buty = 5;}
		else if (tableau[2][6] == '-') {joueur[4].butx = 2; joueur[4].buty = 6;}
		else if (tableau[6][4] == '-') {joueur[4].butx = 6; joueur[4].buty = 4;}
		else if (tableau[5][5] == '-') {joueur[4].butx = 5; joueur[4].buty = 5;}
		else if (tableau[4][6] == '-') {joueur[4].butx = 4; joueur[4].buty = 6;}
		else if (tableau[3][7] == '-') {joueur[4].butx = 3; joueur[4].buty = 7;}
	}
	
	if (p == 5) //but joueur F (camp C)
	{
		if (tableau[0][12] == '-') {joueur[5].butx = 0; joueur[5].buty = 12;}
		else if (tableau[2][12] == '-') {joueur[5].butx = 2; joueur[5].buty = 12;}
		else if (tableau[1][11] == '-') {joueur[5].butx = 1; joueur[5].buty = 11;}
		else if (tableau[4][12] == '-') {joueur[5].butx = 4; joueur[5].buty = 12;}
		else if (tableau[3][11] == '-') {joueur[5].butx = 3; joueur[5].buty = 11;}
		else if (tableau[2][10] == '-') {joueur[5].butx = 2; joueur[5].buty = 10;}
		else if (tableau[6][12] == '-') {joueur[5].butx = 6 ; joueur[5].buty = 12;}
		else if (tableau[5][11] == '-') {joueur[5].butx = 5; joueur[5].buty = 11;}
		else if (tableau[4][10] == '-') {joueur[5].butx = 4; joueur[5].buty = 10;}
		else if (tableau[3][11] == '-') {joueur[5].butx = 3; joueur[5].buty = 11;}
	}
    
	if (p == 0) //but joueur A (camp D)
	{
		if (tableau[12][16] == '-') {joueur[0].butx = 12; joueur[0].buty = 16;}
		else if (tableau[11][15] == '-') {joueur[0].butx = 11; joueur[0].buty = 15;}
		else if (tableau[13][15] == '-') {joueur[0].butx = 13; joueur[0].buty = 15;}
		else if (tableau[10][14] == '-') {joueur[0].butx = 10; joueur[0].buty = 14;}
		else if (tableau[12][14] == '-') {joueur[0].butx = 12; joueur[0].buty = 14;}
		else if (tableau[14][14] == '-') {joueur[0].butx = 14; joueur[0].buty = 14;}
		else if (tableau[9][13]  == '-') {joueur[0].butx = 9 ; joueur[0].buty = 13;}
		else if (tableau[11][13] == '-') {joueur[0].butx = 11; joueur[0].buty = 13;}
		else if (tableau[13][13] == '-') {joueur[0].butx = 13; joueur[0].buty = 13;}
		else if (tableau[15][13] == '-') {joueur[0].butx = 15; joueur[0].buty = 13;}
	}
	
	if (p == 1) //but joueur B (camp E)
	{
		if (tableau[24][12] == '-') {joueur[1].butx = 24; joueur[1].buty = 12;}
		else if (tableau[22][12] == '-') {joueur[1].butx = 22; joueur[1].buty = 12;}
		else if (tableau[23][11] == '-') {joueur[1].butx = 23; joueur[1].buty = 11;}
		else if (tableau[20][12] == '-') {joueur[1].butx = 20; joueur[1].buty = 12;}
		else if (tableau[21][11] == '-') {joueur[1].butx = 21; joueur[1].buty = 11;}
		else if (tableau[22][10] == '-') {joueur[1].butx = 22; joueur[1].buty = 10;}
		else if (tableau[18][12] == '-') {joueur[1].butx = 18; joueur[1].buty = 12;}
		else if (tableau[19][11] == '-') {joueur[1].butx = 19; joueur[1].buty = 11;}
		else if (tableau[20][10] == '-') {joueur[1].butx = 20; joueur[1].buty = 10;}
		else if (tableau[21][9]  == '-') {joueur[1].butx = 21; joueur[1].buty = 9;}
	}
	
	if (p == 2) //but joueur C (camp F)
	{
		if (tableau[24][4] == '-') {joueur[2].butx = 24; joueur[2].buty = 4;}
		else if (tableau[22][4] == '-') {joueur[2].butx = 22; joueur[2].buty = 4;}
		else if (tableau[23][5] == '-') {joueur[2].butx = 23; joueur[2].buty = 5;}
		else if (tableau[20][4] == '-') {joueur[2].butx = 20; joueur[2].buty = 4;}
		else if (tableau[21][5] == '-') {joueur[2].butx = 21; joueur[2].buty = 5;}
		else if (tableau[22][7] == '-') {joueur[2].butx = 22; joueur[2].buty = 7;}
		else if (tableau[18][4] == '-') {joueur[2].butx = 18; joueur[2].buty = 4;}
		else if (tableau[19][5] == '-') {joueur[2].butx = 19; joueur[2].buty = 5;}
		else if (tableau[20][6] == '-') {joueur[2].butx = 20; joueur[2].buty = 6;}
		else if (tableau[21][7] == '-') {joueur[2].butx = 21; joueur[2].buty = 7;}
	}
}

void nettoyerPion (char tableau[25][18], J joueur[], int p)
{
	int i,j;
    
	for (j=0; j<18; j++)
	{
		for (i=0; i<25; i++)
		{
			if (tableau[i][j] >= 48 && tableau[i][j] <= 57) tableau[i][j] = joueur[p].pion;	// si on tombe sur un chiffre on remplace par le pion du joueur
		}
	}
}


void nettoyerCible (char tableau[25][18])
{
	int i,j;
    
	for (j=0; j<18; j++)
	{
		for (i=0; i<25; i++)
		{
			if (tableau[i][j] >= 48 && tableau[i][j] <= 57) tableau[i][j] = '-';	// si on tombe sur un chiffre on remplace par un tiret
		}
	}
}

int chercherDansTableau (char tableau[25][18], char *possibilite[24*16], int i, int j)
{
    int k;
    
    for (k=0; k<(16*24); k++)
    {
        if (&tableau[i][j] == possibilite[k])   return 1;
//        if (possibilite[k] == '\0') break;  //ça évite de faire les 24*16 possibilités bêtement
    }
    
    return 0;
}

int enregistrerQuitter (char tableau[25][18], J joueur[], int p, int nombreJoueur)
{
    char chaine[10];
    
    printf("êtes-vous sûr de vouloir quitter ? (o/n)\n>>");
    readStr(chaine, 10);
    if (chaine[0] == 'y' || chaine[0] == 'Y' || chaine[0] == 'o' || chaine[0] == 'O')
    {
        printf ("Voulez-vous enregistrer ? (o/n)\n>>");
        readStr (chaine, 10);
        if(chaine[0] == 'y' || chaine[0] == 'Y' || chaine[0] == 'o' || chaine[0] == 'O')
        {
            sauvegarder(tableau, joueur, p, nombreJoueur);
        }
        exit(EXIT_SUCCESS); // on quitte qu'il enregistre ou pas
    }
    return 1;
}


void debutJeu(char tableau[25][18], J joueur[6], int *nombreJoueur, int *p)
{
	system("clear");
	initialiserJoueur(joueur);
	initialiserTableau(tableau);
	menu(tableau, nombreJoueur, joueur, p);
}


int prochainJoueur (int nombreJoueur, int p)
{
	int i, k = 0;
    int suite[] = {1,3,5,2,4,6};
    
    for (i = 0; i < 6; i++)
	{
        if (suite[i] <= nombreJoueur)
        {
            if (k == 1)
            {
                return i;
            }
            if (i == p)
                k = 1;
        }
	}
    return 0;
}



int gagner(char tableau[][18], char *joueurGagnant)
{
	if(tableau[12][0]=='D'&&tableau[11][1]=='D'&&tableau[13][1]=='D'&&tableau[10][2]=='D'&&tableau[12][2]=='D'&&tableau[14][2]=='D'&&tableau[9][3]=='D'&&tableau[11][3]=='D'&&tableau[13][3]=='D'&&tableau[15][3]=='D')
    {
		*joueurGagnant='D';
        return 0;
    }
    else if(tableau[9][13]=='A'&&tableau[11][13]=='A'&&tableau[13][13]=='A'&&tableau[15][13]=='A'&&tableau[10][14]=='A'&&tableau[12][14]=='A'&&tableau[14][14]=='A'&&tableau[11][15]=='A'&&tableau[13][15]=='A'&&tableau[12][16]=='A')
    {
		*joueurGagnant='A';
        return 0;
    }
    else if(tableau[0][4]=='E'&&tableau[2][4]=='E'&&tableau[4][4]=='E'&&tableau[6][4]=='E'&&tableau[1][5]=='E'&&tableau[3][5]=='E'&&tableau[5][5]=='E'&&tableau[2][6]=='E'&&tableau[4][6]=='E'&&tableau[3][7]=='E')
    {
		*joueurGagnant='E';
        return 0;
    }
    else if(tableau[21][9]=='B'&&tableau[20][10]=='B'&&tableau[22][10]=='B'&&tableau[19][11]=='B'&&tableau[21][11]=='B'&&tableau[23][11]=='B'&&tableau[18][12]=='B'&&tableau[20][12]=='B'&&tableau[22][12]=='B'&&tableau[24][12]=='B')
    {
		*joueurGagnant='B';
        return 0;
    }
    else if(tableau[3][9]=='F'&&tableau[2][10]=='F'&&tableau[4][10]=='F'&&tableau[1][11]=='F'&&tableau[3][11]=='F'&&tableau[5][11]=='F'&&tableau[0][12]=='F'&&tableau[2][12]=='F'&&tableau[4][12]=='F'&&tableau[6][12]=='F')
    {
		*joueurGagnant='F';
        return 0;
	}
    else if (tableau[18][4] == 'C' && tableau[20][4] == 'C' && tableau[22][4] == 'C' && tableau[24][4] == 'C' && tableau[19][5] == 'C' && tableau[21][5] == 'C' && tableau[23][5] == 'C' && tableau[20][6] == 'C' && tableau[22][6] == 'C' && tableau[21][7] == 'C')
	{
        *joueurGagnant='C';
        return 0;
    }
    else
        return 1;
}


int recommencer(char joueurGagnant)
{
    char recommencer[10];

    printf("Le joueur %c a gagne BRAVO !\n", joueurGagnant);
    printf("Voulez-vous recommencer ? (o/n)\n>>");
    readStr(recommencer, 10);
    if (recommencer[0] == 'y' || recommencer[0] == 'Y' || recommencer[0] == 'o' || recommencer[0] == 'O')
    {
        return 1;
    }
    return 0;
}

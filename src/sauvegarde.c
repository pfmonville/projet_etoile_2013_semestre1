#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sstdin.h"
#include "superviseur.h"

void sauvegarder(char tableau[25][18], J joueur[], int p, int nombreJoueur)
{
	int i, j; /* index des boucles for */
	char nom[100]; /* nom du fichier de sauvegarde */
	char extension[] = ".txt"; /* extension du fichier de sauvegarde */
	char lettre_joueur[] = {'A', 'D', 'B', 'E', 'C', 'F'}; /* ordre de jeu */
	int identifiant_joueur[] = {0, 3, 1, 4, 2, 5}; /* identifiant correspondant aux joueurs dans l'ordre */
	FILE* fichier = NULL; /* pointeur sur le fichier de sauvegarde */

	/* saisie du nom du fichier de sauvegarde */
	printf("Nom du fichier de sauvegarde\n");
	printf(">> ");
	fgets(nom, sizeof(nom), stdin);
	for (i = 0; i < (int)sizeof(nom); i++)
	{
		if (nom[i] == '\n')
		{
			nom[i] = '\0';
		}
	}
	strcat(nom, extension);
 
 	/* ouverture ou création du fichier de sauvegarde */
    fichier = fopen(nom, "w");
 
    if (fichier != NULL)
    {
		/* sauvegarde du plateau */
		for (i = 0; i < 18; i++)
		{
			for (j = 0; j < 25; j++)
			{
				fputc(tableau[j][i], fichier);
			}
			fputc('\n', fichier);
		}

		/* sauvegarde du nombre de joueurs */
		fprintf(fichier, "Nombre de joueurs : %d\n", nombreJoueur);
		fputc('\n', fichier);

		/* sauvegarde du tour de joueurs */
		fprintf(fichier, "Tour du joueur : %c\n", p + 65);
		fputc('\n', fichier);

		/* sauvegarde de la nature des joueurs */
		fputs("Nature des joueurs\n", fichier);
		fputs("0 : IA, 1 : humain\n", fichier);
		fputc('\n', fichier);
		for (i = 0; i < nombreJoueur; i++)
		{
			fprintf(fichier, "Joueur %c : %d\n", lettre_joueur[i], joueur[identifiant_joueur[i]].humain);
		}
        fclose(fichier);
    }
	else
	{
		printf("Erreur dans l'ouverture du fichier de sauvegarde\n");
	}
}

void charger(char tableau[25][18], J joueur[], int *p, int *nombreJoueur)
{
	int i, j; /* index des boucles for */
	char c; /* caractère lu */
	char caractere; /* caractère fprintf */
	char nom[20]; /* nom du fichier de sauvegarde */
	char extension[] = ".txt"; /* extension du fichier de sauvegarde */
	int identifiant_joueur[] = {0, 3, 1, 4, 2, 5}; /* identifiant correspondant aux joueurs dans l'ordre */
	FILE* fichier = NULL; /* pointeur sur le fichier de sauvegarde */

	/* saisie du nom du fichier de sauvegarde */
	printf("Nom du fichier de sauvegarde\n");
	printf(">> ");
	readStr(nom, 20);
	for (i = 0; i < (int)sizeof(nom); i++)
	{
		if (nom[i] == '\n')
		{
			nom[i] = '\0';
		}
	}
	strcat(nom, extension);

 	/* ouverture ou création du fichier de sauvegarde */
    fichier = fopen(nom, "r");

	if (fichier != NULL)
	{
		/* chargement et affectation du plateau */
		for (i = 0; i < 18; i++)
		{
			for (j = 0; j < 25; j++)
			{
				do
                {
					c = fgetc(fichier);
				}while(c == '\n');
				tableau[j][i] = c;
			}
		}

		/* chargement et affectation du nombre de joueurs */
		fseek(fichier, 468, SEEK_SET);
		fscanf(fichier, "Nombre de joueurs : %d\n\n", nombreJoueur);

		/* chargement et affectation du tour du joueur */
		fseek(fichier, 491, SEEK_SET);
		fscanf(fichier, "Tour du joueur : %c\n\n", &caractere);
		*p = caractere - 65;

		/* chargement et affectation de la nature des joueurs */
		fseek(fichier, 550, SEEK_SET);
		for (i = 0; i < *nombreJoueur; i++)
		{
			fscanf(fichier, "Joueur %*c : %d\n", &(joueur[identifiant_joueur[i]].humain));
		}
		fclose(fichier);
	}
	else
	{
		printf("Erreur dans l'ouverture du fichier de sauvegarde\n");
	}
}

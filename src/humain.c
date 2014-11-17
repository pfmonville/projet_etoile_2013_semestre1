#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sstdin.h"
#include "superviseur.h"
#include "pion.h"
#include "humain.h"
#include "sauvegarde.h"

char *selectionPion(char tableau[][18], J joueur[], int *p, int *nombreJoueur)
{
	int k, choixPion;
	char *pionSelectionne = NULL, *selection[10];
    
    k = pionId(tableau, joueur, *p, selection);
	do {
        printf("Tour du joueur %c\n", joueur[*p].pion);
		printf("\n");
        afficherTableau(tableau);
		printf("'c' pour charger, 'q' pour quitter\n");
		printf("\n");printf("Sélection du pion ?\n");
		printf(">> ");
		choixPion = readInt();
        system("clear");
        if (choixPion == 42)
        {
            nettoyerPion(tableau, joueur, *p);
            if(enregistrerQuitter(tableau, joueur, *p, *nombreJoueur))  //si renvoie 1 c'est qu'il ne voulait pas quitter finalement...
            {
                pionId(tableau, joueur, *p, selection);  //... on réaffiche donc les pions (k est le même)
            }
        }
        else if (choixPion == 43)  //on lui dit qu'il ne peut pas revenir en arriere maintenant
        {
            printf("vous ne pouvez pas revenir en arrière avant d'avoir selectionné un pion\n");
        }
        else if (choixPion == 44)  //il ne peut pas passer
        {
            printf("vous ne pouvez passer votre tour avant d'avoir effectuer au moins un premier saut\n");
        }

		if (choixPion == 45)
		{
			nettoyerPion(tableau, joueur, *p);
			charger(tableau, joueur, p, nombreJoueur);
            pionId(tableau, joueur, *p, selection);
			continue;
		}
	}while(choixPion >= k || choixPion < 0);
    
    pionSelectionne = selection[choixPion]; //on récupère l'adresse du pion selectionné (version 1.0 on avait fait une boucle encore)
    nettoyerPion(tableau, joueur, *p);
    
	return (pionSelectionne);
}



int selectionCible(char tableau [25][18],J joueur[], int p, char *pionSelectionne, char **cibleSelectionnee, int *idSaut, int nombreJoueur)
{
    int k, choixCible, probleme = 0;
    char *selection[10];
    
    //affiche les cibles
    k = afficherCible (pionSelectionne, *idSaut, selection);

    do
    {
        printf("Tour du joueur %c\n", joueur[p].pion);
		printf("\n");
        afficherTableau(tableau);
        if (*idSaut != 0)   //vraie si ce un saut a déjà été effectué ce tour ci
		{
			printf("'p' pour passer, 'q' pour quitter\n");
			printf("\n");
            if (probleme == 1)
                printf("Vous ne pouvez pas charger une partie pendant un déplacement\n");
            probleme = 0;
			printf("Resauter sur quelle case ?\n");
			printf(">> ");
		}
        else
		{
			printf("'r' pour annuler, 'q' pour quitter\n");
			printf("\n");
            if (probleme == 1)
                printf("Vous ne pouvez pas charger une partie pendant un déplacement\n");
            probleme = 0;
			printf("Déplacer sur quelle case ?\n");
			printf(">> ");
		}

		/* saisie utilisateur */
        choixCible = readInt();
        system ("clear");
    
        if (choixCible == 42)    //s'il veut quitter on nettoie le tableau (nettoyerCible) et on appel enregistrerQuitter
        {
            nettoyerCible(tableau);
            if (enregistrerQuitter(tableau, joueur, p, nombreJoueur)) //si renvoie un il voulait pas quitter finalement...
            {
                afficherCible(pionSelectionne, *idSaut, selection);    //... on réaffiche les possibilités
            }
        }
        else if (choixCible == 43 && *idSaut == 0)  //s'il veut revenir en arrière lors du premier saut on nettoie et sort avec code 1
        {
            nettoyerCible(tableau);
            return 1;
        }
        else if (choixCible == 44 && *idSaut != 0)  //s'il veut passer son tour après avoir fais un premier coups on nettoie et on sort avec code 1
        {
            nettoyerCible(tableau);
            cibleSelectionnee = NULL;   //pour éviter un déplacement
            return 1;
        }
        else if (choixCible == 45 && *idSaut == 0)  //s'il veut charger une partie pendant un déplacement on lui dit qu'il peut pas
        {
            probleme = 1;
        }
    } while (choixCible >= k || choixCible < 0);
    
    *cibleSelectionnee = selection[choixCible];
    (*idSaut)++;
    nettoyerCible (tableau);
    
    return 0;
}


void humain (char tableau[25][18], J joueur[6], int *p, int *nombreJoueur)
{
    char *pionSelectionne = NULL, *cibleSelectionnee = NULL;
    int idSaut = 0;
    
    do
    {
        pionSelectionne = selectionPion (tableau, joueur, p, nombreJoueur);
    }while (selectionCible (tableau, joueur, *p, pionSelectionne, &cibleSelectionnee, &idSaut, *nombreJoueur));  //sera vraie s'il veut revenir en arrière
    deplacerPion (pionSelectionne, cibleSelectionnee);
    if (saut(pionSelectionne, cibleSelectionnee))
    {
        pionSelectionne = cibleSelectionnee;
        while(selectionCible (tableau, joueur, *p, pionSelectionne, &cibleSelectionnee, &idSaut, *nombreJoueur) == 0)    //tant qu'il saute (renvoie 0)
        {
            deplacerPion(pionSelectionne, cibleSelectionnee);
            pionSelectionne = cibleSelectionnee;
        }
    }
    printf("\n\n");
    afficherTableau (tableau);
    sleep(1);
}

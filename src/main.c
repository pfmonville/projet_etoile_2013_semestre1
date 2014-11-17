#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sstdin.h"
#include "superviseur.h"
#include "pion.h"
#include "humain.h"
#include "ia.h"



int main()
{
    //srand((int)time(NULL));
	J joueur[6]; /* déclaration des 6 joueurs */
	char tableau[25][18]; /* plateau */
	char joueurGagnant; /* joueur gagnant */
	int p; /* joueur actuel */
	int nombreJoueur; /* nombre de joueurs */
    srand((int)time(NULL));
	do
    {
        debutJeu(tableau, joueur, &nombreJoueur, &p);

		/* tour de jeu */
        do
        {
            system("clear");

            if (joueur[p].humain == 0)
            {
                ia(tableau, joueur, p);
            }
            else
            {
                humain(tableau, joueur, &p, &nombreJoueur); //&p pour charger proprement un fichier (changement de joueur en cours)
            }
            p = prochainJoueur(nombreJoueur, p);
        } while (gagner(tableau, &joueurGagnant));
    } while (recommencer(joueurGagnant));

	return 0;
}

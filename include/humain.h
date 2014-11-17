#ifndef HUMAIN
#define HUMAIN

char *selectionPion (char tableau[][18], J joueur[], int *p, int *nombreJoueur);
int selectionCible(char tableau [25][18],J joueur[], int p, char *pionSelectionne, char **cibleSelectionnee, int *idSaut, int nombreJoueur);
void humain (char tableau[25][18], J joueur[6], int *p, int *nombreJoueur);

#endif

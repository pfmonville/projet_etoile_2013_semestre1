#ifndef PION
#define PION

char testerPion (char *pionSelectionne);
int pionId (char tableau[][18], J joueur[], int p, char *selection[10]);
int campAdjacent (char tableau[25][18], int p, char *pionSelectionne);
int pionPlace (char tableau[25][18], int p, char *pionSelectionne);
char afficherCible (char *pionSelectionne, int idSaut, char *selection[10]);
void deplacerPion (char *pionSelectionne,char *cibleSelectionnee);
int saut (char *pionSelectionne, char *cibleSelectionnee);

#endif

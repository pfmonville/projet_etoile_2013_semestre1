#ifndef SUPERVISEUR
#define SUPERVISEUR

typedef struct
{
	int humain;
	int butx;
	int buty;
    int butox;
    int butoy;
	char pion;
} J;

void initialiserJoueur (J joueur[6]);
void initialiserTableau(char tableau[][18]);
void afficherTableau(char tableau[][18]);
void menu (char tableau[25][18], int *nombreJoueur, J joueur[6], int *p);
void changementBut (char tableau[25][18], J joueur[6], int p);
void nettoyerPion (char tableau[25][18], J joueur[], int p);
void nettoyerCible (char tableau[25][18]);
int chercherDansTableau (char tableau[25][18], char *possibilite[24*16], int i, int j);
int enregistrerQuitter (char tableau[25][18], J joueur[], int p, int nombreJoueur);
void debutJeu(char tableau[25][18], J joueur[6], int *nombreJoueur, int *p);
int prochainJoueur (int nombreJoueur, int p);
int gagner (char tableau[][18], char *joueurGagnant);
int recommencer (char joueurGagnant);
void changementBut(char tableau[25][18], J joueur[6], int p);

#endif

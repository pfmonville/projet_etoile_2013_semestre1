#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void clearBuffer()	//fonction qui vide le buffer
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int readStr(char *str, int longueur)
{
    char *positionEntree = NULL;
    
    if(fgets(str, longueur, stdin) != NULL)	// fgets renvoie null si il y a une erreur, donc si il n'y a pas d'erreur ...
    {
        positionEntree = strchr(str, '\n'); //	... strchr fonction qui permet de chercher un caractère dans une chaine
        if(positionEntree != NULL)	// si on a trouver un caractère entrée...
        {
            *positionEntree = '\0';	//... on évite d'écrire le caractère entrée car fgets le lit et l'affiche
        }
        else	// si on a pas trouver le caractère entrée ...
        {
            clearBuffer();	// ... c'est qu'il y a trop de texte tapé donc on affiche ce qui est prévu et on vide le buffer
        }
        return 1;
    }
    else
    {
        clearBuffer();  //erreur non prévu du fgets l'utilisateur aura tapé un truc mais problème alors on vide le buffer et on renvoie un code d'erreur
        return 0;
    }
}

int readInt()	// permet de convertir une chaine en long (qu'on va transtyper en int) ignore les premiers espaces
{
    char *endStr, str[20];
    int l;
    
    while (1)   //boucle infini tant que l'utilisateur n'a pas rentré un nombre valide
    {
        if (readStr (str, 20))	// si la fonction lire renvoie 1 cad ça a bien marché
        {
            if (str[0] == 'q' || str[0] == 'Q') {return 42;} //si le joueur veut quitter et tape 'q' alors on renvoie un code spécial
            if (str[0] == 'r' || str[0] == 'R') {return 43;} //si le joueur veut revenir en arrière et tape 'r' alors renvoie 43
            if (str[0] == 'p' || str[0] == 'P') {return 44;} //si le joueur veut arreter de sauter et tape 's' alors renvoie 44
            if (str[0] == 'c' || str[0] == 'C') {return 45;} //si le joueur veut charger une partie et tape 'c' alors renvoie 45
            
            errno = 0;    //restera à zero si pas d'erreur
            l = (int)strtol(str, &endStr, 10);	// strtol (string to long) converti chaine en long
            
            if ((errno == ERANGE && (l == INT_MAX || l == INT_MIN)) || (errno != 0 && l == 0)) {printf("Mauvaise saisie veuillez recommencer\n>>");}   //on boucle
            else if (endStr == str) {printf("Mauvaise saisie veuillez recommencer\n>>");}    //on boucle
            else    return l;	//Si nous arrivons ici, strtol() a réussi à analyser le nombre et on le retourne
        }
    }
}

#ifndef FIC_H_INCLUDED
#define FIC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

FILE* ouverture_fichier(char* file_name);
FILE* creation_fichier(char *file_name);
void fermeture_fichier(FILE *fic);
void calcul_occurence(FILE *fic,int *tab);
void ecriture_taille(FILE *f,int *taille);
int nombre_caractere(FILE *f);

#endif // FIC_H_INCLUDED

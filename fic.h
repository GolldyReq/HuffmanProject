#ifndef FIC_H_INCLUDED
#define FIC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"
#include "liste.h"

//Ouverture / Fermeture de fichier
FILE* ouverture_fichier(char* file_name);
FILE* creation_fichier(char *file_name);
void fermeture_fichier(FILE *fic);

//Lecture dans un fichier
void calcul_occurence(FILE *fic,int *tab);
int nombre_caractere(FILE *f);

#endif // FIC_H_INCLUDED

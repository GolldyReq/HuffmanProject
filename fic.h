#ifndef FIC_H_INCLUDED
#define FIC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

FILE* ouverture_fichier(char* file_name);
void fermeture_fichier(FILE *fic);
void calcul_occurence(FILE *fic,int *tab);

#endif // FIC_H_INCLUDED

#ifndef FIC_H_INCLUDED
#define FIC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"
#include "liste.h"

FILE* ouverture_fichier(char* file_name);
FILE* creation_fichier(char *file_name);
void fermeture_fichier(FILE *fic);
void calcul_occurence(FILE *fic,int *tab);
void ecriture_taille(FILE *f,int *taille);
int nombre_caractere(FILE *f);
void ecrire_caractere(Arbre *abr,FILE *f);
void ecriture_parcours(Arbre *abr,FILE *f);
void compresser_texte(FILE *fic,T_huffman *tableau_h,FILE *f);

#endif // FIC_H_INCLUDED

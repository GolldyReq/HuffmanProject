#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include <stdio.h>
#include "binarypath.h"



typedef struct Arbre
{
    char car;
    int freq;
    struct Arbre *gauche;
    struct Arbre *droite;
}Arbre;

Arbre* create_feuille(char c,int f);
Arbre* create_arbre(Arbre *g,Arbre *d);
void destruction_arbre(Arbre **n);
int nb_noeud(Arbre *abr);
int nb_feuille(Arbre *abr);
//void parcours_arbre_infixe(Arbre *abr);

void parcours_arbre_infixe_bp(Arbre *abr,BinaryPath *bp);
int isFeuille(Arbre *abr);

#endif // ARBRE_H_INCLUDED

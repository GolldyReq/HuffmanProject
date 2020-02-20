#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"


Arbre* create_feuille(char c,int f)
{
    Arbre *abr=(Arbre*)malloc(sizeof(Arbre));
    if(abr==NULL)
        exit(-3);
    abr->car=c;
    abr->freq=f;
    abr->gauche=NULL;
    abr->droite=NULL;
    return abr;
}

Arbre* create_arbre(Arbre *g, Arbre *d)
{
    Arbre *abr=(Arbre*)malloc(sizeof(Arbre));
    if(abr==NULL)
        exit(-3);
    abr->car=' ';
    abr->freq=g->freq+d->freq;
    abr->gauche=g;
    abr->droite=d;
    return abr;

}

int nb_noeud(Arbre *abr)
{
    if(abr==NULL)
        return 0 ;

    else
        return (1+nb_noeud(abr->droite)+nb_noeud(abr->gauche));
}

int nb_feuille(Arbre *abr)
{
    if(abr->droite==NULL && abr->gauche==NULL)
    {
        printf("%c ->\n",abr->car);
        return 1;
    }
    else
    {
        return (0+nb_feuille(abr->gauche)+nb_feuille(abr->droite));
    }
}

void parcours_arbre_infixe(Arbre *abr)
{
    if(abr==NULL)
        return;
    printf("Gauche\n");
    parcours_arbre_infixe(abr->gauche);
    printf("on remonte\n");
    printf("%c\n",abr->car);
    printf("Droite\n");
    parcours_arbre_infixe(abr->droite);
    printf("on remonte\n");

}

void destruction_arbre(Arbre **abr)
{
    if((*abr)==NULL)
        return;
    destruction_arbre(&(*abr)->gauche);
    destruction_arbre(&(*abr)->droite);
    free(*abr);
    abr=NULL;
}

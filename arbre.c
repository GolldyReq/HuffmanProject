#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#include "binarypath.h"


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
    if(isFeuille(abr))
    {
        printf("%c ->\n",abr->car);
        return 1;
    }
    else
    {
        return (0+nb_feuille(abr->gauche)+nb_feuille(abr->droite));
    }
}

void parcours_arbre_infixe(Arbre *abr,BinaryPath *bp)
{
    if(abr==NULL)
        return;
    //printf("Gauche\n");
    ajout_bits(bp,'0');
    parcours_arbre_infixe(abr->gauche,bp);
    //printf("on remonte\n");
    enlever_bits(bp);

    if(isFeuille(abr))
    {
        printf("feuille : %c -> ",abr->car);
        afficher_BinaryPath(bp);
    }
    //printf("une feuille : %c\n",abr->car);
    //printf("Droite\n");
    ajout_bits(bp,'1');
    parcours_arbre_infixe(abr->droite,bp);
    enlever_bits(bp);
    //printf("on remonte\n");

}
int isFeuille(Arbre *abr)
{
    if(abr->gauche==NULL && abr->droite==NULL)
        return 1;
    return 0;
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

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
    if(isFeuille(abr))
        return 1;
    else
        return (0+nb_feuille(abr->gauche)+nb_feuille(abr->droite));
}

void espace(int i)
{
    for(int j=0;j<i;j++)
        printf("\t");
}
void affichage_arbre(Arbre *abr,int i)
{
    if(isFeuille(abr))
    {
        espace(i);
        printf("(%d) : %c",abr->freq,abr->car);
        return;
    }
    espace(i);
    printf("(%d)\n",abr->freq);
    espace(i);
    printf("|____0____\n");
    i++;
    affichage_arbre(abr->gauche,i);
    i--;
    printf("%c\n",abr->car);
    espace(i);
    printf("|____1____\n");
    i++;
    affichage_arbre(abr->droite,i);
    i--;
}

/*
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
*/


void parcours_arbre_infixe_bp(Arbre *abr,BinaryPath *bp)
{
    if(abr==NULL)
        return;
    ajout_bits(bp,'0');
    parcours_arbre_infixe_bp(abr->gauche,bp);
    enlever_bits(bp);

    /*if(isFeuille(abr))
    {
        //printf("feuille : %c -> ",abr->car);
        //afficher_BinaryPath(bp);
    }*/
    ajout_bits(bp,'1');
    parcours_arbre_infixe_bp(abr->droite,bp);
    enlever_bits(bp);
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

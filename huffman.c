#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"
#include "liste.h"

int i=0;

void construction_arbre_huffman(Liste *l)
{
    Element *e=l->first;
    //Tant qu'il y a au moins 2 elt dans la liste
    while(e->next!=NULL)
    {
        Arbre *abr=create_arbre(e->abr,e->next->abr);
        add_in_liste(l,abr);
        delete_elt(l,e->next);
        delete_elt(l,e);
        e=l->first;
    }
}


void remplissage_table(Arbre *abr,T_huffman *th,BinaryPath *bp)
{
    if(abr==NULL)
        return;
    ajout_bits(bp,'0');
    remplissage_table(abr->gauche,th,bp);
    enlever_bits(bp);
    if(isFeuille(abr))
    {
        add_in_tab(th,abr->car,bp);
        i++;
    }
    ajout_bits(bp,'1');
    remplissage_table(abr->droite,th,bp);
    enlever_bits(bp);
}

void creation_table_huffman(Arbre *abr,T_huffman *th,BinaryPath *bp)
{
    remplissage_table(abr,th,bp);
    afficher_BinaryPath(bp);

}

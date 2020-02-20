#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"
#include "liste.h"
#include "element.h"

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
        afficher_liste(l);
        printf("----------------\n");
        e=l->first;
    }
}

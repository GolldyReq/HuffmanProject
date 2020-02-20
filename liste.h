#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED
#include "arbre.h"
#include "element.h"

typedef struct Liste
{
    struct Element *first;

}Liste;

Liste* create_liste();
void add_in_initial_liste(Liste *l,char c,int f);
void add_arbre_in_tree();
void delete_elt(Liste *l,Element *supp);
void afficher_liste(Liste *l);
void destruction_liste(Liste **l);

#endif // LISTE_H_INCLUDED

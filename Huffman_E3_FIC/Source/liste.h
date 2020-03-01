#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include "element.h"

//Liste permettant de créer l'arbre de Huffman
typedef struct Liste
{
    struct Element *first;

}Liste;

//Tableau de Huffman permettant de passer du BinaryPath au caractere ascii
typedef struct T_huffman
{
    struct THuffman_elt *first;
}T_huffman;
//Fonction pour l'arbre de Huffman
Liste* create_liste();
void add_in_initial_liste(Liste *l,char c,int f);
void add_in_liste(Liste *l,Arbre *abr);
void add_arbre_in_tree();
void delete_elt(Liste *l,struct Element *supp);
void afficher_liste(Liste *l);
void destruction_liste(Liste **l);

//////////////////////////


//Fonction pour le tableau de Huffman
T_huffman* create_table();
void destruction_tableau(T_huffman *th);
void add_in_tab(T_huffman *th,char c,BinaryPath *bp);
void delete_firtst_elt_in_table(T_huffman *th);
void afficher_tableau_huffman(T_huffman *th);

#endif // LISTE_H_INCLUDED

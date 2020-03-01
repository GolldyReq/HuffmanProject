#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include "arbre.h"
#include "binarypath.h"

typedef struct Element
{
    struct Arbre *abr;
    struct Element *next;
}Element;


//Element du tableau de huffman contenant un caractere et un BinaryPath
typedef struct THuffman_elt
{
    char car;
    struct BinaryPath code;
    struct THuffman_elt *next;

}THuffman_elt;

//Fonction utilisant les elements de l'arbre de huffman
Element* create_element(Arbre *a,Element *n);
void destruction_element(Element **e);

//fonction pour les elements du tableau de huffman
THuffman_elt* create_elt(char c,BinaryPath *bp);
void destruction_elt(THuffman_elt **t);

#endif // ELEMENT_H_INCLUDED

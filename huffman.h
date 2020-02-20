#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#include "liste.h"


typedef struct Dictionnaire
{
    struct BinaryPath *bp;
    char car;

}Dictionnaire;

void construction_arbre_huffman(Liste *l);

#endif // HUFFMAN_H_INCLUDED

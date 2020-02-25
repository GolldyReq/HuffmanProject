#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED


#include "liste.h"

void construction_arbre_huffman(struct Liste *l);
void creation_table_huffman(Arbre *abr,T_huffman *th,BinaryPath *bp);

#endif // HUFFMAN_H_INCLUDED

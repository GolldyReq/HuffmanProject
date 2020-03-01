#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED


#include "liste.h"

void construction_arbre_huffman(struct Liste *l);
void creation_table_huffman(Arbre *abr,T_huffman *th,BinaryPath *bp);
T_huffman* reconstruction_arbre(BinaryPath *chemin_arbre,char *c);

#endif // HUFFMAN_H_INCLUDED

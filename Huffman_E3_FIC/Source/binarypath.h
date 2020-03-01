#ifndef BINARYPATH_H_INCLUDED
#define BINARYPATH_H_INCLUDED

typedef struct BinaryPath
{
    char *Bcode;
    int longueur;

}BinaryPath;

BinaryPath* newBinaryPath();
void ajout_bits(BinaryPath *bp,char bit);
void enlever_bits(BinaryPath *bp);
void enlever_premier_bits(BinaryPath *bp);
void afficher_BinaryPath(BinaryPath *bp);
int zero(BinaryPath *bp);
int egalite_bp(BinaryPath *a, BinaryPath *b);


#endif // BINARYPATH_H_INCLUDED

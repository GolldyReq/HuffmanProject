#include <stdlib.h>
#include <stdio.h>

#include "binarypath.h"

BinaryPath* newBinaryPath()
{
    BinaryPath *bp=(BinaryPath*)malloc(sizeof(BinaryPath));
    if(bp==NULL)
        exit(-5);
    bp->longueur=0;
    bp->Bcode=NULL;
    return bp;

}
void ajout_bits(BinaryPath *bp,char bit)
{

    char *tmp=(char*)malloc(bp->longueur*sizeof(char));
    if(tmp==NULL)
        exit(-7);
    for(int i=0;i<bp->longueur;i++)
        tmp[i]=bp->Bcode[i];
    bp->longueur++;
    bp->Bcode=(char*)malloc(bp->longueur*sizeof(char));
    if(bp->Bcode==NULL)
        exit(-7);
    for(int i=0;i<bp->longueur-1;i++)
        bp->Bcode[i]=tmp[i];
    bp->Bcode[bp->longueur-1]=bit;
}
void enlever_bits(BinaryPath *bp)
{
    if(bp->longueur==0)
        exit(-8);
    char *tmp=(char*)malloc(bp->longueur*sizeof(char));
    if(tmp==NULL)
        exit(-7);
    for(int i=0;i<bp->longueur;i++)
        tmp[i]=bp->Bcode[i];
    bp->longueur--;
    bp->Bcode=(char*)malloc(bp->longueur*sizeof(char));
    if(bp->Bcode==NULL)
        exit(-7);
    for(int i=0;i<bp->longueur;i++)
        bp->Bcode[i]=tmp[i];
}
void afficher_BinaryPath(BinaryPath *bp)
{
    for(int i=0;i<bp->longueur;i++)
        printf("%c|",bp->Bcode[i]);
    printf("\n");
}

BinaryPath* copieBinaryPath(BinaryPath *bp)
{
    BinaryPath *code=(BinaryPath*)malloc(sizeof(BinaryPath));
    if(code==NULL)
        exit(-15);
    code->longueur=bp->longueur;
    for(int i=0;i<code->longueur;i++)
        code->Bcode[i]=bp->Bcode[i];
    return code;
}

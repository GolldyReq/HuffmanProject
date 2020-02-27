#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"
#include "liste.h"

int i=0;
int cpt=0;
int gauche=1;
int code=0;

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
    i=0;
    afficher_BinaryPath(bp);

}


void construction_depuis_bp(T_huffman *th,BinaryPath *chemin_arbre,BinaryPath *bp,char *c,int i)
{
    //printf("longueur : %d\n",chemin_arbre->longueur);

    while(i<chemin_arbre->longueur)
    {
        if(chemin_arbre->Bcode[i]=='0')
        {
            code=1;

            if(gauche)
                ajout_bits(bp,'0');
            else
                {gauche=1;ajout_bits(bp,'1');}
        }
        else
        {
            if(code)
            {
                //Feuille
                code=0;
                add_in_tab(th,c[cpt],bp);
                cpt++;
            }
            enlever_bits(bp);
            gauche=0;
        }
        i++;
    }
}

T_huffman* reconstruction_arbre(BinaryPath *chemin_arbre,char *c)
{
    T_huffman *th=create_table();
    BinaryPath *bp=newBinaryPath();
    construction_depuis_bp(th,chemin_arbre,bp,c,i);
    i=0;cpt=0;
    return th;
}

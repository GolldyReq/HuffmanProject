#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"
#include "liste.h"

int i=0;
int cpt=0;
int gauche=1;

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


void construction_depuis_bp(Arbre *abr,BinaryPath *chemin_arbre,BinaryPath *bp,char *c,int i)
{
    printf("longueur : %d\n",chemin_arbre->longueur);

    while(i<chemin_arbre->longueur)
    {

        printf("i : %d \n",i);
        printf("code : %c\n",chemin_arbre->Bcode[i]);
        if(chemin_arbre->Bcode[i]=='0')
        {
            if(gauche)
                printf("on descend a gauche \n");
            else
                {printf("on descend a droite \n");gauche=1;}
        }
        else
        {
            printf("On remonte\n");
            gauche=0;
        }
        i++;
        //add_in_table(bp,th)...


    }

}

void reconstruction_arbre(BinaryPath *chemin_arbre,char *c)
{
    T_huffman *th=create_table();
    BinaryPath *bp=newBinaryPath();
    construction_depuis_bp(th,chemin_arbre,bp,c,i);
}

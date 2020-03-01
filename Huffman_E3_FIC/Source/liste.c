#include <stdlib.h>
#include <stdio.h>
#include "liste.h"
#include "arbre.h"
#include "element.h"

Liste* create_liste()
{
    Liste *l=(Liste*)malloc(sizeof(Liste));
    if (l==NULL)
        exit(-3);
    l->first=NULL;
    return l;
}

//construction de la liste initial
//la liste est construite trié par ordre croissant en fonction de la frequence
void add_in_initial_liste(Liste *l,char c,int f)
{
    Arbre *abr=create_feuille(c,f);
    add_in_liste(l,abr);
}

void add_in_liste(Liste *l,Arbre *abr)
{
    Element *e=l->first;
    if(e==NULL){
        Element *ajout=create_element(abr,NULL);
        l->first=ajout;
        return;
    }
    //ajout en debut
    if(abr->freq<=e->abr->freq)
    {
        Element *ajout=create_element(abr,e);
        ajout->next=l->first;
        l->first=ajout;
        return;
    }
    while(e->next!=NULL)
    {
        //Si l'element suivant a une plus grande frequence
        //Alors on l'ajoute ici
        if(abr->freq<e->next->abr->freq)
        {
            Element *ajout=create_element(abr,e->next);
            e->next=ajout;
            return;
        }

        e=e->next;
    }
    Element *ajout=create_element(abr,NULL);
    e->next=ajout;
    return;
}

void delete_elt(Liste *l,Element *supp)
{
    Element *e=l->first;
    //suppression du premier elt
    if(e==supp)
    {
        //printf("Suppression premier elt\n");
        l->first=e->next;
        free(e);
        return;
    }
    while(e->next!=NULL)
    {
        if(e->next==supp)
        {
            e->next=supp->next;
            free(supp);
            return;
        }
    }
    //suppression dernier elt
    //printf("suppression dernier elt\n");
    e->next=NULL;
    free(supp);

}

void afficher_liste(Liste *l)
{
    Element *e=l->first;
    while(e!=NULL)
    {
        if((int)e->abr->car<32)
            printf("SP : %d -> \n",e->abr->freq);
        else
            printf("%c : %d -> \n",e->abr->car,e->abr->freq);
        e=e->next;
    }
}

void destruction_liste(Liste **l)
{
    if(*l!=NULL)
    {
        Element *e=(*l)->first;
        while(e!=NULL)
        {
            (*l)->first=e->next;
            destruction_element(&e);
            e=(*l)->first;
        }
    }
    free(*l);

}


////////////////////////////////////////////////////////////////////////////////////////////


T_huffman* create_table()
{
    T_huffman *th=(T_huffman*)malloc(sizeof(T_huffman));
    if(th==NULL)
        exit(-3);
    th->first=NULL;
    return  th;
}


//Ajout dans la table de huffman
//L'ajout se fait par tri alphabétique pour l'affichage utilisateur
void add_in_tab(T_huffman *th,char c,BinaryPath *bp)
{
    THuffman_elt *elt=(THuffman_elt*)malloc(sizeof(THuffman_elt));
    elt=create_elt(c,bp);
    if(elt==NULL)
        exit(-3);
    THuffman_elt *actuel=th->first;
    if(actuel==NULL)
    {
        th->first=elt;
        //afficher_BinaryPath(&th->first->code);
        return;
    }
    if(elt->car<actuel->car)
    {
        elt->next=actuel;
        th->first=elt;
        return;
    }
    while(actuel->next!=NULL)
    {
        if(elt->car<actuel->next->car)
        {
            elt->next=actuel->next;
            actuel->next=elt;
            return;
        }
        actuel=actuel->next;
    }
    //ajout a la fin
    actuel->next=elt;
}

void afficher_tableau_huffman(T_huffman *th)
{
    THuffman_elt *actuel=(THuffman_elt*)malloc(sizeof(THuffman_elt));
    if(actuel==NULL)
        return;
    actuel=th->first;
    printf("TABLE DE HUFFMAN :\n");
    while(actuel!=NULL)
    {
        if((int)actuel->car<32)
            printf("'SP %d' -----> ",actuel->car);
        else
            printf("'%c' -----> ",actuel->car);
        afficher_BinaryPath(&actuel->code);
        actuel=actuel->next;
    }
}

#include <stdlib.h>
#include <stdio.h>
#include "liste.h"
#include "arbre.h"
#include "element.h"

Liste* create_liste()
{
    Liste *l=(Liste*)malloc(sizeof(Liste));
    if (l==NULL)
        exit(-4);
    l->first=NULL;
}
//construction de la liste initial
//la liste est construite tri� par ordre croissant en fonction de la frequence
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
        printf("Suppression premier elt\n");
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
    printf("suppression dernier elt\n");
    e->next=NULL;
    free(supp);

}

void afficher_liste(Liste *l)
{
    Element *e=l->first;
    while(e!=NULL)
    {
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
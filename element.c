#include <stdlib.h>
#include <stdio.h>
#include "element.h"

Element* create_element(Arbre *a,Element *n)
{
    Element *e=(Element*)malloc(sizeof(Element));
    if(e==NULL)
        exit(-5);
    e->abr=a;
    e->next=n;
}

void destruction_element(Element **e)
{
    if(*e!=NULL)
    {
        destruction_arbre(&(*e)->abr);
        (*e)->next=NULL;
    }
    free(*e);

}
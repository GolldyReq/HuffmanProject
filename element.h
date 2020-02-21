#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include "arbre.h"

typedef struct Element
{
    struct Arbre *abr;
    struct Element *next;
}Element;


Element* create_element(Arbre *a,Element *n);
void destruction_element(Element **e);
#endif // ELEMENT_H_INCLUDED

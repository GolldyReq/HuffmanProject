/*******************************************************************************
 *  Objectif : Tester la pile d'entiers
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pile.h"

int main()
{
    Pile pile;

    /* Initialiser la pile */
    initialiser(&pile);
    assert(est_vide(pile));

    /* Empiler un premier élément */
    empiler(&pile, 'A');
    assert(! est_vide(pile));
    assert(sommet(pile) == 'A');

    /* Empiler un deuxième élément */
    empiler(&pile, 'B');
    assert(! est_vide(pile));
    assert(sommet(pile) == 'B');

    /* Empiler un troisième élément */
    empiler(&pile, 'C');
    assert(! est_vide(pile));
    assert(sommet(pile) == 'C');

    /* Dépiler tous les éléments */
    depiler(&pile);
    assert(! est_vide(pile));
    assert(sommet(pile) == 'B');
    depiler(&pile);
    assert(! est_vide(pile));
    assert(sommet(pile) == 'A');
    depiler(&pile);
    assert(est_vide(pile));

    return EXIT_SUCCESS;
}


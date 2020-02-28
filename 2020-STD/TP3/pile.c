/****************************************************************
 *  Objectif : Implantation d'une pile de char
 ***************************************************************/

#include <assert.h>
#include <stdlib.h>
#include "pile.h"

void initialiser(Pile *p)
{
    assert(p != NULL);

    /* TODO: mettre le code... */

    assert(est_vide(*p));
}

void detruire(Pile *p)
{
    assert(p != NULL);

    /* TODO: mettre le code... */
}

char sommet(Pile p)
{
    assert(!est_vide(p));

    /* TODO: mettre le code... */
}

void depiler(Pile *p)
{
    assert(p != NULL);
    assert(!est_vide(*p));

    /* TODO: mettre le code... */
}

void empiler(Pile *p, char v)
{
    assert(p != NULL);
    assert(!est_pleine(*p));

    /* TODO: mettre le code... */

    assert(sommet(*p) == v);
}

bool est_vide(Pile p)
{
    /* TODO: mettre le code... */
}

bool est_pleine(Pile p)
{
    /* TODO: mettre le code... */
}

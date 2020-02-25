/*******************************************************************************
  *  Objectif : Illustration de quelques opérations sur les bits.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>


// Afficher le texte puis les 8 bits de octet en commençant par le plus à gauche
void afficher_octet_en_binaire(const char texte[], unsigned char octet) {
    printf("%s", texte);
    for (int i = 0; i < 8; i++) {
	int bit = octet >> 7;
	printf("%d", bit);
	octet = octet << 1;
    }
}

int main()
{
    // Comment coder le code 1011 sur un unsigned char sachant que l'on a les
    // bits dans l'ordre suivant 1, 0, 1, 1
    // On applique le schéma de Horner :
    // 1011 = ((((0 * 2) + 1) * 2 + 0) * 2 + 1) * 2 + 1
    // * 2 peut s'écrire par un décalage vers la gauche << 1
    // + peut ici s'écrire avec un | bit à bit
    unsigned char code = 0;	// code à 0
    unsigned char lg = 0;	// la longueur du code

    // Ajouter le premier bit
    code = (code << 1) | 1;	// on multiplie le code par deux et on ajoute 1
    lg++;			// le code augmente de 1
    afficher_octet_en_binaire("code   = ", code);
    printf(", %3hhu, %2hhx (lg = %u)\n", code, code, lg);

    // Ajouter le 2ème bit
    code = (code << 1) | 0;
    lg++;
    afficher_octet_en_binaire("code   = ", code);
    printf(", %3hhu, %2hhx (lg = %u)\n", code, code, lg);

    // Ajouter le 3ème bit
    code = (code << 1) | 1;
    lg++;
    afficher_octet_en_binaire("code   = ", code);
    printf(", %3hhu, %2hhx (lg = %u)\n", code, code, lg);

    // Ajouter le 4ème bit
    code = (code << 1) | 1;
    lg++;
    afficher_octet_en_binaire("code   = ", code);
    printf(", %3hhu, %2hhx (lg = %u)\n", code, code, lg);

    // Supposons que phrase initialiement vide (un unsigned char) à laquelle on
    // veut ajouter deux fois le code précédent.  On peut faire :
    // Ajouter une première fois le code
    unsigned char phrase = 0;	// tous les bits à 0
    phrase = phrase << lg;	// décaler les bits de lg caractères à gauche
    phrase = phrase | code;	// ou bit à bit pour ajouter le code
    afficher_octet_en_binaire("phrase = ", phrase);
    printf(", %3hhu, %2hhx\n", phrase, phrase);

    // Ajouter une deuxième fois le code
    phrase = phrase << lg;	// décaler les bits de lg caractères à gauche
    phrase = phrase | code;	// ou bit à bit pour ajouter le code
    afficher_octet_en_binaire("phrase = ", phrase);
    printf(", %3hhu, %2hhx\n", phrase, phrase);

    // Attention, si on dépasse la capacité, les bits les plus à gauche seront
    // perdus lors du décalage. Exemple :
    phrase = phrase << 1;	// Le premier bit est perdu !
    afficher_octet_en_binaire("phrase = ", phrase);
    printf(", %3hhu, %2hhx\n", phrase, phrase);

    // Attention aux opérations sur les signés !
    unsigned char pu = (code << lg) | code;
    afficher_octet_en_binaire("pu = ", pu);
    printf(", %3hhu, %2hhx\n", pu, pu);

    char ps = pu;
    afficher_octet_en_binaire("ps = ", ps);
    printf(", %3hhu, %2hhx\n", ps, ps);

    pu = pu >> 1;
    afficher_octet_en_binaire("pu = ", pu);
    printf(", %3hhu, %2hhx\n", pu, pu);

    ps = ps >> 1;	// Attention : le signe sera conservé (division par 2)
    afficher_octet_en_binaire("ps = ", ps);
    printf(", %3hhu, %2hhx\n", ps, ps);

    return EXIT_SUCCESS;
}

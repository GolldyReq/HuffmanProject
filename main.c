#include <stdio.h>
#include <stdlib.h>
#include "fic.h"
#include "arbre.h"
#include "liste.h"
#include "huffman.h"

int main()
{

    //Ouverture fichier
    FILE *fic=NULL;
    char* file="test.txt";
    fic=ouverture_fichier(file);

    //Tableau d'occurence l'indice du tableau
    //représente la lettre et la valeur sa fréquence d'appartion
    //on ne prend en compte que les caractére compris entre l'espace (32)
    //jusqu'au tilt (126)
    int occurence[128];
    for(int i=0;i<128;i++)
        occurence[i]=0;
    //calcule de la fréquence d'apparition
    calcul_occurence(fic,occurence);
    //Creation des arbres possedant une unique feuille
    //et de la liste chainé trié par fréquence de ces arbres
    Liste *l=NULL;
    l=create_liste();
    for(int i=32;i<126;i++)
    {
        if(occurence[i]!=0)
        {
            //printf("%c : %d\n",(char)i,occurence[i]);
            add_in_initial_liste(l,(char)i,occurence[i]);
            afficher_liste(l);
            printf("#######################\n");
        }
    }

    //construction de l'arbre de Huffman
    construction_arbre_huffman(l);


    int a=nb_feuille(l->first->abr);
    printf("nombre de feuille : %d\n",a);
    parcours_arbre_infixe(l->first->abr);

    //Liberation de la memoire
    printf("avant suppr: %d\n",l->first->abr->freq);
    destruction_liste(&l);
    printf("apres suppr: %d\n",l->first->abr->freq);



    //Fermeture fichier
    fermeture_fichier(fic);
    return 0;
}

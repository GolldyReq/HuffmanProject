#include <stdio.h>
#include <stdlib.h>
#include "fic.h"
#include "arbre.h"
#include "liste.h"
#include "huffman.h"
#include "binarypath.h"

int main()
{
    //Ouverture fichier
    FILE *fic=NULL;
    char* file="test.txt";
    fic=ouverture_fichier(file);
    //Creation fichier compressé
    FILE *f=NULL;
    f=creation_fichier("compress.txt");


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
    int nb_car=0;
    for(int i=32;i<126;i++)
    {
        if(occurence[i]!=0)
        {
            //printf("%c : %d\n",(char)i,occurence[i]);
            add_in_initial_liste(l,(char)i,occurence[i]);
            afficher_liste(l);
            printf("#######################\n");
            nb_car++;
        }
    }
    //construction de l'arbre de Huffman
    construction_arbre_huffman(l);


    int a=nb_feuille(l->first->abr);
    printf("nombre de feuille : %d\n",a);
    BinaryPath *bp=newBinaryPath();

    parcours_arbre_infixe_bp(l->first->abr,bp);

    //ecriture nb de caractere total
    int gr=nombre_caractere(fic);
    fprintf(f,"%d\n",gr);
    //ecriture nombre de caractere different
    unsigned char i=nb_car;
    fprintf(f,"%d\n",i);
    //ecriture des caractere
    ecrire_caractere(l->first->abr,f);



    //Liberation de la memoire
    printf("avant suppr: %d\n",l->first->abr->freq);
    destruction_liste(&l);
    printf("apres suppr: %d\n",l->first->abr->freq);



    //Fermeture des fichiers
    fermeture_fichier(fic);
    fermeture_fichier(f);
    return 0;

}

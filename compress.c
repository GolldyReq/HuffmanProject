#include <stdio.h>
#include <stdlib.h>

#include "compress.h"
#include "fic.h"
#include "arbre.h"
#include "liste.h"
#include "huffman.h"
#include "binarypath.h"
#include <string.h>


void compress_file(char *file){


    //Ouverture fichier
    FILE *fic=NULL;
    fic=ouverture_fichier(file);
    //Creation fichier compressé
    FILE *f=NULL;
    char file_out[50];
    strcpy(file_out,file);
    strcat(file, ".hf");
    f=creation_fichier(file);

    //Tableau d'occurence l'indice du tableau
    //représente la lettre et la valeur sa fréquence d'appartion
    int occurence[128];
    for(int i=0;i<128;i++)
        occurence[i]=0;
    //calcul de la fréquence d'apparition
    calcul_occurence(fic,occurence);
    //Creation des arbres possedant une unique feuille
    //et de la liste chainé trié par fréquence de ces arbres
    Liste *l=NULL;
    l=create_liste();
    for(int i=0;i<126;i++)
    {
        if(occurence[i]!=0)
            add_in_initial_liste(l,(char)i,occurence[i]);
    }

    //construction de l'arbre de Huffman
    construction_arbre_huffman(l);

    BinaryPath *bp=newBinaryPath();

    parcours_arbre_infixe_bp(l->first->abr,bp);

    //ecriture nb de caractere total
    int gr=nombre_caractere(fic);
    fprintf(f,"%d\n",gr);
    //ecriture nombre de caractere different
    int nb_car=nb_feuille(l->first->abr);
    unsigned char i=nb_car;
    fprintf(f,"%d\n",i);
    //ecriture des caractere
    ecrire_caractere(l->first->abr,f);
    //ecriture du parcours de l'arbre
    ecriture_parcours(l->first->abr,f);
    //ecriture du texte
    T_huffman *tableau_h=NULL;
    tableau_h=create_table();
    BinaryPath *pb=newBinaryPath();
    creation_table_huffman(l->first->abr,tableau_h,pb);
    afficher_tableau_huffman(tableau_h);
    compresser_texte(fic,tableau_h,f);

    //Liberation de la memoire
    printf("avant suppr: %d\n",l->first->abr->freq);
    destruction_liste(&l);
    printf("apres suppr: %d\n",l->first->abr->freq);

    //Fermeture des fichiers
    fermeture_fichier(fic);
    fermeture_fichier(f);

}

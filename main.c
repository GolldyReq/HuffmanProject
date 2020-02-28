#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#include "decompress.h"



/**

/!\IMPORTANT/!\
Utilisation du projet :
1er argument : compress OU decompress   /!\OBLIGATOIRE/!\
               l'argument both compress et decompresse le fichier
2e argument : nom du fichier (en .txt si compress et .hf si decompress) /!\OBLIGATOIRE/!\
autres argument : -w (write) nom_fichier-> ecrit la decompression dans un fichier txt au lieu de l'afficher sur la console (optionnel)
                 par défault -> decompress.txt (optionnel)
                 -v pour le mode verbose avec l'affichage de l'arbre version 1(optionnel)
                 -V pour le mode verbose avec l'affichage de l'arbre version 2(optionnel)
                 -e pour afficher les entetes du fichiers (nb caractere total, nb caractere distinct...)
**/

void affichage_argument()
{
    printf("Liste des arguments du programme:\n\n");
    printf("help : \n\taffiche l'aide\n");
    printf("compress nom_fichier.txt : \n\tpermet de compresser le fichier txt\n");
    printf("decompress nom_fichier.hf : \n\tpermet de decompresser un fichier compressé\n");
    printf("both nom_fichier.txt : \n\tcompresse ET decompresse un fichier\n");
    printf("-w fichier_sortie : \n\tmode ecriture, decompresse le fichier dans un .txt\n");
    printf("-v fichier_sortie : \n\tmode verbose, affiche l'arbre de Huffman\n");
    printf("-V fichier_sortie : \n\tmode verbose, affiche la table de Huffman\n");
    printf("-e fichier_sortie : \n\tmode entete, affiche l'entete et les caracteristiques du fichier\n");
}

int main(int nbarg,char **argv)
{

    if(nbarg<2)
    {
        fprintf(stderr,"veuillez saisir au moins un argument\n");
        affichage_argument();
        exit(-1);
    }


    //Demande d'aide
    if(strcmp(argv[1],"help")==0)
    {
        printf("/////PAGE D'AIDE DU PROGRAMME DE COMPRESSION/DECOMPRESSION/////\n\n");
        printf("Ce programme vous permet de compresser et de decompresser des fichiers textes\n\n");
        affichage_argument();
        exit(1);
    }


    //compression + decompression
    if(strcmp(argv[1],"both")==0 && nbarg>=3)
    {
        compress_file(argv[2]);
        decompress_file(argv[2]);
        exit(0);
    }

    if(strcmp(argv[1],"compress")!=0 && strcmp(argv[1],"decompress")!=0)
    {
        printf("%s\n",argv[1]);
        fprintf(stderr,"mauvais argument saisie\n");
        exit(-2);
    }

    if(strcmp(argv[1],"compress")==0&& nbarg>=3)
    {
        printf("lancement de la compression du fichier %s ....\n",argv[2]);
        compress_file(argv[2]);
    }

    if(strcmp(argv[1],"decompress")==0&& nbarg>=3)
    {
        printf("lancement de la decompression du fichier %s ....\n",argv[2]);
        decompress_file(argv[2]);
    }
    return 0;


}

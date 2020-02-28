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
3e argument : -w (write) -> ecrit la decompression dans un fichier txt au lieu de l'afficher sur la console (optionnel)
4e argument : nomfichier -> seulement si l'argument -w est demand�, par d�fault -> decompress.txt (optionnel)
5e argument : -v pour le mode verbose avec l'affichage de l'arbre version 1(optionnel)
              -V pour le mode verbose avec l'affichage de l'arbre version 2(optionnel)
**/

int main(int nbarg,char **argv)
{
    for(int i=0;i<nbarg;i++)
        printf("%d : %s\n",i,argv[i]);


    if(nbarg<3)
    {
        fprintf(stderr,"veuillez saisir au moins 2 arguments\n");
        exit(-1);
    }
    //compression + decompression
    if(strcmp(argv[1],"both")==0)
    {
        compress_file(argv[2]);
        decompress_file(argv[2]);
        exit(3);
    }

    if(strcmp(argv[1],"compress")!=0 && strcmp(argv[1],"decompress")!=0)
    {
        printf("%s\n",argv[1]);
        fprintf(stderr,"mauvais argument saisie\n");
        exit(-2);
    }

    if(strcmp(argv[1],"compress")==0)
    {
        printf("lancement de la compression du fichier %s ....\n",argv[2]);
        compress_file(argv[2]);
    }

    if(strcmp(argv[1],"decompress")==0)
    {
        printf("lancement de la decompression du fichier %s ....\n",argv[2]);
        decompress_file(argv[2]);
    }
    return 0;


}

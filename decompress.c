#include <stdlib.h>
#include <stdio.h>
#include "decompress.h"
#include "binarypath.h"

void decompress_file(char *file)
{
    FILE *fic=NULL;
    fic=ouverture_fichier(file);
    int nb_car_total;
    rewind(fic);

    int nb_caractere_total,nb_feuille;
    fscanf(fic,"%d\n%d\n",&nb_caractere_total,&nb_feuille);
    printf("nb de caractere au total : %d\n",nb_caractere_total);
    printf("nb de feuille : %d\n",nb_feuille);
    char c[nb_feuille];
    for(int i=0;i<nb_feuille;i++)
    {
        c[i]=fgetc(fic);
        printf("%c",c[i]);
    }
    fgetc(fic);
    fgetc(fic);
    printf("\n");
    BinaryPath *chemin_arbre=newBinaryPath();
    char tmp=fgetc(fic);
    while(tmp!='\n')
    {
        printf("tmp : %c\n",tmp);
        if(tmp=='1' || tmp=='0')
            ajout_bits(chemin_arbre,tmp);
        tmp=fgetc(fic);
    }
    printf("\n\nchemin de l'arbre :");
    afficher_BinaryPath(chemin_arbre);
    reconstruction_arbre(chemin_arbre,c);


    /*
    fread(&nb_car_total,sizeof(int),1,fic);
    printf("nb de caratere : %d",&nb_car_total);
    */
    fermeture_fichier(fic);

}

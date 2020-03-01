#include <stdlib.h>
#include <stdio.h>
#include "fic.h"
#include "binarypath.h"
#include "element.h"

FILE* ouverture_fichier(char *file_name)
{
    //printf("Ouverture du fichier %s \n",file_name);
    FILE *f=fopen(file_name, "r+b");
    if(f==NULL)
    {
        fprintf(stderr,"erreur lors de l'ouverture");
        exit(-1);
    }
    return f;
}

FILE* creation_fichier(char *file_name)
{
    //printf("Ouverture du fichier %s \n",file_name);
    FILE *f=fopen(file_name, "w");
    if(f==NULL)
    {
        fprintf(stderr,"erreur lors de l'ouverture");
        exit(-1);
    }
    return f;
}

void fermeture_fichier(FILE *fic)
{
    //Evaluation du code de retour de fclose()
    if(fclose(fic))
    {
        fprintf(stderr,"erreur lors de la fermeture\n");
        exit(-2);
    }
}

void calcul_occurence(FILE *fic,int *tab)
{
    rewind(fic);
    char car=fgetc(fic);
    while(car!=EOF)
    {
        //Gestion majuscule
        if(car>=65 && car<=90 )
            car=car+32;
        tab[(int)car]++;
        car=fgetc(fic);
    }
}

int nombre_caractere(FILE *f)
{
    rewind(f);
    int compteur=0;
    char c=fgetc(f);
    while (c!=EOF)
    {
        compteur++;
        c=fgetc(f);
    }
    return compteur;
}


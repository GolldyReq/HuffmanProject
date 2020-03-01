#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "decompress.h"
#include "binarypath.h"
#include "liste.h"
#include "fic.h"
#include "huffman.h"

int arg=0;

char* get_file_name(char** argv)
{
    for(int i=0;i<arg-1;i++)
    {
        if(strcmp(argv[i],"-w")==0)
            return argv[i+1];
    }
    return "decompress.txt";
}

int recherche_argument(char **argv,char *search)
{
    for(int i=0;i<arg;i++)
    {
        if(strcmp(argv[i],search)==0)
            return 1;
    }
    return 0;
}

int recherche_mot(BinaryPath *mot,T_huffman *th,FILE *out,char **argv)
{
    THuffman_elt *actuel=th->first;
    while(actuel!=NULL)
    {
        if(egalite_bp(mot,&actuel->code))
        {
            printf("%c",actuel->car);
            if(recherche_argument(argv,"-w")==1)
                fprintf(out,"%c",actuel->car);
            return 1;
        }
        actuel=actuel->next;
    }
    return 0;
}

void traduction_bp(T_huffman *th,BinaryPath *binaire,char* nb,char **argv)
{
    FILE *out=NULL;
    if(recherche_argument(argv,"-w")==1)
    {
        char *fichier_sortie=get_file_name(argv);
        out=fopen(fichier_sortie,"w+b");
        if(out==NULL)
            exit(-3);
    }

    int objectif=atoi(nb);
    BinaryPath *mot=newBinaryPath();
    int lettre_trouve=0;
    int i=0;
    while(i<binaire->longueur)
    {
        ajout_bits(mot,binaire->Bcode[i]);
        if(lettre_trouve<objectif)
        {
            //ajout_bits(mot,binaire->Bcode[i]);
            if(recherche_mot(mot,th,out,argv))
            {
                lettre_trouve++;
                while(mot->longueur!=0)
                    enlever_bits(mot);
            }
        }
        i++;
    }
    if(!zero(mot))
    {
        BinaryPath *last=newBinaryPath();
        int i=0;
        while(!zero(mot))
        {
            ajout_bits(last,mot->Bcode[i]);
            if(recherche_mot(last,th,out,argv))
            {
                while(last->longueur!=0)
                    {enlever_bits(last);
                    enlever_premier_bits(mot);}
                    i=0;
            }
            else
                i++;
        }
    }
    fclose(out);
}

void stocker_dans_le_bp(unsigned char buffer,BinaryPath *binaire)
{
    for(int i=0;i<8;i++)
    {
        int bit=buffer>>7;
        if(bit==1)
            ajout_bits(binaire,'1');
        else
            ajout_bits(binaire,'0');
        buffer = buffer << 1;
    }
}


//////////////////////////////////////////
//////////////////////////////////////////
void decompress_file(char **argv,int nbarg)
{
    arg=nbarg;


    FILE *fic=ouverture_fichier(argv[2]);
    rewind(fic);
    char *nb_caractere_total,*nb_feuille;
    nb_caractere_total=(char*)malloc(10*sizeof(char));
    nb_feuille=(char*)malloc(3*sizeof(char));
    fgets(nb_caractere_total,8,fic);
    fgets(nb_feuille,3,fic);
    //A mettre en argument
    //printf("nb de caractere au total : %s\n",nb_caractere_total);
    //printf("nb de feuille : %s\n",nb_feuille);
    if(atoi(nb_feuille)>=10)
        fseek(fic,2,SEEK_CUR);
    /*pasur*/
    else
        fseek(fic,1,SEEK_CUR);

    char c[atoi(nb_feuille)];
    //remplacer par une boucle for en gerant le '\n'

    //Prendre des screens test pour expliquer dans le rapport
    fgets(c,128,fic);
    while(strlen(c)<atoi(nb_feuille))
    {
        c[strlen(c)-1]='\0';
        c[strlen(c)-1]=(char)10;
        char d[atoi(nb_feuille)];
        fgets(d,128,fic);
        strcat(c,d);
        c[strlen(c)-2]='\0';
    }
    //A screen pour montrer la chaine recuperer et l'utilite du code au dessus !
    /*
    for(int p=0;p<strlen(c);p++)
        printf("%d,",c[p]);
    */

    char *line=(char*)malloc(500*sizeof(char));
    fgets(line,500,fic);
    BinaryPath *chemin_arbre=newBinaryPath();
    for(int i=0;i<strlen(line)-1;i++)
        ajout_bits(chemin_arbre,line[i]);

    if(recherche_argument(argv,"-e")==1)
    {
        printf("nombre de caractere total : %d\n",atoi(nb_caractere_total));
        printf("nombre de caractere distinct : %d\n",atoi(nb_feuille));
        printf("liste des caracteres : %s \n",c);
        printf("chemin de l'arbre en parcours infixe : \n");
        afficher_BinaryPath(chemin_arbre);
        printf("\n");
    }

    //printf("\n\n chemin de l'arbre :");
    //afficher_BinaryPath(chemin_arbre);

    //Construction table de Huffman
    T_huffman *table_h=reconstruction_arbre(chemin_arbre,c);

    if(recherche_argument(argv,"-v")==1)
        afficher_tableau_huffman(table_h);

    unsigned char buffer=0;
    BinaryPath *binaire=newBinaryPath();
    //recuperation de l'encodage binaire du fichier
    while (fread(&buffer,1,1,fic) == 1) {
        stocker_dans_le_bp(buffer,binaire);
    }

    //le texte compressé en binaire
    //afficher_BinaryPath(binaire);

    traduction_bp(table_h,binaire,nb_caractere_total,argv);
    printf("\n");

    fermeture_fichier(fic);
}

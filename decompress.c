#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "decompress.h"
#include "binarypath.h"
#include "liste.h"


int recherche_mot(BinaryPath *mot,T_huffman *th,FILE *out)
{
    THuffman_elt *actuel=th->first;
    while(actuel!=NULL)
    {
        if(egalite_bp(mot,&actuel->code))
        {
            printf("%c",actuel->car,actuel->car);
            //fwrite(actuel->car,1,1,out);
            fprintf(out,"%c",actuel->car);
            return 1;
        }
        actuel=actuel->next;
    }
    return 0;

}

void traduction_bp(T_huffman *th,BinaryPath *binaire,char* nb)
{
    FILE *out=fopen("decompression.txt","w+b");
    if(out==NULL)
        exit(-32);
    int objectif=atoi(nb);
    BinaryPath *mot=newBinaryPath();
    int lettre_trouve=0;
    int i=0;
    printf("NOMBRE DE LETTRE A TROUVER : %d\n",objectif);
    while(i<binaire->longueur)
    {
        ajout_bits(mot,binaire->Bcode[i]);
        if(lettre_trouve<objectif)
        {
            //ajout_bits(mot,binaire->Bcode[i]);
            if(recherche_mot(mot,th,out))
            {
                lettre_trouve++;
                //Bug chelou texte long
                //printf("<- lettre : %d\n",lettre_trouve);
                while(mot->longueur!=0)
                    enlever_bits(mot);
            }
        }
        i++;
    }
    if(!zero(mot))
    {
        printf("\nvidage de ce buffer de merde\n");
        BinaryPath *jsp=newBinaryPath();
        for(int i=0;i<mot->longueur;i++)
        {
            ajout_bits(jsp,mot->Bcode[i]);
            if(recherche_mot(jsp,th,out))
            {
                printf("\n mot trouve \n");
                while(jsp->longueur!=0)
                    {enlever_bits(jsp);
                    enlever_premier_bits(mot);
                    afficher_BinaryPath(mot);}
            }
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
void afficher_octet_en_binaire(const char texte[], unsigned char octet) {
    printf("%s", texte);
    for (int i = 0; i < 8; i++) {
	int bit = octet >> 7;
	printf("%d", bit);
	octet = octet << 1;
    }
}

void decompress_file(char *file)
{
    FILE *fic=NULL;
    fic=ouverture_fichier(file);
    int nb_car_total;
    rewind(fic);

    char *nb_caractere_total,*nb_feuille;
    nb_caractere_total=(char*)malloc(10*sizeof(char));
    nb_feuille=(char*)malloc(3*sizeof(char));
    fgets(nb_caractere_total,8,fic);
    fgets(nb_feuille,3,fic);
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
    int nb_ligne_entete=0;
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
    for(int p=0;p<strlen(c);p++)
        printf("%d,",c[p]);


    char *line=(char*)malloc(500*sizeof(char));
    fgets(line,500,fic);
    BinaryPath *chemin_arbre=newBinaryPath();
    for(int i=0;i<strlen(line)-1;i++)
        ajout_bits(chemin_arbre,line[i]);



    //printf("\n\n chemin de l'arbre :");
    //afficher_BinaryPath(chemin_arbre);

    T_huffman *table_h=reconstruction_arbre(chemin_arbre,c);
    afficher_tableau_huffman(table_h);
    unsigned char buffer=0;
    BinaryPath *binaire=newBinaryPath();
    while (fread(&buffer,1,1,fic) == 1) {
        stocker_dans_le_bp(buffer,binaire);
    }

    //le texte compressé en binaire
    //afficher_BinaryPath(binaire);

    traduction_bp(table_h,binaire,nb_caractere_total);
    printf("\n");

    fermeture_fichier(fic);

}

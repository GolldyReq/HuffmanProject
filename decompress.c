#include <stdlib.h>
#include <stdio.h>
#include "decompress.h"
#include "binarypath.h"
#include "liste.h"


int recherche_mot(BinaryPath *mot,T_huffman *th)
{
    THuffman_elt *actuel=th->first;
    while(actuel!=NULL)
    {
        if(egalite_bp(mot,&actuel->code))
        {
            printf("%c",actuel->car);
            return 1;
        }
        actuel=actuel->next;
    }
    return 0;

}

void traduction_bp(T_huffman *th,BinaryPath *binaire,char* nb)
{
    int objectif=atoi(nb);
    BinaryPath *mot=newBinaryPath();
    int lettre_trouve=0;
    int i=0;
    printf("NOMBRE DE LETTRE A TROUVER : %d\n",objectif);
    while(i<binaire->longueur)
    {
        if(lettre_trouve<objectif)
        {
            ajout_bits(mot,binaire->Bcode[i]);
            if(recherche_mot(mot,th))
            {
                lettre_trouve++;
                while(mot->longueur!=0)
                    enlever_bits(mot);
            }
        }
        i++;
    }
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
    printf("nb de caractere au total : %s\n",nb_caractere_total);
    printf("nb de feuille : %s\n",nb_feuille);

    fseek(fic,2,SEEK_CUR);

    char c[atoi(nb_feuille)];
    //remplacer par une boucle for en gerant le '\n'

    //Prendre des screens test pour expliquer dans le rapport
    fgets(c,128,fic);
    if(strlen(c)<atoi(nb_feuille))
    {
        c[strlen(c)-1]='\0';
        c[strlen(c)-1]=(char)10;
        char d[atoi(nb_feuille)];
        fgets(d,128,fic);
        for(int i=0;i<strlen(d);i++)
            printf("-->%d",d[i]);
        strcat(c,d);
        c[strlen(c)-2]='\0';
    }

    printf("voici les caractere lu :%s\n",c);
    printf("taille lu :%d\n",strlen(c));
    for(int i=0;i<strlen(c);i++)
        printf("->%d",c[i]);

    printf("\n");

    char *line=(char*)malloc(500*sizeof(char));
    fgets(line,500,fic);
    printf("Chemin arbre :::: %s",line);
    BinaryPath *chemin_arbre=newBinaryPath();
    for(int i=0;i<strlen(line)-1;i++)
    {
        ajout_bits(chemin_arbre,line[i]);
    }



    //printf("\n\nchemin de l'arbre :");
    //afficher_BinaryPath(chemin_arbre);

    T_huffman *table_h=reconstruction_arbre(chemin_arbre,c);
    //afficher_tableau_huffman(table_h);
    unsigned char buffer=0;
    BinaryPath *binaire=newBinaryPath();
    while (fread(&buffer,1,1,fic) == 1) {
        stocker_dans_le_bp(buffer,binaire);
    }
    //afficher_BinaryPath(binaire);


    BinaryPath *mot_tmp=newBinaryPath();
    ajout_bits(mot_tmp,'0');
    ajout_bits(mot_tmp,'0');

    traduction_bp(table_h,binaire,nb_caractere_total);
    printf("\n");

    fermeture_fichier(fic);

}

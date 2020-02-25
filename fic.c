#include <stdlib.h>
#include <stdio.h>
#include "fic.h"
#include "binarypath.h"
#include "element.h"

FILE* ouverture_fichier(char *file_name)
{
    printf("Ouverture du fichier %s \n",file_name);
    FILE *f=fopen(file_name, "r+");
    if(f==NULL)
    {
        fprintf(stderr,"erreur lors de l'ouverture");
        exit(-1);
    }
    return f;

}

FILE* creation_fichier(char *file_name)
{
    printf("Ouverture du fichier %s \n",file_name);
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
    if(!fclose(fic))
    {
        printf("Fermeture du fichier : OK\n");
    }
    else
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

void ecriture_taille(FILE *f,int *taille)
{
    fwrite(taille, sizeof(int), 4, f);
}


void parcours_infixe_char(Arbre *abr,FILE *f)
{
    if(abr==NULL)
        return;
    parcours_infixe_char(abr->gauche,f);
    if(isFeuille(abr))
        fprintf(f,"%c",abr->car);
    parcours_infixe_char(abr->droite,f);
}
void ecrire_caractere(Arbre *abr,FILE *f)
{
    parcours_infixe_char(abr,f);
    fprintf(f,"\n");
}

void parcours_infixe_bp(Arbre *abr,FILE *f,BinaryPath *bp)
{
    if(isFeuille(abr))
        return;
    //descente dans l'arbre
    ajout_bits(bp,'0');
    parcours_infixe_bp(abr->gauche,f,bp);
    //montee dans l'arbre
    ajout_bits(bp,'1');
    //descente dans l'arbre
    ajout_bits(bp,'0');
    parcours_infixe_bp(abr->droite,f,bp);
    //montee dans l'arbre
    ajout_bits(bp,'1');
    printf("fin de parcours infixe : %c\n",abr->car);

}

void suppression_un(Arbre *abr,BinaryPath *bp)
{
    //Pour conserver le premier '1' marquant la fin du parcours
    if(isFeuille(abr->droite))
        return;
    enlever_bits(bp);
    suppression_un(abr->droite,bp);
}

void ecriture_parcours(Arbre *abr,FILE *f)
{
    //Création du chemin binaire du parcours de l'arbre
    BinaryPath *bp=newBinaryPath();
    //Parcours infixe
    parcours_infixe_bp(abr,f,bp);
    //Suppression des 1 en trop a la fin du parcours lorsqu'on remonte a la racine
    suppression_un(abr,bp);
    for(int i=0;i<bp->longueur;i++)
        fprintf(f,"%c",bp->Bcode[i]);
    fprintf(f,"\n");

}


void afficher_octet_en_binaire(const char texte[], unsigned char octet) {
    printf("%s", texte);
    for (int i = 0; i < 8; i++) {
	int bit = octet >> 7;
	printf("%u", bit);
	octet = octet << 1;
    }
}


void ecrire_binary_path(char c,T_huffman *th,FILE *outfile,unsigned char *buffer,int *taille)
{
    THuffman_elt *actuel = th->first;
    int trouve=0;
    while(actuel!=NULL || trouve==0)
    {
        if(actuel->car==c)
        {
            trouve=1;
            for(int i=0;i<actuel->code.longueur;i++)
            {
                if(actuel->code.Bcode[i]=='1')
                    {*buffer=(*buffer<<1) | 1;}
                else
                    {*buffer=(*buffer<<1) | 0;}

                *taille=*taille+1;
                if(*taille==8)
                   {
                        printf("vider buffer : ");
                        /*
                        for (int i = 0; i < 8; i++) {
                            int bit = *buffer >> 7;
                            fprintf(outfile,"%u", bit);
                            *buffer = *buffer << 1;
                        }
                        */
                        //Tester fwrite pour l'opti
                        fwrite(buffer,1,1,outfile);
                        //fwrite(buffer,sizeof(*buffer),sizeof(unsigned char),outfile);
                        *buffer=0;
                        *taille=0;
                   }
            }
        }
        actuel=actuel->next;
    }
}

void compresser_texte(FILE *entry,T_huffman *th,FILE *outfile)
{
    unsigned char buffer=0;
    int taille_buffer=0;
    rewind(entry);
    char c=fgetc(entry);
    printf("%c\n",c);
    while(c!=EOF)
    {
        ecrire_binary_path(c,th,outfile,&buffer,&taille_buffer);
        c=fgetc(entry);
    }
    //Ecrire ce qu'il reste dans le buffer et le vider

        /*
        for (int i = 0; i < 8; i++) {
            int bit = buffer >> 7;
            //Ligne a remplacer //
            if(taille_buffer==2)
                fprintf(outfile,"%u",bit);
            else
                taille_buffer--;
            buffer = buffer << 1;
        }
        */
        buffer=(buffer<<5);
        fwrite(&buffer,1,1,outfile);
        //Il reste des 0 "en trop" placé a la fin du fichier
        //Mais ils pésent moins d'un octet -> on les laisse
}

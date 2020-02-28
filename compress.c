#include <stdio.h>
#include <stdlib.h>

#include "compress.h"
#include "fic.h"
#include "arbre.h"
#include "liste.h"
#include "huffman.h"
#include "binarypath.h"
#include <string.h>


void ecriture_taille(FILE *f,int *taille)
{
    fwrite(taille, sizeof(int),1, f);
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

void ecrire_binary_path(char c,T_huffman *th,FILE *outfile,unsigned char *buffer,int *taille)
{
    //Gestion majuscule
    if((int)c>64 && (int)c<91)
        c=c+32;
    THuffman_elt *actuel = th->first;
    while(actuel!=NULL)
    {
        if(actuel->car==c)
        {
            for(int i=0;i<actuel->code.longueur;i++)
            {
                if(actuel->code.Bcode[i]=='1')
                    *buffer=(*buffer<<1) | 1;
                else
                    *buffer=(*buffer<<1) | 0;
                *taille=*taille+1;
                //L'octet est rempli, on vide le buffer
                if(*taille==8)
                   {
                        fwrite(buffer,1,1,outfile);
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
    while(c!=EOF)
    {
        ecrire_binary_path(c,th,outfile,&buffer,&taille_buffer);
        c=fgetc(entry);
    }
    //Ecrire ce qu'il reste dans le buffer et le vider
    buffer=(buffer<<8-taille_buffer);
    fwrite(&buffer,1,1,outfile);
    //Il reste des 0 "en trop" placé a la fin du fichier
    //Mais ils pésent moins d'un octet -> on les laisse
}




void compress_file(char *file){


    //Ouverture fichier
    FILE *fic=NULL;
    fic=ouverture_fichier(file);
    //Creation fichier compresse
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
    for(int i=0;i<128;i++)
    {
        if(occurence[i]!=0)
            add_in_initial_liste(l,(char)i,occurence[i]);
    }

    //afficher_liste(l);


    //construction de l'arbre de Huffman
    construction_arbre_huffman(l);


/*
    BinaryPath *bp=newBinaryPath();
    parcours_arbre_infixe_bp(l->first->abr,bp);
*/

    //PARTIE COMPRESSION
    printf("compression en cours....\n");
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

    //Creation table de huffman
    T_huffman *tableau_h=NULL;
    tableau_h=create_table();
    BinaryPath *pb=newBinaryPath();
    creation_table_huffman(l->first->abr,tableau_h,pb);

    //afficher_tableau_huffman(tableau_h);

    //Compression du texte
    compresser_texte(fic,tableau_h,f);

    //Liberation de la memoire
    //printf("avant suppr: %d\n",l->first->abr->freq);
    destruction_liste(&l);
    //printf("apres suppr: %d\n",l->first->abr->freq);

    //Fermeture des fichiers
    fermeture_fichier(fic);
    fermeture_fichier(f);

}

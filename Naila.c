#include <stdio.h>
#include <stdlib.h>
 typedef struct 
 {
   char ch[1000];
 }buffer,bloc;
//ENTETE 
typedef struct Entete{
    int nb_btete;//le numero de premier bloc
    int nbbloc;
    int nbenreg;
}Entete;
//declaration de la structure de l'enregistrement 
typedef struct enreg {
 lenreg  *svt ;
    char marque[10];
    char modele[100];
    char moteur[100]; 
    char reference[100];    }lenreg;
 
typedef struct  LOF{
Entete entete;
FILE *NIH ;
 }LOF;

//FONCTION QUI OUVRE LE FICHIER
LOF* OPEN (char filename[100],const char mode)
{
LOF (*FILE )=malloc(sizeof(LOF));
if ((mode=='n')||(mode=='N'))//si le mode est nouveau (n,N)
    {   FILE->NIH=fopen(filename,"wb+");
        FILE->entete.nb_btete=0;
        FILE->entete.nbenreg=0; 
        FILE->entete.nbbloc=0;
        fwrite(&(FILE->entete),sizeof(Entete),1,FILE->NIH);
    }
    else
    {
        if ((mode=='a')||(mode=='A'))//si le mode est ancien (a,A)
        {
          FILE->NIH=fopen(filename,"rb+");
          fread(&(FILE->entete),sizeof(Entete),1,FILE->NIH);
        }
        else printf("incorrect mode");
    }
    return FILE;
}

  
int main()
{
    LOF *f ;
     f->NIH = fopen("AUDI.txt","r+");
   if (f->NIH== NULL)
   {
       printf("ERREUR !!!!\n");
       return -1;
   }

    return 0;
}

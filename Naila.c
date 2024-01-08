#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T_Bloc 300
 typedef struct 
 {
   char ch[1000];
 }buffer;
//ENTETE 
typedef struct Entete{
    int nbbloc;
    int nbenreg;
}Entete;
//declaration de la strecture enregistrement 
typedef struct enreg {
 typedef struct lenreg *enreg{
 lenreg  *svt ;
    char nom[10];
    char prenom[10];     }lenreg;
}enreg;
 
typedef struct  LOF{
Entete entete;

FILE *NIH=NULL;
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

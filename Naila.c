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
    int numtete;
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
 //procedure modification de lentete
 void modif_entete(LOF*FILE,int num,int val)
 {
    if (num==1){
      FILE->entete.numtete=val;
    }
    if (num==2){
      FILE->entete.nbenreg=val;
    }
    if (num==3){
      FILE->entete.nbbloc=val;

    }

 }
 //Retourner la valeur du numero afficher
 int entete(LOF*FILE,int num)
 {
    int val;
   if (num==1){
     val=FILE->entete.numtete;
    }
    if (num==2){
      val=FILE->entete.nbenreg;
    }
    if (num==3){
      val=FILE->entete.nbbloc;
      return val;

    } 
 }

//FONCTION QUI OUVRE LE FICHIER
LOF* OPEN (char filename[100],const char mode)
{
LOF (*FILE )=malloc(sizeof(LOF));
if ((mode=='n')||(mode=='N'))//si le mode est nouveau (n,N)
    {   FILE->NIH=fopen(filename,"wb+");
        FILE->entete.numtete=0;
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
//procedure fermeture du fichier 
void CLOSED (LOF*FILE)
{
    rewind(FILE->NIH);
    fwrite(&(FILE->entete),sizeof(Entete),1,FILE->NIH);
    fclose(FILE->NIH);
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

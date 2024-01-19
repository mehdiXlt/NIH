<#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T_Bloc 300
 typedef struct 
 {
   char ch[1000];
 }buffer;

 //declaration du bloc 
 typedef struct TBloc{
typedef struct list *TBloc
{
int T[T_Bloc];//tableau d'enregistrement
int Nb;//le nombre d'enregistrement dans le tableau
TBloc * suiv;//le nombre de prochain bloc
}list;
}TBloc;

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
                                                          /*********************************/

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


                                                                 /*********************************/
//procedure pour lire directement depuis le fichier et stocker dans le buffer a la position i                                                                 
 void lecture(LOF*FILLE,int i,TBloc buffer )
 {
    if(i != 1)
    {
      // Se positionne à la position exacte dans le fichier en utilisant fseek
      fseek(FILLE->NIH,sizeof(entete)+((i-1)*sizeof(TBloc)), SEEK_SET);//SEEK_SET :pour faire un décalage a partir du debut du fichier 
     // Lit les données d'un bloc depuis la position courante dans le fichier
      freed(buffer,sizeof(TBloc),1,FILLE->NIH);//lire une suele données dans le fichier et la stockée dans le buffer  
      rewind(FILLE->NIH);//pour remet le curceur au debut de fichier 
    }


 }
                                                 /*****************************************/
//procedure pour ecrire directement sur le fichier 
void ecrire_dir(LOF *FILLE,int i,TBloc *buffer)//ecriture directe du contenu de buf dans le fichier a la position i
{   if (i!=-1){ 
    fseek(FILLE->NIH,sizeof(En_Tete)+((i-1)*sizeof(TBloc)),SEEK_SET);//se positionner a la place exacte
    fwrite(buffer,sizeof(TBloc),1,FILLE->NIH);//ecriture
    rewind(FILLE->NIH);}//on se positionne au debut de fichier
}


                                                           /************************************/

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
                                                           /************************************/
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
                                                /*****************************************/
//procedure fermeture du fichier 
void CLOSED (LOF*FILE)
{
    rewind(FILE->NIH);
    fwrite(&(FILE->entete),sizeof(Entete),1,FILE->NIH);
    fclose(FILE->NIH);
}
                                                /*****************************************/
//procedure d'allocation d'un bloc
void alloc_bloc(LOF *FILLE,int *i,TBloc *buff)
{
  int j;
  *i=entete(FILLE,3)+1;
  buff->suiv=-1;//Initialise le champ suiv du bloc buff à -1.
    buf->Nb = 0;  // Initialise le champ Nb du bloc buff à 0.
  buff->nb=0;
 for(j=0;j<T_Bloc;j++)//intialise tout les champs de tableau a 0;
 {
  buff->T[j]=0;
 } 
modif_entete(FILLE,3,entete(FILLE,3)+1);// Met à jour l'entête du fichier avec la nouvelle valeur obtenue.
}



void afficherLOF(LOF *l)//a chaque foix quand on crée un bloc on l'affiche 
{
    TBloc Buffer;  // Déclaration d'une variable de type TBloc pour stocker temporairement les données d'un bloc
    int i, j;   // Variables d'itération et de stockage

    i = entete(l, 1);  // Obtient le numéro du premier bloc à partir de l'entête du fichier

    while (i != -1)  // Continue tant qu'il y a des blocs à parcourir (la valeur -1 indique la fin de la liste)
    {
        j = 0;  // Réinitialise l'indice pour parcourir le tableau T du bloc actuel

        lecture(l, i, &Buffer);  // Lit les données du bloc courant dans la variable Buf

        printf(" Numero du  BLOC %d \n", i);  // Affiche le numéro du bloc courant

        while (j < Buffer.Nb)  // Parcourt les éléments du tableau T du bloc courant
        {
            printf("%3d %10d \n", j, Buffer.T[j]);  // Affiche l'indice et la valeur de chaque élément du tableau
            j++;
        }

        i = Buffer.suiv;  // Met à jour i avec le numéro du prochain bloc dans la séquence
    }

                                             /*****************recherche*******************/

 void rech_sequentielle(LOF *fichier,int cle,int *i,int *j,int *q,int *trouv)//module de recherche de la cle ds un fichier
{
    TBloc buf;//declarer un buffer
    int b,arret,Inf,Sup,Vlast=0;//donne le nummero de bloc courant
    if (fichier->f!=NULL)//tester si le fichier existe
    {
          *trouv=0; // Initialiser la variable de résultat de recherche
          *j=0;*q=-1;
           *i=entete(fichier,1); // Obtenir l'en-tête du fichier pour commencer la recherche
           // Vérifier si le fichier est vide
           if(*i==0)
           {
              printf("\n \t\t<<Le fichier est vide>>");//tester si le fichier n'est pas vide
           }
           else
           {
             arret=FALSE;   // Variable pour indiquer si la recherche doit s'arrêter

             // Boucle de recherche dans les blocs du fichier
              while((*i!=-1)&&(!arret))
              {
               lire_dir(fichier,*i,&buf);//lire le bloc i
               if (buf.Nb!=0)
               {
                b=buf.Nb-1;// Indice du dernier élément dans le bloc
                if ((buf.T[0]<=cle)&&(buf.T[b]>=cle ))
                 {
                   //rech_decho(buf.T,buf.Nb,cle,&pos,&trouv);
                    Inf=0 ;
                    Sup=b;
                    while ((*trouv==0)&&(Inf<=Sup))
                    {
                       *j=(Inf+Sup)/2;
                       if (buf.T[*j]==cle)
                       {
                         *trouv=TRUE;// La clé a été trouvée
                       }
                       else
                       {
                        // Mise à jour des indices pour la recherche decho
                         if (buf.T[*j]>cle)
                         {
                            Sup=*j-1;
                         }
                         else
                         { Inf=*j+1;}
                         }
                       }
                       // Si la clé n'est pas trouvée, mettre à jour l'indice de position
                       if (*trouv==0) *j=Inf;
                       arret=TRUE; // Arrêter la recherche dans les blocs
                     }
                     else if ((buf.T[0]>cle)&&(Vlast<cle)) {*j=0,arret=TRUE;}
                     else { Vlast = buf.T[b];
                           *q=*i;  // Stocker l'indice du bloc courant
                           *i=buf.suiv;  // Passer au bloc suivant
                                         }
                 }
                else {*q=*i;*i=buf.suiv;}// Stocker l'indice du bloc courant et passer au bloc suivant
               }

            }
            if (!arret)
            {
                *i=entete(fichier,3)+1;
            }
          }

    }
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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T_Bloc 300
 typedef struct 
 {
   char ch[1000];
 }buffer;
//ENTETE 
typedef struct {
    int nb_btete;//le numero de premier bloc 
    int nbbloc;
    int nbenreg;
}Entete;
//bloc

typedef struct TBloc{
typedef struct list *TBloc
{
int T[T_Bloc];//tableau d'enregistrement
int Nb;//le nombre d'enregistrement dans le tableau
TBloc * suiv;//le nombre de prochain bloc
}list;
}TBloc;

//declaration de la strecture enregistrement 
typedef struct enreg {
 typedef struct liste *enreg{
 liste  *svt ;
    char nom[10];
    char prenom[10];     }liste;
}enreg;
 //fichier LOF
typedef struct {
Entete entete;
FILE *NIH;
 }LOF;
   
    
int main()
{
    

   NIH = fopen("employer.txt","r+");
   if (NIH== NULL)
   {
       printf("ERREUR !!!!\n");
       return -1;
   }
    printf("Hello world!\n");
    return 0;
}

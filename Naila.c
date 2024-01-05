#include <stdio.h>
#include <stdlib.h>
 typedef struct 
 {
   char ch[1000];
 }buffer,bloc;
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

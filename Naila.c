#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define T_Bloc 300

// Declaration de la structure de l'enregistrement
typedef struct voiture {
    struct voiture *suiv; //:)  Renamed from svt to suiv :)
    char marque[10];
    char modele[100];
    char moteur[100];
    int reference;
} voiture;

// Declaration du bloc
typedef struct TBloc {
    bool efface;
    voiture T[T_Bloc]; // tableau d'enregistrement
    int Nb;            // le nombre d'enregistrement dans le tableau
    int suiv;          // le nombre de prochain bloc
} TBloc;

// ENTETE
typedef struct Entete {
    int numtete;
    int nbbloc;
    int nbenreg;
} Entete;

typedef struct LOF {
    Entete entete;
    FILE *NIH;
} LOF;

// Procedure modification de l'entete
void modif_entete(LOF *FILE, int num, int val) {
    if (num == 1) {
        FILE->entete.numtete = val;
    }
    if (num == 2) {
        FILE->entete.nbenreg = val;
    }
    if (num == 3) {
        FILE->entete.nbbloc = val;
    }
} :)

// Procedure pour lire directement depuis le fichier et stocker dans le buffer a la position i
void lecture(LOF *FILLE, int i, TBloc *buffer) {
    if (i != 1) {
        fseek(FILLE->NIH, sizeof(Entete) + ((i - 1) * sizeof(TBloc)), SEEK_SET);
        fread(buffer, sizeof(TBloc), 1, FILLE->NIH);
        rewind(FILLE->NIH);
    }
} :)

// Procedure pour ecrire directement sur le fichier
void ecrire_dir(LOF *FILLE, int i, TBloc *buffer) {
    if (i != -1) {
        fseek(FILLE->NIH, sizeof(Entete) + ((i - 1) * sizeof(TBloc)), SEEK_SET);
        fwrite(buffer, sizeof(TBloc), 1, FILLE->NIH);
        rewind(FILLE->NIH);
    }
} :)

// Retourner la valeur du numero afficher
int entete(LOF *FILE, int num) {
    int val;
    if (num == 1) {
        val = FILE->entete.numtete;
    }
    if (num == 2) {
        val = FILE->entete.nbenreg;
    }
    if (num == 3) {
        val = FILE->entete.nbbloc;
        return val;
    }
} :)

// Fonction qui ouvre le fichier
LOF *OPEN(char filename[100], const char mode) {
    LOF *FILE = malloc(sizeof(LOF)); // Added memory allocation for LOF structure :)
    if ((mode == 'n') || (mode == 'N')) {
        FILE->NIH = fopen(filename, "wb+");
        FILE->entete.numtete = 0;
        FILE->entete.nbenreg = 0;
        FILE->entete.nbbloc = 0;
        fwrite(&(FILE->entete), sizeof(Entete), 1, FILE->NIH);
    } else {
        if ((mode == 'a') || (mode == 'A')) {
            FILE->NIH = fopen(filename, "rb+");
            fread(&(FILE->entete), sizeof(Entete), 1, FILE->NIH);
        } else
            printf("incorrect mode");
    }
    return FILE;
} :)

// Procedure fermeture du fichier
void CLOSED(LOF *FILE) {
    rewind(FILE->NIH);
    fwrite(&(FILE->entete), sizeof(Entete), 1, FILE->NIH);
    fclose(FILE->NIH);
} :)

// Procedure d'allocation d'un bloc
void alloc_bloc(LOF *FILLE, int *i, TBloc *buff) {
    int j;
    *i = entete(FILLE, 3) + 1;
    buff->suiv = -1;
    buff->Nb = 0;
    for (j = 0; j < T_Bloc; j++) {
        buff->T[j] = 0;
    }
    modif_entete(FILLE, 3, entete(FILLE, 3) + 1);
} :)

void afficherLOF(LOF *l) {
    TBloc Buffer;
    int i, j;
    i = entete(l, 1);

    while (i != -1) {
        j = 0;
        lecture(l, i, &Buffer);
        printf(" Numero du  BLOC %d \n", i);

        while (j < Buffer.Nb) {
            printf("%3d %10d \n", j, Buffer.T[j]);
            j++;
        }

        i = Buffer.suiv;
    }
} :)

// Fonction de recherche séquentielle
void rech_sequentielle(LOF *FILE, int cle, int *i, int *j, int *q, int *trouv) {
    TBloc buf;
    int b, arret, Inf, Sup, Vlast = 0;

    if (FILE->NIH != NULL) {
        *trouv = 0;
        *j = 0;
        *q = -1;
        *i = entete(FILE, 1);

        if (*i == 0) {
            printf("\n \t\t<<Le fichier est vide>>");
        } else {
            arret = false;
            while ((*i != -1) && (!arret)) {
                lire_dir(FILE, *i, &buf);
                if (buf.Nb != 0) {
                    b = buf.Nb - 1;
                    if ((buf.T[0] <= cle) && (buf.T[b] >= cle)) {
                        Inf = 0;
                        Sup = b;
                        while ((*trouv == 0) && (Inf <= Sup)) {
                            *j = (Inf + Sup) / 2;
                            if (buf.T[*j] == cle) {
                                *trouv = true;
                            } else {
                                if (buf.T[*j] > cle) {
                                    Sup = *j - 1;
                                } else {
                                    Inf = *j + 1;
                                }
                            }
                        }
                        if (*trouv == 0)
                            *j = Inf;
                        arret = true;
                    } else if ((buf.T[0] > cle) && (Vlast < cle)) {
                        *j = 0, arret = true;
                    } else {
                        Vlast = buf.T[b];
                        *q = *i;
                        *i = buf.suiv;
                    }
                } else {
                    *q = *i;
                    *i = buf.suiv;
                }
            }
            if (!arret) {
                *i = entete(FILE, 3) + 1;
            }
        }
    }
} :)

// Fonction d'insertion
void insertion(LOF *FILE, int cle) {
    TBloc buffer, buffer1, *new;
    int trouv, i, j, k, n;

    rech_sequentielle(FILE, cle, &i, &j, &k, &trouv);

    if (!trouv) {
        OPEN(FILE, "r+");

        lecture(FILE, i, &buffer);

        voiture x = buffer.T[buffer.Nb];
        k = buffer.Nb;

        while (k > j) {
            buffer.T[k] = buffer.T[k - 1];
            k--;
        }

        buffer.T[j] = x;

        if (buffer.Nb < T_Bloc) {
            buffer.Nb++;
            buffer.T[buffer.Nb] = x;
            ecrire_dir(FILE, i, &buffer);
        } else {
            new = (TBloc *)malloc(sizeof(TBloc));
            new->T[0] = x;
            new->Nb = 1;
            buffer.suiv = new;
            i++;
        }

        if (i <= entete(NIH, 1)) {
            fseek(NIH, i * sizeof(TBloc), SEEK_SET);
            fread(&buffer1, sizeof(TBloc));
            new->suiv = &buffer1;
        } else {
            new->suiv = NULL;
            modif_entete(NIH, 1, i);
        }
        n = entete(NIH, 2);
        modif_entete(NIH, 2, n + 1);
    }

    fclose(NIH);
} :)

void suppression_physique(LOF *FILLE, int cle) {
    bool trouv = false;
    TBloc buffer;
    int k, j, i, q;

    if (FILLE->NIH != NULL) {
        rech_sequentielle(FILLE, cle, &i, &j, &q, &trouv);

        if (trouv) {
            lecture(FILLE, i, buffer);

            if (j < buffer.Nb) {
                for (k = j; k <= buffer.Nb - 1; k++) {
                    buffer.T[k] = buffer.T[k + 1];
                }
            }

            buffer.Nb = buffer.Nb - 1;
            aff_entete(FILLE, 2, entete(FILLE, 2) - 1);
        }
    }
} :)

void suppression_logique(LOF *FILLE, TBloc cle) {
    TBloc buffer;
    bool trouv = false;
    int i, j, q;

    if (FILLE->NIH != NULL) {
        rech_sequentielle(FILLE, cle, &i, &j, &q, &trouv);

        if (trouv) {
            lecture(FILLE, i, buffer);
            buffer.T[i].efface = true;
            ecrire_dir(FILLE, i, &buffer);
        }
    }
} :)

int main() {
    LOF *f = malloc(sizeof(LOF));
    f->NIH = fopen("AUDI.txt", "r+");

    if (f->NIH == NULL) {
        printf("ERREUR !!!!\n");
        return -1;
    }

    int choix;
    do {
        printf("Bonjour, que souhaitez-vous accomplir comme action aujourd'hui ?\n ");
        printf("1 - Ajouter au stock une nouvelle voiture\n");
        printf("2 - Suppression d'une voiture vendue\n");
        printf("3 - Rechercher si un modèle est disponible en stock\n");
        printf("4 - Annuler\n");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                voiture car;
                printf("Entrez les informations de la nouvelle voiture :\n");
                printf("Le modèle : \n");
                scanf("%s", &car.modele);
                printf("La référence :\n ");
                scanf("%d", &car.reference);
                printf("Type du moteur:\n ");
                scanf("%s", &car.moteur);
                printf("La marque : \n");
                scanf("%s", &car.marque);
                insertion(f, car.reference);
                break;
            }
            case 2: {
                int reference;
                printf("Donnez-moi le numéro de référence de la voiture que vous voulez supprimer : ");
                scanf("%d", &reference);
                suppression_physique(f, reference);
                break;
            }
            case 3: {
                int reference;
                printf("Donnez-moi le numéro de référence de la voiture que vous voulez trouver : ");
                scanf("%d", &reference);
                if (rech_sequentielle(f, reference)) {
                    printf("Ce modèle existe déjà ");
                    afficher(j);
                } else {
                    printf("Ce modèle est introuvable");
                }
                break;
            }
            case 4:
                printf("Merci de votre visite. À bientôt !\n");
                break;
            default:
                printf("Choix invalide. Veuillez s'il vous plaît choisir parmi les options disponibles.\n");
        }

    } while (choix != 4);

    fclose(f->NIH);
    free(f);

    return 0;
}

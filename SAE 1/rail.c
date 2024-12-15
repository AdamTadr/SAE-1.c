#include "rail.h"


int depart_valide(dictionnaire* dico, const char* mot, jeu* j) {

    if (strlen(mot) != 4)
        return PAS_JOUABLE;
    if (trouver_mot(dico, mot) == PAS_TROUVER)
        return PAS_JOUABLE;
    int validite = jouable(j, mot);
    return validite;

}


void demander_mot(dictionnaire* dico, jeu* j, char* mot) {
    int valide = PAS_JOUABLE;
    while (valide == PAS_JOUABLE) {
        affichage_jeu(j);
        printf("Entrez un mot : ");
        scanf("%s", mot);
        valide = depart_valide(dico, mot, j);
        if (valide == PAS_JOUABLE) {
            printf("Mot invalide. Reessaye.\n");

        }
    }
}

void placement_de_depart(jeu* j1, jeu* j2, const char* mot1, const char* mot2, rail* r) {

    if (strcmp(mot1, mot2) < 0) {
        for (int i = 0; i < MOT_DEPART - 1; i++) {
            r->recto[i] = jouer_chevalet(j1, mot1[i]);
        }
        int d = MOT_DEPART - 1;
        for (int j = d, i = 0; j < d + MOT_DEPART - 1; j++, i++) {
            r->recto[j] = jouer_chevalet(j2, mot2[i]);
        }
    }
    else {
        for (int i = 0; i < MOT_DEPART - 1; i++) {
            r->recto[i] = jouer_chevalet(j2, mot2[i]);
        }
        int d = MOT_DEPART - 1;
        for (int j = d, i = 0; j < d + MOT_DEPART - 1; j++, i++) {
            r->recto[j] = jouer_chevalet(j1, mot1[i]);
        }
    }
    r->recto[TAILLE_RAIL - 1] = '\0';
    copie_recto_verso(r);
}

void init_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r) {
    char mot1[30], mot2[30];

    demander_mot(dico, j1, mot1);
    demander_mot(dico, j2, mot2);

    placement_de_depart(j1, j2, mot1, mot2, r);
}


void affiche_rail(rail* r) {
    printf("\n");
    for (int i = 0; i < TAILLE_RAIL - 1; i++) {
        printf("%c", r->recto[i]);
    }
    printf("\n");
    for (int i = 0; i < TAILLE_RAIL - 1; i++) {
        printf("%c", r->recto[i]);
    }
    printf("\n");

}

void copie_recto_verso(rail* r) {
    for (int i = 0; r->recto[i] != '\0'; i++)
        r->recto[i] = r->verso[TAILLE_RAIL - 2 - i];
    r->verso[TAILLE_RAIL - 1] = '\0';
}

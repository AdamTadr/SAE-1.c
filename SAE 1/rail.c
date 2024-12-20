#include "rail.h"


int depart_valide(dictionnaire* dico, const char* mot, jeu* j) {

    if (strlen(mot) != 4)
        return PAS_JOUABLE;
    /*if (trouver_mot(dico, mot) == PAS_TROUVER)
        return PAS_JOUABLE;*/
    int validite = jouable(j, mot);
    return validite;

}


void demander_mot_depart(dictionnaire* dico, jeu* j, char* mot, int nbj) {
    char mot_test[MOT_TEST_MAX];
    int valide = PAS_JOUABLE;
    while (valide == PAS_JOUABLE) {
        printf("%d> ", nbj);
        scanf("%s", mot_test);
        valide = depart_valide(dico, mot_test, j);
        if (valide == PAS_JOUABLE) {
            continue;
        }
        else {
            strcpy(mot, mot_test);
        }
    }
}

int placement_de_depart(jeu* j1, jeu* j2, const char* mot1, const char* mot2, rail* r) {

    if (strcmp(mot1, mot2) < 0) {
        for (int i = 0; i < MOT_DEPART - 1; i++) {
            r->recto[i] = jouer_chevalet(j1, mot1[i]);
        }
        int d = MOT_DEPART - 1;
        for (int j = d, i = 0; j < d + MOT_DEPART - 1; j++, i++) {
            r->recto[j] = jouer_chevalet(j2, mot2[i]);
        }
        r->recto[TAILLE_RAIL - 1] = '\0';
        copie_recto_verso(r);
        return 1;
    }
    else {
        for (int i = 0; i < MOT_DEPART - 1; i++) {
            r->recto[i] = jouer_chevalet(j2, mot2[i]);
        }
        int d = MOT_DEPART - 1;
        for (int j = d, i = 0; j < d + MOT_DEPART - 1; j++, i++) {
            r->recto[j] = jouer_chevalet(j1, mot1[i]);
        }
        r->recto[TAILLE_RAIL - 1] = '\0';
        copie_recto_verso(r);
        return 2;
    }
}

int init_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r) {
    char mot1[TAILLE_MOT_MAX], mot2[TAILLE_MOT_MAX];

    demander_mot_depart(dico, j1, mot1, 1);
    demander_mot_depart(dico, j2, mot2, 2);

    int joueur_depart = placement_de_depart(j1, j2, mot1, mot2, r);
    return joueur_depart;
}


void affiche_rail(const rail* r) {
    printf("R : ");
    for (int i = 0; i < TAILLE_RAIL - 1; i++) {
        printf("%c", r->recto[i]);
    }
    printf("\n");
    printf("V : ");
    for (int i = 0; i < TAILLE_RAIL - 1; i++) {
        printf("%c", r->verso[i]);
    }
    printf("\n");

}

void copie_recto_verso(rail* r) {
    for (int i = 0; r->recto[i] != '\0'; i++)
        r->verso[i] = r->recto[TAILLE_RAIL - 2 - i];
    r->verso[TAILLE_RAIL - 1] = '\0';
}

void copie_verso_recto(rail* r) {
    for (int i = 0; r->verso[i] != '\0'; i++)
        r->recto[i] = r->verso[TAILLE_RAIL - 2 - i];
    r->recto[TAILLE_RAIL - 1] = '\0';
}

void copie_arecto_averso(rail* r) {
    for (int i = 0; r->ancien_recto[i] != '\0'; i++)
        r->ancien_verso[i] = r->ancien_recto[TAILLE_RAIL - 2 - i];
    r->ancien_verso[TAILLE_RAIL - 1] = '\0';
}

void copie_averso_arecto(rail* r) {
    for (int i = 0; r->ancien_verso[i] != '\0'; i++)
        r->ancien_recto[i] = r->verso[TAILLE_RAIL - 2 - i];
    r->ancien_recto[TAILLE_RAIL - 1] = '\0';
}

void save_rail(rail* r, char cote) {
    if (cote == 'R') {
        for (int i = 0; i < TAILLE_RAIL - 1; i++) {
            r->ancien_recto[i] = r->recto[i];
        }
        copie_arecto_averso(r);
    }
    if (cote == 'V') {
        for (int i = 0; i < TAILLE_RAIL - 1; i++) {
            r->ancien_recto[i] = r->recto[i];
        }
        copie_averso_arecto(r);
    }
}
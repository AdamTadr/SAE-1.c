#include "rail.h"


int depart_valide(dictionnaire* dico, const char* mot, jeu* j) {

    if (strlen(mot) != TAILLE_MOT_MIN-1)
        return PAS_JOUABLE;
    int indice_mot = 1;//trouver_mot(dico, mot);
    if (indice_mot == PAS_TROUVER) return PAS_JOUABLE;
    int validite = jouable(j, mot);
	if (validite == PAS_JOUABLE) 
        return PAS_JOUABLE;
	rendre_mot_injouable(dico, indice_mot);
    return validite;

}


void demander_mot_depart(dictionnaire* dico, jeu* j, char* mot, int nbj) {
    char mot_test[MOT_TEST_MAX];
    int valide = PAS_JOUABLE;
    while (valide == PAS_JOUABLE) {
        printf("%d> ", nbj);
		fgets(mot_test, MOT_TEST_MAX, stdin);
		sscanf(mot_test, "%s", mot_test);
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
            ajouter_rail_recto(r, i, jouer_chevalet(j1, mot1[i]));
        }
        int d = MOT_DEPART - 1;
        for (int j = d, i = 0; j < d + MOT_DEPART - 1; j++, i++) {
            ajouter_rail_recto(r, j, jouer_chevalet(j2, mot2[i]));

        }
        ajouter_rail_recto(r, TAILLE_RAIL - 1, '\0');
        copie_recto_verso(r);
        save_rail(r);
        return JOUEUR_1;
    }
    else {
        for (int i = 0; i < MOT_DEPART - 1; i++) {
            ajouter_rail_recto(r, i, jouer_chevalet(j2, mot2[i]));
        }
        int d = MOT_DEPART - 1;
        for (int j = d, i = 0; j < d + MOT_DEPART - 1; j++, i++) {
            ajouter_rail_recto(r, j, jouer_chevalet(j1, mot1[i]));
        }
        copie_recto_verso(r);
        save_rail(r);
        return JOUEUR_2;
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
        printf("%c", valeur_rail_recto(r,i));
    }
    printf("\n");
    printf("V : ");
    for (int i = 0; i < TAILLE_RAIL - 1; i++) {
        printf("%c", valeur_rail_verso(r, i));
    }
    printf("\n\n");
}

void copie_recto_verso(rail* r) {
    for (int i = 0; i < TAILLE_RAIL - 1; i++)
        ajouter_rail_verso(r, i, valeur_rail_recto(r, TAILLE_RAIL - 2 - i));
    ajouter_rail_verso(r, TAILLE_RAIL - 1, '\0');
}

void copie_verso_recto(rail* r) {
    for (int i = 0; i < TAILLE_RAIL - 1; i++)
        ajouter_rail_recto(r, i, valeur_rail_verso(r, TAILLE_RAIL - 2 - i));
    ajouter_rail_recto(r, TAILLE_RAIL - 1, '\0');
}

void copie_arecto_averso(rail* r) {
    for (int i = 0; i < TAILLE_RAIL - 1; i++)
        ajouter_rail_averso(r, i, valeur_rail_arecto(r, TAILLE_RAIL - 2 - i));
    ajouter_rail_averso(r, TAILLE_RAIL - 1, '\0');
}

void copie_averso_arecto(rail* r) {
    for (int i = 0; i < TAILLE_RAIL - 1; i++)
        ajouter_rail_arecto(r, i, valeur_rail_averso(r, TAILLE_RAIL - 2 - i));
    ajouter_rail_arecto(r, TAILLE_RAIL - 1, '\0');
}

void save_rail(rail* r) {
    for (int i = 0; i < TAILLE_RAIL - 1; i++) {
        ajouter_rail_arecto(r, i, valeur_rail_recto(r, i));
    }
    ajouter_rail_arecto(r, TAILLE_RAIL - 1, '\0');
    copie_arecto_averso(r);
}

void init_rail(rail* r) {
    modif_t_drn_mot_joue(r, VIDE);
}

void ajouter_rail_recto(rail* r, int indice, char che) {
    assert(indice >= 0 && indice < TAILLE_RAIL);
    r->recto[indice] = che;
}

void ajouter_rail_verso(rail* r, int indice, char che) {
    assert(indice >= 0 && indice < TAILLE_RAIL);
    r->verso[indice] = che;
}

void ajouter_rail_arecto(rail* r, int indice, char che) {
    assert(indice >= 0 && indice < TAILLE_RAIL);
    r->ancien_recto[indice] = che;
}

void ajouter_rail_averso(rail* r, int indice, char che) {
    assert(indice >= 0 && indice < TAILLE_RAIL);
    r->ancien_verso[indice] = che;
}

char valeur_rail_recto(const rail* r, int indice) {
    assert(indice >= 0 && indice < TAILLE_RAIL);
    return r->recto[indice];
}

char valeur_rail_verso(const rail* r, int indice) {
    assert(indice >= 0 && indice < TAILLE_RAIL);
    return r->verso[indice];
}

char valeur_rail_arecto(const rail* r, int indice) {
    assert(indice >= 0 && indice < TAILLE_RAIL);
    return r->ancien_recto[indice];
}

char valeur_rail_averso(const rail* r, int indice) {
    assert(indice >= 0 && indice < TAILLE_RAIL);
    return r->ancien_verso[indice];
}

int valeur_t_drn_mot_joue(const rail* r) {
    return r->t_drn_mot_joue;
}

void modif_t_drn_mot_joue(rail* r, int n ) {
    r->t_drn_mot_joue = n;
}
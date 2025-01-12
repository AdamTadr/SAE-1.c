#include "rail.h"


int depart_valide(dictionnaire* dico, const char* mot, jeu* j) {
    assert(dico != NULL && mot != NULL && j != NULL);

    if (strlen(mot) != TAILLE_MOT_MIN-1)
        return PAS_JOUABLE;
    int indice_mot = trouver_mot(dico, mot);
    if (indice_mot == PAS_TROUVER) return PAS_JOUABLE;
    int validite = jouable(j, mot);
	if (validite == PAS_JOUABLE) 
        return PAS_JOUABLE;
	rendre_mot_injouable(dico, indice_mot);
    return validite;

}


void demander_mot_depart(dictionnaire* dico, jeu* j, char* mot, int nbj) {
    assert(dico != NULL && j != NULL && mot != NULL);

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
    assert(j1 != NULL && j2 != NULL && mot1 != 2 && mot2 != NULL && r != NULL);

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
    assert(dico != NULL && p != NULL && j1 != NULL && j2 != NULL && r != NULL);
    char mot1[TAILLE_MOT_MAX], mot2[TAILLE_MOT_MAX];

    demander_mot_depart(dico, j1, mot1, 1);
    demander_mot_depart(dico, j2, mot2, 2);

    int joueur_depart = placement_de_depart(j1, j2, mot1, mot2, r);
    return joueur_depart;
}


void affiche_rail(const rail* r) {
    assert(r != NULL);
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
    assert(r != NULL);
    for (int i = 0; i < TAILLE_RAIL - 1; i++)
        ajouter_rail_verso(r, i, valeur_rail_recto(r, TAILLE_RAIL - 2 - i));
    ajouter_rail_verso(r, TAILLE_RAIL - 1, '\0');
}

void copie_verso_recto(rail* r) {
    assert(r != NULL);
    for (int i = 0; i < TAILLE_RAIL - 1; i++)
        ajouter_rail_recto(r, i, valeur_rail_verso(r, TAILLE_RAIL - 2 - i));
    ajouter_rail_recto(r, TAILLE_RAIL - 1, '\0');
}

void copie_arecto_averso(rail* r) {
    assert(r != NULL);
    for (int i = 0; i < TAILLE_RAIL - 1; i++)
        ajouter_rail_averso(r, i, valeur_rail_arecto(r, TAILLE_RAIL - 2 - i));
    ajouter_rail_averso(r, TAILLE_RAIL - 1, '\0');
}

void copie_averso_arecto(rail* r) {
    assert(r != NULL);
    for (int i = 0; i < TAILLE_RAIL - 1; i++)
        ajouter_rail_arecto(r, i, valeur_rail_averso(r, TAILLE_RAIL - 2 - i));
    ajouter_rail_arecto(r, TAILLE_RAIL - 1, '\0');
}

void save_rail(rail* r) {
    assert(r != NULL);
    for (int i = 0; i < TAILLE_RAIL - 1; i++) {
        ajouter_rail_arecto(r, i, valeur_rail_recto(r, i));
    }
    ajouter_rail_arecto(r, TAILLE_RAIL - 1, '\0');
    copie_arecto_averso(r);
}

void init_rail(rail* r) {
    assert(r != NULL);
    modif_t_drn_mot_joue(r, VIDE);
}

char sortir_chevalet_droite(rail* r, char cote, int taille_mot) {
    assert(r != NULL && taille_mot >= 0);
    char temp = 'n';

    if (cote == 'R') {
        temp = selec_rail_recto(r, TAILLE_RAIL - 2);
        for (int i = TAILLE_RAIL - 2; i >= RANG_PREM_L; i--) {
            mod_r_recto(r, i + 1, selec_rail_recto(r, i));
        }
        mod_r_recto(r, TAILLE_RAIL - 1, '\0');
    }
    else if (cote == 'V') {
        temp = selec_rail_verso(r, TAILLE_RAIL - 2);
        for (int i = TAILLE_RAIL - 2; i >= RANG_PREM_L; i--) {
            mod_r_verso(r, i + 1, selec_rail_verso(r, i));
        }
        mod_r_recto(r, TAILLE_RAIL - 1, '\0');
    }

    return temp;
}



char sortir_chevalet_gauche(rail* r, char cote, int taille_mot) {
    assert(r != NULL && taille_mot >= 0);
    char temp = 'n';

    if (cote == 'R') {
        temp = selec_rail_recto(r, RANG_PREM_L);
        for (int i = 0; i < TAILLE_RAIL - 1; i++) {
            mod_r_recto(r, i, selec_rail_recto(r, i + 1));
        }
    }
    else if (cote == 'V') {
        temp = selec_rail_verso(r, RANG_PREM_L);
        for (int i = 0; i < TAILLE_RAIL - 1; i++) {
            mod_r_verso(r, i, selec_rail_verso(r, i + 1));
        }
    }
    return temp;

}


void inserer_chevalet_droite(rail* r, char che, char cote) {
    assert(r != NULL);
    if (cote == 'R') {
        mod_r_recto(r, TAILLE_RAIL - 2, che);
        copie_recto_verso(r);
    }
    if (cote == 'V') {
        mod_r_verso(r, TAILLE_RAIL - 2, che);
        copie_verso_recto(r);
    }
}

void inserer_chevalet_gauche(rail* r, char che, char cote) {
    assert(r != NULL);
    if (cote == 'R') {
        mod_r_recto(r, PREMIERE_LETTRE, che);
        copie_recto_verso(r);
    }
    if (cote == 'V') {
        mod_r_verso(r, PREMIERE_LETTRE, che);
        copie_verso_recto(r);
    }
}




void ajouter_rail_recto(rail* r, int indice, char che) {
    assert(indice >= 0 && indice < TAILLE_RAIL && r != NULL);
    r->recto[indice] = che;
}

void ajouter_rail_verso(rail* r, int indice, char che) {
    assert(indice >= 0 && indice < TAILLE_RAIL && r != NULL);
    r->verso[indice] = che;
}

void ajouter_rail_arecto(rail* r, int indice, char che) {
    assert(indice >= 0 && indice < TAILLE_RAIL && r != NULL);
    r->ancien_recto[indice] = che;
}

void ajouter_rail_averso(rail* r, int indice, char che) {
    assert(indice >= 0 && indice < TAILLE_RAIL && r !=NULL);
    r->ancien_verso[indice] = che;
}

char valeur_rail_recto(const rail* r, int indice) {
    assert(indice >= 0 && indice < TAILLE_RAIL && r != NULL);
    return r->recto[indice];
}

char valeur_rail_verso(const rail* r, int indice) {
    assert(indice >= 0 && indice < TAILLE_RAIL && r !=NULL);
    return r->verso[indice];
}

char valeur_rail_arecto(const rail* r, int indice) {
    assert(indice >= 0 && indice < TAILLE_RAIL && r != NULL);
    return r->ancien_recto[indice];
}

char valeur_rail_averso(const rail* r, int indice) {
    assert(indice >= 0 && indice < TAILLE_RAIL && r!=NULL);
    return r->ancien_verso[indice];
}

int valeur_t_drn_mot_joue(const rail* r) {
    assert(r != NULL);
    return r->t_drn_mot_joue;
}

void modif_t_drn_mot_joue(rail* r, int n ) {
    assert(r != NULL);
    r->t_drn_mot_joue = n;
}

void changer_t_dnr_mot_joue(rail* r, int n) {
    assert(r != NULL);
    r->t_drn_mot_joue = n;
}
int t_drn_mot_joue(rail* r) {
    assert(r != NULL);
    return r->t_drn_mot_joue;
}

void mod_r_recto(rail* r, int indice, char che) {
    assert(r != NULL && indice >= 0);
    r->recto[indice] = che;
}

void mod_r_verso(rail* r, int indice, char che) {
    assert(r != NULL && indice >= 0);
    r->verso[indice] = che;
}

char selec_rail_recto(rail* r, int indice) {
    assert(r != NULL && indice >= 0);
    return r->recto[indice];
}

char selec_rail_verso(rail* r, int indice) {
    assert(r != NULL && indice >= 0);
    return r->verso[indice];
}


char* rail_recto(rail* r) {
    assert(r != NULL);
    return r->recto;
}

char* rail_arecto(rail* r) {
    assert(r != NULL);
    return r->ancien_recto;
}

char* rail_verso(rail* r) {
    assert(r != NULL);
    return r->verso;
}

char* rail_averso(rail* r) {
    assert(r != NULL);
    return r->ancien_verso;
}
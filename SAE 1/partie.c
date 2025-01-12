#include "partie.h"


int jouer_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r, statut_partie joueur_actuel) {
    assert(dico != NULL && p != NULL && j1 != NULL && j2 != NULL && r != NULL);
    assert(!dico_vide(dico));
    assert(!pioche_vide(p));
    assert(taille_jeu_actuel(j1) != VIDE);
    assert(taille_jeu_actuel(j2) != VIDE);
    
    while (joueur_actuel != FINI) {
        printf("\n");
		affichage_tour(j1, j2, r);

        if (joueur_actuel == TOUR_J2) {
            char mot[TAILLE_MOT_MAX];
            joueur_actuel = demander_mot(dico,p, j2, j1, mot, joueur_actuel, r, joueur_actuel);

        }
        else if (joueur_actuel == TOUR_J1) {
            char mot[TAILLE_MOT_MAX];
            joueur_actuel = demander_mot(dico,p, j1, j2, mot, joueur_actuel, r, joueur_actuel);
        }
    }
        return FINI;
}

void affichage_tour(jeu* j1, jeu* j2, rail* r) {
    assert(j1 != NULL && j2 != NULL && r != NULL);
    affichage_jeu(j1, JOUEUR_1);
    affichage_jeu(j2, JOUEUR_2);
    affiche_rail(r);
}

statut_partie demander_mot(dictionnaire* dico,pioche* p, jeu* j, jeu* j_autre, char* mot, int nbj, rail* r, statut_partie joueur_actuel) {
    assert(dico != NULL && p != NULL && j != NULL && j_autre != NULL && mot != NULL && r != NULL);
    assert(taille_jeu_actuel(j)!=VIDE);
    assert(taille_jeu_actuel(j_autre) != VIDE);
    assert(!dico_vide(dico));

    int valide = PAS_JOUABLE;
    char interprete = 'n', test[MOT_TEST_MAX];

    while (valide == PAS_JOUABLE) {
        printf("%d> ", nbj);

		fgets(test, MOT_TEST_MAX, stdin);
        if (test[1] != ' ' || test[0]==' ') {
            continue;
        }
		sscanf(test,"%c %s", &interprete, test);
        if (strlen(test) > TAILLE_MOT_MAX - 1 || strlen(test)<TAILLE_LETTRE) 
            continue;

        strcpy(mot, test);

        if (interprete != 'R' && interprete != 'V' && interprete != 'r' && interprete != 'v' && interprete != '-')
            continue;

        if (interprete == '-') {
            if (strlen(mot) > 1) {
                return joueur_actuel;
            }
                valide = echanger_chevalet(p, j, mot[0]);
                if (valide == PAS_JOUABLE)
                    continue;
                changer_t_dnr_mot_joue(r, UN_MOT);
                if (joueur_actuel == TOUR_J2)
                    joueur_actuel = TOUR_J1;
                else if (joueur_actuel == TOUR_J1)
                    joueur_actuel = TOUR_J2;

				return joueur_actuel;
        }

        if (interprete == 'R' || interprete == 'V' || interprete == 'r' || interprete == 'v') {
            valide = tentative(j, j_autre, r, dico, mot, interprete, joueur_actuel);

            if (valide == PAS_JOUABLE)
                continue;

            if (valide == FINI)
                return FINI;

            if (interprete == 'V' || interprete == 'R') {
                if (valide != PAS_JOUABLE) {
                    if (joueur_actuel == TOUR_J2)
                        joueur_actuel = TOUR_J1;
                    else if (joueur_actuel == TOUR_J1)
                        joueur_actuel = TOUR_J2;
                }
            }
            return joueur_actuel;
        }
    }
}



void jouer_mot(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico, char* mot, char* lettre_parenthese,char* lettre_hors_p, char cote, statut_partie joueur_actuel) {
    assert(j != NULL && j_autre != NULL & dico != NULL && mot != NULL && lettre_parenthese != NULL && lettre_hors_p != NULL);
    int taille_mot = strlen(mot);
    int taille_mot_parenth = strlen(lettre_parenthese);
    int taille_mot_remplace = strlen(lettre_hors_p);

    save_rail(r);
    save_jeu(j);

    if (mot[0] == '(') {
        for (int i = 0; i < taille_mot_remplace; i++) {

            char chevalet = sortir_chevalet_gauche(r, cote, taille_mot);
            inserer_chevalet_droite(r, lettre_hors_p[i], cote);

            if (joueur_actuel == TOUR_J1) {
                recevoir_chevalet(j_autre, chevalet);
                jouer_chevalet(j, lettre_hors_p[i]);
            }
            else if (joueur_actuel == TOUR_J2) {
                recevoir_chevalet(j_autre, chevalet);
                jouer_chevalet(j, lettre_hors_p[i]);
            }
        }



    }
    else if (mot[taille_mot - 1] == ')' ) {

        for (int i = 0; i < taille_mot_remplace; i++) {

            char chevalet = sortir_chevalet_droite(r, cote, taille_mot);
            inserer_chevalet_gauche(r, lettre_hors_p[taille_mot_remplace - i - 1], cote);

            if (joueur_actuel == TOUR_J1) {
                recevoir_chevalet(j_autre, chevalet);
                jouer_chevalet(j, lettre_hors_p[taille_mot_remplace - i - 1]);
            }
            else if (joueur_actuel == TOUR_J2) {
                recevoir_chevalet(j_autre, chevalet);
                jouer_chevalet(j, lettre_hors_p[taille_mot_remplace - i - 1]);
            }
        }
    }

}







int verif_format_mot(char* mot, int* indice_ouv, int* indice_ferm ) {
    assert(mot != NULL && indice_ouv != NULL && indice_ferm != NULL);

    int parenthese_ouv = 0, parenthese_ferm = 0;

    int taille_mot = strlen(mot);

	if (taille_mot > TAILLE_MOT_MAX || taille_mot < TAILLE_MOT_MIN)
		return PAS_JOUABLE;

    for (int i = 0; i < taille_mot; i++) {
        if (mot[i] == '(') {
            ++parenthese_ouv;
            *indice_ouv = i;
        }
        if (mot[i] == ')') {
            ++parenthese_ferm;
            *indice_ferm = i;
        }
    }

    if (parenthese_ouv != 1 || parenthese_ferm != 1)
        return PAS_JOUABLE;

    if (*indice_ferm - *indice_ouv - 1 > L_MAX_PARENTH || *indice_ferm - *indice_ouv - 1 == PAS_ASSEZ_ENTRE)
        return PAS_JOUABLE;
    return JOUABLE;
}



int tentative(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico, char* mot, char cote, statut_partie joueur_actuel) {
    assert(j != NULL && j_autre != NULL && dico != NULL && r != NULL && mot != NULL);

    int taille_mot = strlen(mot);
    char mot_forme[TAILLE_MOT_MAX];
    char mot_sans_parenthese[TAILLE_MOT_SANS_P], lettre_parenthese[L_MAX_PARENTH + 1], lettres_hors_parenthese[L_MAX_H_PARENTH + 1];

    if (cote == 'r' || cote == 'v') {
		if (t_drn_mot_joue(r) == TAILLE_RAIL - 1 || t_drn_mot_joue(r) < TAILLE_MOT_MIN_SANS_P) {
			return PAS_JOUABLE;
		}
        else {
            int i = PAS_JOUABLE;
            printf("\n");
            while (i == PAS_JOUABLE) {
                i = octo_chevalet(j, j_autre, r, joueur_actuel);
            }

            changer_t_dnr_mot_joue(r, PAS_JOUABLE);
        }
    }

	if (init_mot(mot, &mot_sans_parenthese, &lettres_hors_parenthese, &lettre_parenthese, cote, j,r) == PAS_JOUABLE) {
		return PAS_JOUABLE;
	}
    int indice_mot = trouver_mot(dico, &mot_sans_parenthese);
    if (indice_mot == PAS_TROUVER)
        return PAS_JOUABLE;

    if (cote == 'R' || cote == 'V') {
        jouer_mot(j, j_autre, r, dico, mot, &lettre_parenthese, &lettres_hors_parenthese, cote, joueur_actuel);
        changer_t_dnr_mot_joue(r, strlen(mot_sans_parenthese));

        if (taille_jeu_actuel(j) == 0) {
            return FINI;
        }

        if (strlen(&mot_sans_parenthese) == TAILLE_MOT_SANS_P - 1) {

			int i = PAS_JOUABLE;
            printf("\n");
            if(joueur_actuel==TOUR_J1)
                affichage_tour(j, j_autre, r);
            if(joueur_actuel==TOUR_J2)
                affichage_tour(j_autre, j, r);
            while (i == PAS_JOUABLE) {
                if (joueur_actuel == TOUR_J1) {
                    i = octo_chevalet(j, j_autre, r, joueur_actuel);
                }
                else {
                    i = octo_chevalet(j, j_autre, r, joueur_actuel);
                }
            }
        }
    }


    rendre_mot_injouable(dico, indice_mot); 
    return JOUE;

}



int init_mot(char* mot, char* mot_sans_parenthese, char* lettres_hors_parenthese, char* lettre_parenthese, char cote, jeu* j,rail* r) {
    assert(mot != NULL && mot_sans_parenthese != NULL && lettre_parenthese != NULL && j != NULL && r != NULL);

    int indice_ferm, indice_ouv;

    if (verif_format_mot(mot, &indice_ouv, &indice_ferm) == PAS_JOUABLE) {
        return PAS_JOUABLE;
    }
    if (lettre_joue_valide(r,j, mot, lettres_hors_parenthese,lettre_parenthese, cote, indice_ouv, indice_ferm) == PAS_JOUABLE
        || lettre_rail_valide(r, mot, lettres_hors_parenthese,lettre_parenthese, cote,j, indice_ouv, indice_ferm) == PAS_JOUABLE) {
        return PAS_JOUABLE;
    }
    supprime_parenthese(mot, lettre_parenthese, lettres_hors_parenthese, mot_sans_parenthese);
    return JOUABLE;
}


void supprime_parenthese(char* mot, char* lettre_parenthese, char* lettre_hors_parenthese, char* mot_sans_parenthese) {
    assert(mot != NULL && lettre_parenthese != NULL && lettre_hors_parenthese != NULL && mot_sans_parenthese != NULL);

    int taille_mot = strlen(mot);

    if (mot[0] == '(') {
        strcpy(mot_sans_parenthese, lettre_parenthese);
        int debut = strlen(mot_sans_parenthese);
        for (int i = debut, d = 0; i < TAILLE_MOT_SANS_P - 1; i++, d++) {
            mot_sans_parenthese[i] = lettre_hors_parenthese[d];
        }
        mot_sans_parenthese[TAILLE_MOT_SANS_P - 1] = '\0';
    }

    if (mot[taille_mot - 1] == ')') {
        strcpy(mot_sans_parenthese, lettre_hors_parenthese);
        int debut = strlen(mot_sans_parenthese);
        for (int i = debut, d = 0; i < TAILLE_MOT_SANS_P - 1; i++, d++) {
            mot_sans_parenthese[i] = lettre_parenthese[d];
        }
        mot_sans_parenthese[TAILLE_MOT_SANS_P - 1] = '\0';
    }
}


int lettre_joue_valide(rail* r, jeu* j, char* mot, char* lettres_hors_parenthese, char* lettres_parenthese, char cote, int indice_ouv, int indice_ferm) {
    assert(r != NULL && j != NULL && mot != NULL && lettres_hors_parenthese != NULL && lettres_parenthese != NULL);
    assert(indice_ouv >= 0 && indice_ouv < TAILLE_MOT_MAX && indice_ferm >= 0 && indice_ferm < TAILLE_MOT_MAX);

    int d = 0, taille_mot = strlen(mot);

    if (mot[0] == '(') {
        for (int i = indice_ferm + 1; i < taille_mot; i++) {
            lettres_hors_parenthese[d++] = mot[i];
        }
    }
    else if (mot[taille_mot - 1 ] == ')') {
        for (int i = 0; i < indice_ouv; i++){
            lettres_hors_parenthese[d++] = mot[i];
        }
                
    }

    lettres_hors_parenthese[d] = '\0';

    if (strlen(lettres_hors_parenthese) == 0)
        return PAS_JOUABLE;


    if (cote == 'V' || cote == 'R')
        if (jouable(j, lettres_hors_parenthese) == PAS_JOUABLE) // a modif
            return PAS_JOUABLE;
    else if (cote == 'v' || cote == 'r')
        if (precedent_jouable(j, lettres_hors_parenthese) == PAS_JOUABLE) // a modif
                return PAS_JOUABLE;
    else
        return PAS_JOUABLE;

    return JOUABLE;

}



int verif_debut(char* mot,rail* r, char* lettres_parenthese, int indice_ferm, int indice_ouv, int taille_mot, char cote) {
    assert(mot != NULL && r != NULL && lettres_parenthese != NULL);
    assert(taille_mot <= TAILLE_MOT_MAX && taille_mot >= 0);
    assert(indice_ouv >= 0 && indice_ouv < TAILLE_MOT_MAX && indice_ferm >= 0 && indice_ferm < TAILLE_MOT_MAX);

    if (cote == 'R') {
        return verif_Recto_debut(mot, rail_recto(r), lettres_parenthese, indice_ferm, indice_ouv, taille_mot);
    }
    else if (cote == 'V') {
        return verif_Verso_debut(mot, rail_verso(r), lettres_parenthese, indice_ferm, indice_ouv, taille_mot);
    }
    if (cote == 'r') {
        return verif_Recto_debut(mot, rail_arecto(r), lettres_parenthese, indice_ferm, indice_ouv, taille_mot);
    }
    else if (cote == 'v') {
        return verif_Verso_debut(mot, rail_averso(r), lettres_parenthese, indice_ferm, indice_ouv, taille_mot);
	}
    return PAS_JOUABLE;
}
int verif_fin(char* mot, rail* r, char* lettres_parenthese, int indice_ouv,int indice_ferm, int taille_mot, char cote) {
    assert(mot != NULL && r != NULL && lettres_parenthese != NULL);
    assert(taille_mot <= TAILLE_MOT_MAX && taille_mot >= 0);
    assert(indice_ouv >= 0 && indice_ouv < TAILLE_MOT_MAX && indice_ferm >= 0 && indice_ferm < TAILLE_MOT_MAX);

    if (cote == 'R') {
        return verif_Recto_fin(mot, rail_recto(r), lettres_parenthese, indice_ouv, indice_ferm, taille_mot);
    }
    else if (cote == 'V') {
        return verif_Verso_fin(mot, rail_verso(r), lettres_parenthese, indice_ouv, indice_ferm, taille_mot);
    }

    if (cote == 'r') {
        return verif_Recto_fin(mot, rail_arecto(r), lettres_parenthese, indice_ouv, indice_ferm, taille_mot);
    }
    else if (cote == 'v') {
        return verif_Verso_fin(mot, rail_averso(r), lettres_parenthese, indice_ouv, indice_ferm, taille_mot);
    }
    return PAS_JOUABLE;
}




int verif_Recto_debut(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ferm, int indice_ouv, int taille_mot) {
    assert(mot != NULL && rail_verso != NULL && lettres_parenthese != NULL);
    assert(indice_ouv >= 0 && indice_ouv < TAILLE_MOT_MAX && indice_ferm >= 0 && indice_ferm < TAILLE_MOT_MAX);
    int d = 0;
    for (int i = indice_ouv+1; i < indice_ferm && d < L_MAX_H_PARENTH - 1; i++) {
        if (mot[i] == rail_recto[d]){
            lettres_parenthese[d++] = mot[i];
        }
        else
            return PAS_JOUABLE;
    }
    lettres_parenthese[d] = '\0';
    if (strlen(lettres_parenthese) < 1) {
        return PAS_JOUABLE;
    }

    return JOUABLE;
}
int verif_Recto_fin(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ouv, int indice_ferm, int taille_mot) {
    assert(mot != NULL && rail_verso != NULL && lettres_parenthese != NULL);
    assert(indice_ouv >= 0 && indice_ouv < TAILLE_MOT_MAX && indice_ferm >= 0 && indice_ferm < TAILLE_MOT_MAX);

    int d = indice_ferm - 1, j = 0;
    for (int i = TAILLE_RAIL - 2; d > indice_ouv ; i--, d--, j++) {
        if (mot[d] == rail_recto[i]) {
            lettres_parenthese[j] = mot[j+1];
        }
        else
            return PAS_JOUABLE;
    }
    lettres_parenthese[j] = '\0';
    if (strlen(lettres_parenthese) < 1) {
        return PAS_JOUABLE;
    }
    return JOUABLE;
}

int verif_Verso_debut(char* mot, char* rail_verso, char* lettres_parenthese, int indice_ferm,int indice_ouv, int taille_mot) {
    assert(mot != NULL && rail_verso != NULL && lettres_parenthese != NULL);
    assert(indice_ouv >= 0 && indice_ouv < TAILLE_MOT_MAX && indice_ferm >= 0 && indice_ferm < TAILLE_MOT_MAX);
    int d = 0;
    for (int i = indice_ouv+1; i < indice_ferm && d < L_MAX_H_PARENTH - 1; i++) {
        if (mot[i] == rail_verso[d])
            lettres_parenthese[d++] = mot[i];
        else
            return PAS_JOUABLE;
    }
    lettres_parenthese[d] = '\0';
    if (strlen(lettres_parenthese) < 1) {
        return PAS_JOUABLE;
    }

    return JOUABLE;
}

int verif_Verso_fin(char* mot, char* rail_verso, char* lettres_parenthese, int indice_ouv, int indice_ferm, int taille_mot) {
    assert(mot != NULL && rail_verso != NULL && lettres_parenthese != NULL);
    assert(indice_ouv >= 0 && indice_ouv < TAILLE_MOT_MAX && indice_ferm >= 0 && indice_ferm < TAILLE_MOT_MAX);
    int d = indice_ferm - 1, j = 0;
    for (int i = TAILLE_RAIL - 2; d > indice_ouv; i--, d--, j++) {
        if (mot[d] == rail_verso[i]) {
            lettres_parenthese[j] = mot[j+1];
        }
        else
            return PAS_JOUABLE;
    }
    lettres_parenthese[j] = '\0';
    if (strlen(lettres_parenthese) < 1) {
        return PAS_JOUABLE;
    }
    return JOUABLE;
}




int lettre_rail_valide(rail* r, char* mot, char* lettres_hors_parenthese, char* lettres_parenthese,char cote, jeu* j, int indice_ouv, int indice_ferm) {
    assert(r != NULL && mot != NULL && lettres_hors_parenthese != NULL && lettres_parenthese != NULL && j != NULL);
    assert(indice_ouv >= 0 && indice_ouv < TAILLE_MOT_MAX && indice_ferm >= 0 && indice_ferm < TAILLE_MOT_MAX);
    int taille_mot = strlen(mot);
    if (mot[0] == '(') {
        if (verif_fin(mot, r, lettres_parenthese, indice_ouv, indice_ferm, taille_mot, cote) == PAS_JOUABLE)
            return PAS_JOUABLE;
    }
    else if (mot[taille_mot - 1] == ')') {
        if (verif_debut(mot, r, lettres_parenthese, indice_ferm,indice_ouv, taille_mot, cote) == PAS_JOUABLE)
            return PAS_JOUABLE;
    }
    else {
        return PAS_JOUABLE;
    }
    return JOUABLE;
}


int echanger_chevalet(pioche* p, jeu* j, char che) {
    assert(p != NULL && j != NULL);
    assert(che >= 'A' && che <= 'Z');
	assert(!pioche_vide(p));

    int i = indice_chevalet_paquet(j, che);
    if (i == PAS_JOUABLE)
        return PAS_JOUABLE;
    save_jeu(j);

    int d = rand() % taille_pioche(p);
    char temp = selec_che_j_actuel(j, i);

    remp_che_j_actuel(j,i, selectionner_chevalet(p,d));
    modif_che_pioche(p, d, temp);

    return JOUABLE;
}


int octo_chevalet(jeu* j, jeu* j_autre, rail* r, statut_partie joueur_actuel) {
    assert(j != NULL && j_autre != NULL && r != NULL);
    assert(joueur_actuel == TOUR_J1 || joueur_actuel == TOUR_J2);
    char chevalet_jouer = 'n';
    printf("-%d> ", joueur_actuel);
    scanf(" %c", &chevalet_jouer);
    getchar();
    int i = indice_chevalet_paquet(j, chevalet_jouer); 
	if (i == PAS_JOUABLE)
		return PAS_JOUABLE;
    recevoir_chevalet(j_autre, chevalet_jouer);
    jouer_chevalet(j, chevalet_jouer);
    return JOUABLE;

}
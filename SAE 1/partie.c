#include "partie.h"


int jouer_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r, statut_partie joueur_actuel) {

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
    affichage_jeu(j1, JOUEUR_1);
    affichage_jeu(j2, JOUEUR_2);
    affiche_rail(r);
}

statut_partie demander_mot(dictionnaire* dico,pioche* p, jeu* j, jeu* j_autre, char* mot, int nbj, rail* r, statut_partie joueur_actuel) {
    int valide = PAS_JOUABLE;
    char interprete = 'n', test[MOT_TEST_MAX];

    while (valide == PAS_JOUABLE) {
        printf("%d> ", nbj);

		fgets(test, MOT_TEST_MAX, stdin); // faire une fct rentrer mot jeu et pour l'init rentrer mot init.
        if (test[1] != ' ' || test[0]==' ') {
            //printf("MARCHE PAS %c\n", test[1]);
            continue;
        }
		sscanf(test,"%c %s", &interprete, test);
		//printf("le Char : (%c) le Mot : (%s)\n", interprete, test);
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
                r->t_drn_mot_joue = 1;
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


char sortir_chevalet_droite(rail* r, char cote, int taille_mot) {
    char temp = 'n';

    if (cote == 'R') {
        temp = r->recto[TAILLE_RAIL - 1];
        for (int i = TAILLE_RAIL - 2; i >= 0; i--) {
            r->recto[i + 1] = r->recto[i];
        }
    }
    else if (cote == 'V') {
        temp = r->verso[TAILLE_RAIL - 1];
        for (int i = TAILLE_RAIL - 2; i >= 0; i--) {
            r->verso[i + 1] = r->verso[i];
        }
    }

    return temp;

}


char sortir_chevalet_gauche(rail* r, char cote, int taille_mot) {
    char temp = 'n';

    if (cote == 'R') {
        temp = r->recto[0];
        for (int i = 0; i < TAILLE_RAIL - 1; i++) {
            r->recto[i] = r->recto[i + 1];
        }
    }
    else if (cote == 'V') {
        temp = r->verso[0];
        for (int i = 0; i < TAILLE_RAIL - 1; i++) {
            r->verso[i] = r->verso[i + 1];
        }
    }
    return temp;

}


void inserer_chevalet_droite(rail* r, char che, char cote) {
    if (cote == 'R') {
        r->recto[TAILLE_RAIL - 2] = che;
        copie_recto_verso(r);
    }
    if (cote == 'V') {
        r->verso[TAILLE_RAIL - 2] = che;
        copie_verso_recto(r);
    }
}

void inserer_chevalet_gauche(rail* r, char che, char cote) {
    if (cote == 'R') {
        r->recto[0] = che;
        copie_recto_verso(r);
    }
    if (cote == 'V') {
        r->verso[0] = che;
        copie_verso_recto(r);
    }
}





int verif_format_mot(char* mot, int* indice_ouv, int* indice_ferm ) {

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


    int taille_mot = strlen(mot);
    char mot_forme[TAILLE_MOT_MAX];
    char mot_sans_parenthese[TAILLE_MOT_SANS_P], lettre_parenthese[L_MAX_PARENTH + 1], lettres_hors_parenthese[L_MAX_H_PARENTH + 1];

    if (cote == 'r' || cote == 'v') {
		if (r->t_drn_mot_joue == TAILLE_RAIL - 1 || r->t_drn_mot_joue < TAILLE_MOT_MIN_SANS_P) {
			return PAS_JOUABLE;
		}
        else {
            int i = PAS_JOUABLE;
            while (i == PAS_JOUABLE) {
                printf("\n");
                i = octo_chevalet(j, j_autre, r, joueur_actuel);
            }

            r->t_drn_mot_joue = PAS_JOUABLE;
        }
    }

	if (init_mot(mot, &mot_sans_parenthese, &lettres_hors_parenthese, &lettre_parenthese, cote, j,r) == PAS_JOUABLE) {
		return PAS_JOUABLE;
	}
    int indice_mot = 1; //trouver_mot(dico, &mot_sans_parenthese);
    if (indice_mot == PAS_TROUVER)
        return PAS_JOUABLE;

    if (cote == 'R' || cote == 'V') {
        jouer_mot(j, j_autre, r, dico, mot, &lettre_parenthese, &lettres_hors_parenthese, cote, joueur_actuel);
        r->t_drn_mot_joue = strlen(mot_sans_parenthese);

        if (j->nb[0] == 0) {
            return FINI;
        }

        if (strlen(&mot_sans_parenthese) == TAILLE_MOT_SANS_P - 1) {

			int i = PAS_JOUABLE;
            while (i == PAS_JOUABLE) {
                if (joueur_actuel == TOUR_J1) {
                    printf("\n");
					affichage_tour(j, j_autre, r);
                    i = octo_chevalet(j, j_autre, r, joueur_actuel);

                }
                else {
                    printf("\n");
                    affichage_tour(j_autre, j, r);
                    i = octo_chevalet(j, j_autre, r, joueur_actuel);
                }
            }
        }
    }


    //rendre_mot_injouable(dico, indice_mot); 
    return JOUE;

}



int init_mot(char* mot, char* mot_sans_parenthese, char* lettres_hors_parenthese, char* lettre_parenthese, char cote, jeu* j,rail* r) {
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
    if (cote == 'R') {
        return verif_Recto_debut(mot, r->recto, lettres_parenthese, indice_ferm,indice_ouv, taille_mot);
    }
    else if (cote == 'V') {
        return verif_Verso_debut(mot, r->verso, lettres_parenthese, indice_ferm,indice_ouv, taille_mot);
    }
    if (cote == 'r') {
        return verif_Recto_debut(mot, r->ancien_recto, lettres_parenthese, indice_ferm,indice_ouv, taille_mot);
    }
    else if (cote == 'v') {
        return verif_Verso_debut(mot, r->ancien_verso, lettres_parenthese, indice_ferm,indice_ouv, taille_mot);
	}
    return PAS_JOUABLE;
}
int verif_fin(char* mot, rail* r, char* lettres_parenthese, int indice_ouv,int indice_ferm, int taille_mot, char cote) {
    if (cote == 'R') {
        return verif_Recto_fin(mot, r->recto, lettres_parenthese, indice_ouv, indice_ferm, taille_mot);
    }
    else if (cote == 'V') {
        return verif_Verso_fin(mot, r->verso, lettres_parenthese, indice_ouv, indice_ferm, taille_mot);
    }

    if (cote == 'r') {
        return verif_Recto_fin(mot, r->ancien_recto, lettres_parenthese, indice_ouv, indice_ferm, taille_mot);
    }
    else if (cote == 'v') {
        return verif_Verso_fin(mot, r->ancien_verso, lettres_parenthese, indice_ouv, indice_ferm, taille_mot);
    }
    return PAS_JOUABLE;
}




int verif_Recto_debut(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ferm, int indice_ouv, int taille_mot) {

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
	assert(!pioche_vide(p));

    int i = indice_chevalet_paquet(j, che);
    if (i == PAS_JOUABLE)
        return PAS_JOUABLE;
    save_jeu(j);

    int d = rand() % p->nb;
    char temp = j->jeu_actuel[i];

    j->jeu_actuel[i] = p->pioche[d];
    p->pioche[d] = temp;

    return JOUABLE;
}


int octo_chevalet(jeu* j, jeu* j_autre, rail* r, statut_partie joueur_actuel) {
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
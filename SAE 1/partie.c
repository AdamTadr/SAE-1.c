#include "partie.h"


void jouer_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r, statut_partie joueur_actuel) {

	while (joueur_actuel != FINI) {
        affichage_jeu(j1, 1);
        affichage_jeu(j2, 2);
        affiche_rail(r);
        if (joueur_actuel == TOUR_J2) {
            char mot[TAILLE_MOT_MAX];
            joueur_actuel = demander_mot(dico,j2, j1, mot, joueur_actuel, r, joueur_actuel); // DEMANDER MOT DOIT RETOURNER UNE VALEUR 

        }
        else if (joueur_actuel == TOUR_J1) {
            char mot[TAILLE_MOT_MAX];
            joueur_actuel = demander_mot(dico, j1, j2, mot, joueur_actuel, r, joueur_actuel);
            if (joueur_actuel == FINI)
                return FINI;
        }
        printf("Au tour du joueur %d \n", joueur_actuel);
	}

}


statut_partie demander_mot(dictionnaire* dico, jeu* j, jeu* j_autre, char* mot, int nbj, rail* r, statut_partie joueur_actuel) {
    int valide = PAS_JOUABLE;
    char interprete = 'n';
    char test[MOT_TEST_MAX];

    while (valide == PAS_JOUABLE) {
        printf("%d> ", nbj);
        scanf(" %c %s",&interprete, test);
        if (strlen(test) > TAILLE_MOT_MAX-1)
            continue;
        strcpy(mot, test);  

        printf("Le char : %c\n", interprete);
        printf("Le mot %s\n", mot);
        if (interprete != 'R' && interprete != 'V' && interprete != 'r' && interprete != 'v' && interprete != '-')
            continue;


        if (interprete == 'R' || interprete == 'V') {
            printf("je passe\n");
            valide = tentative(j, j_autre, r,dico,mot,  interprete, joueur_actuel);
            if (valide == FINI) {
                return FINI;
            }

            if (valide != PAS_JOUABLE){
                if (joueur_actuel == TOUR_J2) {
                    printf("Pour lui le tour est au j2");
                    joueur_actuel = TOUR_J1;
                    printf(" Il est censer retourner % d\n", joueur_actuel);
                    return joueur_actuel;
                }
                else if (joueur_actuel == TOUR_J1) {
                    printf("Pour lui le tour est au j1");
                    joueur_actuel = TOUR_J2;
                    printf(" Il est censer retourner %d\n", joueur_actuel);
                    return joueur_actuel;
                }
            }
        }
    }
}






















int jouer_mot(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico,char* mot, char* lettre_parenthese,char cote, statut_partie joueur_actuel) {
    int taille_mot = strlen(mot);
    int taille_mot_remplace = strlen(lettre_parenthese);
    if (taille_mot_remplace == 0)
        return PAS_JOUABLE;

    if (mot[0] == '(') {
        for (int i = 0; i < taille_mot_remplace; i++) {
            save_rail(r, cote);

            char chevalet = sortir_chevalet_droite(r, cote, taille_mot);
            inserer_chevalet_gauche(r, lettre_parenthese[taille_mot_remplace-i-1], cote);

            if (joueur_actuel == TOUR_J1) {
                recevoir_chevalet(j_autre, chevalet);
                jouer_chevalet(j, lettre_parenthese[i]);
            }
            else if (joueur_actuel == TOUR_J2) {
                recevoir_chevalet(j_autre, chevalet);
                jouer_chevalet(j, lettre_parenthese[i]);
            }
            else {
                return PAS_JOUABLE;
            }
        }
    }
    else if (mot[taille_mot - 1] == ')') {
        for (int i = 0; i < taille_mot_remplace; i++) {
            save_rail(r, cote);

            char chevalet = sortir_chevalet_gauche(r, cote, taille_mot);
            inserer_chevalet_droite(r, lettre_parenthese[i], cote);

            if (joueur_actuel == TOUR_J1) {
                recevoir_chevalet(j_autre, chevalet);
                jouer_chevalet(j, lettre_parenthese[i]);
            }
            else if (joueur_actuel == TOUR_J2) {
                recevoir_chevalet(j_autre, chevalet);
                jouer_chevalet(j, lettre_parenthese[i]);
            }
        }
    }
    
}


char sortir_chevalet_droite(rail* r, char cote, int taille_mot){
    char temp = 'n';

    if (cote == 'R') {
        temp = r->recto[TAILLE_RAIL - 1];
        for (int i = TAILLE_RAIL-2; i >=0 ; i--) {
            r->recto[i+1] = r->recto[i];
        }
    }
    else if (cote == 'V') {
        temp = r->verso[TAILLE_RAIL - 1];
        for (int i = TAILLE_RAIL - 2; i >= 0; i--) {
            r->verso[i+1] = r->verso[i];
        }
    }
    printf("\n\n FINISH : \n\n");

    return temp;

}
// Tcheck (pas vrmt lui mais bon)

// Je valide
char sortir_chevalet_gauche(rail* r, char cote, int taille_mot) {
    char temp = 'n';

    if (cote == 'R') {
        temp = r->recto[0];
        for (int i = 0; i <TAILLE_RAIL - 2; i++) { // c'était -1 avt
            r->recto[i] = r->recto[i+1];
        }
    }
    else if (cote == 'V') {
        temp = r->verso[0];
        for (int i = 0; i < TAILLE_RAIL - 2; i++) { // c'était -1 avt
            r->verso[i] = r->verso[i+1];
        }
    }
    printf("\n\n FINISH : \n\n");
    return temp;

}
// tcheck

// Je valide


void inserer_chevalet_droite(rail* r, char che, char cote) {
    if (cote == 'R') {
        r->recto[TAILLE_RAIL - 2] = che;
        //copie_recto_verso(r);
    }
    if (cote == 'V') {
        r->verso[TAILLE_RAIL - 2] = che;
        //copie_verso_recto(r);
    }
    printf("Voici comment le petit (%c) c'est insere : \n", che);
    affiche_rail(r);
    printf("\n\n\n");
}
//tcheck

void inserer_chevalet_gauche(rail* r, char che, char cote) {
    if (cote == 'R') {
        r->recto[0] = che;
        //copie_recto_verso(r);
    }
    if (cote == 'V') {
        r->verso[0] = che;
        //copie_verso_recto(r);
    }
    printf("Voici comment le petit (%c) c'est insere : \n", che);
    affiche_rail(r);
    printf("\n\n\n");
}
//tcheck

int tentative(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico,char* mot, char cote, statut_partie joueur_actuel) {
    printf("Le j actuel que tentative ressoie %d\n", joueur_actuel);
    printf("\n\n%s\n\n", mot);
    printf("BJR\n");
    int parenthese_ouv = 0, indice_ferm;
    int parenthese_ferm = 0, indice_ouv;
    char mot_forme[TAILLE_MOT_MAX];

    int taille_mot = strlen(mot);

    for (int i = 0; i < taille_mot; i++) {
        if (mot[i] == '(') {
            ++parenthese_ouv;
            indice_ouv = i;
        }
        if (mot[i] == ')') {
            ++parenthese_ferm;
            indice_ferm = i;
        }
    }

    if (parenthese_ouv !=1 || parenthese_ferm != 1)
        return PAS_JOUABLE;
    printf("1\n");

    if (indice_ferm - indice_ouv > L_MAX_PARENTH+1 || indice_ferm - indice_ouv== RIEN_ENTRE)
        return PAS_JOUABLE;
    printf("2\n");

    char lettre_parenthese[L_MAX_PARENTH+1];
    if (lettre_joue_valide(mot,&lettre_parenthese, j, indice_ouv, indice_ferm) == PAS_JOUABLE){
        printf("Mince, je ne suis pas jouable\n");
        return PAS_JOUABLE;
    }
    char lettres_hors_parenthese[L_MAX_H_PARENTH + 1];
    if (lettre_rail_valide(j, r, mot, &lettres_hors_parenthese, cote, indice_ouv, indice_ferm) == PAS_JOUABLE) {
        printf("Et bien ca alors, je ne suis pas bonnnn !!!\n");
        return PAS_JOUABLE;
    }
    char mot_sans_parenthese[TAILLE_MOT_SANS_P];
    supprime_parenthese(mot, &lettre_parenthese, &lettres_hors_parenthese, &mot_sans_parenthese);
    int indice_mot = 1;  // IL FAUDRA UTILSIER trouver_mot(dico, &mot_sans_parenthese);
    if (indice_mot == PAS_TROUVER)
        return PAS_JOUABLE;
    jouer_mot(j, j_autre, r, dico, mot, &lettre_parenthese, cote, joueur_actuel);
    // Il faut rajouter après : rendre_mot_injouable(dico, indice_mot);
    if (j->nb[0] == 0) {
        return FINI;
    }

    return joueur_actuel;
    
}


int supprime_parenthese(char* mot, char* lettre_parenthese, char* lettre_hors_parenthese, char* mot_sans_parenthese) {

    int taille_mot = strlen(mot);

    if (mot[0] == '(') {
        strcpy(mot_sans_parenthese, lettre_parenthese);
        int debut = strlen(mot_sans_parenthese);
        for (int i = debut, d = 0; i < TAILLE_MOT_SANS_P-1; i++, d++) {
            mot_sans_parenthese[i] = lettre_hors_parenthese[d];
        }
        mot_sans_parenthese[TAILLE_MOT_SANS_P - 1] = '\0';
        printf(" PRIIIIIIINTF :::::  %s\n", mot_sans_parenthese);
    }
    if (mot[taille_mot - 1] == ')') {
        strcpy(mot_sans_parenthese, lettre_hors_parenthese);
        int debut = strlen(mot_sans_parenthese);
        int fin = strlen(lettre_hors_parenthese);
        int i = debut;
        for (int d = 0; i < debut+fin-1; i++, d++) {
            mot_sans_parenthese[i] = lettre_parenthese[d];
            printf("l'iter = %d la lettre %c \n", i, mot_sans_parenthese[i]);
        }
        mot_sans_parenthese[i] = '\0';

        printf(" PRIIIIIIINTF :::::  %s\n", mot_sans_parenthese);
    }
}



int lettre_rail_valide(jeu* j, rail* r, char* mot, char* lettres_hors_parenthese, char cote, int indice_ouv, int indice_ferm) {
   
    int taille_mot = strlen(mot);
    if (mot[0] == '(') {
        if (cote == 'R') {
            if (verif_Recto_debut(mot, r, lettres_hors_parenthese, indice_ferm, taille_mot) == PAS_JOUABLE){
                return PAS_JOUABLE;
            }
            else {
                return JOUABLE;
            }
  

        }
        else if (cote == 'V') {
            if (verif_Verso_debut(mot, r, lettres_hors_parenthese, indice_ferm, taille_mot) == PAS_JOUABLE)
                return PAS_JOUABLE;
            else
                return JOUABLE;
        }
        else {
            return PAS_JOUABLE;
        }
    }



    else if (mot[taille_mot - 1] == ')') {
        if (cote == 'R') {
            if (verif_Recto_fin(mot, r, lettres_hors_parenthese, indice_ouv, taille_mot) == PAS_JOUABLE)
                return PAS_JOUABLE;
            else
                return JOUABLE;
        }
        else if (cote == 'V') {
            if (verif_Verso_fin(mot, r, lettres_hors_parenthese, indice_ouv, taille_mot) == PAS_JOUABLE)
                return PAS_JOUABLE;
            else
                return JOUABLE;
        }
        else {
            return PAS_JOUABLE;
        }
    }
    else
        return PAS_JOUABLE;


}


int verif_Recto_debut(char* mot, rail* r, char* lettres_hors_parenthese, int indice_ferm, int taille_mot) {

    int d = 0;
    for (int i = indice_ferm +1; i < taille_mot && d < L_MAX_H_PARENTH - 1; i++) {
        printf("Les lettres du mot : %c, ceux du rail %c\n", mot[i], r->recto[d]);
        if (mot[i] == r->recto[d])
            lettres_hors_parenthese[d++] = mot[i];
        else
            return PAS_JOUABLE;
    }
    lettres_hors_parenthese[d] = '\0';
    if (strlen(lettres_hors_parenthese) < 2) {
        return PAS_JOUABLE;
    }

    printf("Voila ce que ça a copie colle %s", lettres_hors_parenthese);
    return JOUABLE;
}


int verif_Recto_fin(char* mot, rail* r, char* lettres_hors_parenthese, int indice_ouv, int taille_mot) {
    int d = indice_ouv - 1, j = 0;
    for (int i = TAILLE_RAIL - 2 ; d >= 0 ; i--, d--, j++) {
        printf("Les lettres du mot : %c, ceux du rail %c\n", mot[d], r->recto[i]);
        if (mot[d] == r->recto[i]){
            lettres_hors_parenthese[j] = mot[j];
        }
        else
            return PAS_JOUABLE;
    }
    lettres_hors_parenthese[j] = '\0';
    if (strlen(lettres_hors_parenthese) < 2) {
        return PAS_JOUABLE;
    }
    printf("Voila ce que ca a copie colle %s\n", lettres_hors_parenthese);
    return JOUABLE;
}


int verif_Verso_debut(char* mot, rail* r, char* lettres_hors_parenthese, int indice_ferm, int taille_mot) {
    int d = 0;
    for (int i = indice_ferm + 1; i < taille_mot && d < L_MAX_H_PARENTH - 1; i++) {
        printf("Les lettres du mot : %c, ceux du rail %c\n", mot[i], r->verso[d]);
        if (mot[i] == r->verso[d])
            lettres_hors_parenthese[d++] = mot[i];
        else
            return PAS_JOUABLE;
    }
    lettres_hors_parenthese[d] = '\0';
    if (strlen(lettres_hors_parenthese) < 2) {
        return PAS_JOUABLE;
    }
    printf("Voila ce que ça a copie colle %s", lettres_hors_parenthese);
    return JOUABLE;
}

int verif_Verso_fin(char* mot, rail* r, char* lettres_hors_parenthese, int indice_ouv, int taille_mot) {
    int d = indice_ouv - 1, j = 0;
    for (int i = TAILLE_RAIL - 2; d >= 0; i--, d--, j++) {
        printf("Les lettres du mot : %c, ceux du rail %c\n", mot[d], r->verso[i]);
        if (mot[d] == r->verso[i]) {
            lettres_hors_parenthese[j] = mot[j];
        }
        else
            return PAS_JOUABLE;
    }
    lettres_hors_parenthese[j] = '\0';
    if (strlen(lettres_hors_parenthese) < 2) {
        return PAS_JOUABLE;
    }
    printf("Voila ce que ca a copie colle %s\n", lettres_hors_parenthese);
    return JOUABLE;
}

int lettre_joue_valide(char* mot, char* lettres_parenthese, jeu* j, int indice_ouv, int indice_ferm) {
    printf("Le mot detecte %s\n", mot);

    int d = 0;
    for (int i = indice_ouv+1 ; i < indice_ferm && d < L_MAX_PARENTH - 1; i++)
        lettres_parenthese[d++] = mot[i];

    lettres_parenthese[d] = '\0';

    if (strlen(lettres_parenthese) == 0) {
        return PAS_JOUABLE;
    }

    printf("Ce qu'il detecte dans la paranthese : %s\n", lettres_parenthese);

    if (jouable(j, lettres_parenthese) == PAS_JOUABLE)
        return PAS_JOUABLE;
    return JOUABLE;
}

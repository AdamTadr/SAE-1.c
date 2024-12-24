#pragma once
#include "rail.h"

typedef enum{TOUR_J1 = 1, TOUR_J1_OCTO = -1, TOUR_J2 = 2, TOUR_J2_OCTO = -2, FINI = 0} statut_partie;

enum{ L_MAX_PARENTH= 7, L_MAX_H_PARENTH = 8, RIEN_ENTRE = 1, TAILLE_LETTRE = 1};



#include "partie.h"


int jouer_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r, statut_partie joueur_actuel);


statut_partie demander_mot(dictionnaire* dico, pioche* p, jeu* j, jeu* j_autre, char* mot, int nbj, rail* r, statut_partie joueur_actuel);




void jouer_mot(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico, char* mot, char* lettre_parenthese, char* lettre_hors_p, char cote, statut_partie joueur_actuel);


char sortir_chevalet_droite(rail* r, char cote, int taille_mot);


char sortir_chevalet_gauche(rail* r, char cote, int taille_mot);


void inserer_chevalet_droite(rail* r, char che, char cote);

void inserer_chevalet_gauche(rail* r, char che, char cote);




int verif_format_mot(char* mot, int* indice_ouv, int* indice_ferm);




int tentative(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico, char* mot, char cote, statut_partie joueur_actuel);









int init_mot(char* mot, char* mot_sans_parenthese, char* lettres_hors_parenthese, char* lettre_parenthese, char cote, jeu* j, rail* r);








void supprime_parenthese(char* mot, char* lettre_parenthese, char* lettre_hors_parenthese, char* mot_sans_parenthese);



int lettre_joue_valide(rail* r, jeu* j, char* mot, char* lettres_hors_parenthese, char* lettres_parenthese, char cote, int indice_ouv, int indice_ferm);





int verif_debut(char* mot, rail* r, char* lettres_parenthese, int indice_ferm, int indice_ouv, int taille_mot, char cote);
int verif_fin(char* mot, rail* r, char* lettres_parenthese, int indice_ouv,int indice_ferm, int taille_mot, char cote);




int verif_Recto_debut(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ferm, int indice_ouv, int taille_mot);
int verif_Recto_fin(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ouv, int indice_ferm, int taille_mot);

int verif_Verso_debut(char* mot, char* rail_verso, char* lettres_parenthese, int indice_ferm,int indice_ouv, int taille_mot);

int verif_Verso_fin(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ouv, int indice_ferm, int taille_mot);




int lettre_rail_valide(rail* r, char* mot, char* lettres_hors_parenthese, char* lettres_parenthese, char cote, jeu* j, int indice_ouv, int indice_ferm);


void octo_chevalet(jeu* j, jeu* j_autre, statut_partie joueur_actuel);

void echanger_chevalet(pioche* p, jeu* j, char che);

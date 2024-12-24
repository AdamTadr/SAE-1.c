#pragma once
#include "dictionnaire.h"
#pragma warning(disable:4996)

typedef enum { FAUX, VRAI }bool;

enum { TAILLE_RAIL = 9, MOT_DEPART = 5, MOT_TEST_MAX =50, PAS_ENCORE_JOUE = 0 };

typedef struct {
    char recto[TAILLE_RAIL];
    char verso[TAILLE_RAIL];
    char ancien_recto[TAILLE_RAIL];
    char ancien_verso[TAILLE_RAIL];
    int t_drn_mot_joue;
} rail;

void init_rail(rail* r);
int init_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r);
int depart_valide(dictionnaire* dico, const char* mot, jeu* joueur);
void demander_mot_depart(dictionnaire* dico, jeu* j, char* mot, int nbj);
int placement_de_depart(jeu* j1, jeu* j2, const char* mot1, const char* mot2, rail* r);
void affiche_rail(const rail* r);
void copie_recto_verso(rail* r);
void copie_verso_recto(rail* r);
void copie_averso_arecto(rail* r);
void copie_arecto_averso(rail* r);
void save_rail(rail* r, char cote);

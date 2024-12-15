#pragma once
#include "dictionnaire.h"
#pragma warning(disable:4996)

typedef enum { FAUX, VRAI }bool;

enum { TAILLE_RAIL = 9, MOT_DEPART = 5 };

typedef struct {
    char recto[TAILLE_RAIL];
    char verso[TAILLE_RAIL];
} rail;

void init_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r);
int depart_valide(dictionnaire* dico, const char* mot, jeu* joueur);
void demander_mot(dictionnaire* dico, jeu* joueur, char* mot);
void placement_de_depart(jeu* j1, jeu* j2, const char* mot1, const char* mot2, rail* r);
void affiche_rail(rail* r);
void copie_recto_verso(rail* r);
//void copie_verso_recto(rail* r);

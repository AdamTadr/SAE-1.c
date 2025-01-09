#pragma once
#include "joueur.h"

enum { TAILLE_ALPHABET = 26, PREMIERE_LETTRE = 0, DEUXIEME_LETTRE = 1, PAS_TROUVER = -1, VIDE = 0};

typedef struct {
	int ind_premiere;
	int ind_deuxieme[TAILLE_ALPHABET];
}index;

typedef struct {
	index index[TAILLE_ALPHABET];
	char** dico;
	int taille;
}dictionnaire;


size_t recherche_taille_dico(const char* nom_dico);

int taille_dico(const dictionnaire* dico);

void creation_dico(dictionnaire* dico, size_t taille, const char* nom_dico);

void indexage_dico(dictionnaire* dico);

void init_index(dictionnaire* dico);

void indexage_secondaire(dictionnaire* dico, char ref, int depart);

void affichage_index(const dictionnaire* dico);

int trouver_mot(const dictionnaire* dico, const char* mot);

char* addr_mot(const dictionnaire* dico, int indice);

int bonne_casse(const char* mot);

void rendre_mot_injouable(dictionnaire* dico, int indice);

void mod_taille_dico(dictionnaire* dico, int taille);

int dico_vide(const dictionnaire* dico);

// dico->index[val_alphanum_l].ind_premiere;
int indice_premiere_lettre(const dictionnaire* dico, int val_alphanum_l);

//dico->index[val_alphanum_l].ind_premiere = indice;
void add_ind_prem_l(dictionnaire* dico, int val_alphanum_l, int indice);

//dico->index[val_alphanum_l1].ind_deuxieme[val_alphanum_l2] = indice;
void add_ind_deuxieme_l(dictionnaire* dico, int val_alphanum_l1, int val_alphanum_l2, int indice);
// dico->index[val_alphanum_l].ind_deuxieme[val_alphanum_l];
int indice_deuxieme_lettre(const dictionnaire* dico, int val_num_l, int val_ref);

void changer_taille_dico(dictionnaire* dico, int valeur);

void dico_alloc(dictionnaire* dico, size_t taille);

//return dico->dico[indice][PREMIERE_LETTRE];
int val_permiere_lettre(const dictionnaire* dico, int indice);

//return dico->dico[indice][DEUXIEME_LETTRE];
int val_deuxieme_lettre(const dictionnaire* dico, int indice);

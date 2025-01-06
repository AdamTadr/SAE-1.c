#pragma once
#include "joueur.h"

enum { TAILLE_ALPHABET = 26, PREMIERE_LETTRE = 0, DEUXIEME_LETTRE = 1, PAS_TROUVER = -1 };

typedef struct {
	int ind_premiere;
	int ind_deuxieme[TAILLE_ALPHABET];
}index;

typedef struct {
	index index[TAILLE_ALPHABET];
	char** dico;
	int taille;
}dictionnaire;


size_t recherche_taille_dico(char* nom_dico);

int taille_dico(dictionnaire* dico);

void creation_dico(dictionnaire* dico, size_t taille, char* nom_dico);

void affichage_dico(const dictionnaire* dico);

void indexage_dico(dictionnaire* dico);

void indexage_secondaire(dictionnaire* dico, char ref, int depart);

void affichage_index(const dictionnaire* dico);

int trouver_mot(const dictionnaire* dico, const char* mot);

int bonne_casse(const char* mot);

void rendre_mot_injouable(dictionnaire* dico, int indice);
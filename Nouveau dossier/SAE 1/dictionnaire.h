#pragma once
#include "joueur.h"

enum { TAILLE_ALPHABET = 26, PREMIERE_LETTRE = 0, DEUXIEME_LETTRE = 1, PAS_TROUVER = -1 };

typedef enum {
	A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7, I = 8, J = 9,
	K = 10, L = 11, M = 12, N = 13, O = 14, P = 15, Q = 16, R = 17, S = 18, T = 19,
	U = 20, V = 21, W = 22, X = 23, Y = 24, Z = 25
} alphabet_numerique;

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
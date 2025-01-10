#pragma once
#include "pioche.h"

enum { MAX_CHEVALETS = 16, CHEVALETS_INIT = 12, NB_TABLEAU = 2, PAS_JOUABLE = -1, JOUABLE = 1, JOUE = 1, TAILLE_MOT_MAX = 11,TAILLE_MOT_MIN = 5, TAILLE_MOT_SANS_P = 9, TAILLE_MOT_MIN_SANS_P = 3,
JEU_ACTUEL = 0, JEU_PRECEDENT = 1, RIEN = 0 };


typedef struct {
	int nb[NB_TABLEAU];
	char jeu_actuel[MAX_CHEVALETS];
	char jeu_precedent[MAX_CHEVALETS];
}jeu;

typedef struct {
	int nb;
	int list[TAILLE_MOT_MAX];
}black_list;


void init_bl(black_list* bl);

int taille_jeu_actuel(const jeu* j);

void init_jeu(jeu* j); // la capacité initial (12), le nb pour les 2 cases est nul et correspod à la taille des 2 jeux.

int paquet_vide(const jeu* j);

void remplir_paquet(jeu* j, pioche* p); //autant que ça capacité

void trie_alphabetique(jeu* j);

void affichage_jeu(jeu* j, int jnb);

void affichage_jeu_precedent(jeu* j, int jnb);

char distribuer_chevalet(pioche* p, int i);

void recevoir_chevalet(jeu* j, char che);

char jouer_chevalet(jeu* j, char che);

void save_jeu(jeu* j);

int jouable(jeu* j, char* che);

int precedent_jouable(jeu* j_autre, char* che);

void modif_j_taille_jeu(jeu* j, int taille);

void modif_j_taille_jeu_precedent(jeu* j, int taille);

char selec_che_j_actuel(jeu* j, int indice);

char selec_che_j_precendent(jeu* j, int indice);

void remp_che_j_actuel(jeu* j, int indice, char che);

void ajouter_che(jeu* j, char che);

void ajouter_che_precedent(jeu* j,int ind, char che);

int taille_bl(black_list* bl);

int selec_ele_bl(black_list* bl, int indice);

void ajouter_ele_bl(black_list* bl, int n);

void decr_j_actuel(jeu* j);


// Rajouter une fct ajouter carte prenant en paramètre le char retourner par le distrib_chevalet correspondant, elle est void,
// à chaque fois que le joueur perd face à son adv, fait une alloc dynamique si le nb > 0 avec facteur 8 (ou autre)...

// Rajouter une fct échanger carte à chaque fois que le joueur en à l'occasion, de ce fait rajouter une fct recevoir carte pour pioche.c ...
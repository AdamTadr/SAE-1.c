#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

enum { MAX_pioche = 88 };

typedef enum {
	UNE_L =1, NB_E = 14, NB_A = 9, NB_IS = 7,
	NB_NTR = 6, NB_ULO = 5, NB_MD = 3, NB_CVP = 2
}freq_lettres;


/**
 * @brief pioche est une structure compos� d'un tableau de caract�res
 * et du nombre de caract�res dans ce tableau, permettant de repr�senter
 * un pioche de chevalet.
 */

typedef struct {
	int nb;
	char pioche[MAX_pioche];
}pioche;

/**
 * @brief V�rifie si un pioche est vide
 * @param[in] p  Le pioche de chevalets que l'on v�rifie.
 * @return Retourne un bool�en indiqueant si oui ou non le pioche vide
 */
int pioche_vide(pioche* p);

/**
 * @brief l'initialisation d'une pioche vide.
 * @param[out] p La pioche initialis�.
 */
void init_pioche(pioche* p);

/**
* @brief Permet l'initialisation d'une pioche de chevalets.
* @param[in][out] p La pioche remplis de chevalet.
* @pre la pioche doit �tre vide.
*/
void remplissage_pioche(pioche* p);

// Pour Debug.
void affichage_pioche(const pioche* p);


char distribuer_chevalet(pioche* p, int i);

/**
 * @brief
 * @param p
 * @param i
 * @return
 */

int indice_valide(const pioche* p, int i);


void ajouter_element_pioche(pioche* p, char che);

char selectionner_chevalet(const pioche* p, int n);

int taille_pioche(const pioche* p);

void mod_taille_pioche(pioche* p, int n);
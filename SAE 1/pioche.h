#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

enum { MAX_pioche = 88, VIDE = 0, TEST = 5};
/**
 * @brief fréquence de remplissage des lettres dans la pioche
 */
typedef enum {
	UNE_L =1, NB_E = 14, NB_A = 9, NB_IS = 7,
	NB_NTR = 6, NB_ULO = 5, NB_MD = 3, NB_CVP = 2
}freq_lettres;


/**
 * @brief pioche est une structure composé d'un tableau de caractères
 * et du nombre de caractères dans ce tableau, permettant de représenter
 * un pioche de chevalet.
 */

typedef struct {
	int nb;
	char pioche[MAX_pioche];
}pioche;

/**
 * @brief Vérifie si un pioche est vide
 * @param[in] p  Le pioche de chevalets que l'on vérifie.
 * @return Retourne un booléen indiqueant si oui ou non le pioche vide
 */
int pioche_vide(pioche* p);

/**
 * @brief l'initialisation d'une pioche vide.
 * @param[out] p La pioche initialisé.
 */
void init_pioche(pioche* p);

/**
* @brief Permet l'initialisation d'une pioche de chevalets.
* @param[in][out] p La pioche remplis de chevalet.
* @pre la pioche doit être vide.
*/
void remplissage_pioche(pioche* p);

/**
 * @brief Permet d'afficher une pioche
 * @param p la pioche à afficher
 */
void affichage_pioche(const pioche* p);

/**
 * @brief Distribue un chevalet spécifique depuis la pioche.
 * @param[in, out] p La pioche dont le chevalet est distribué.
 * @param[in] i L'indice du chevalet à distribuer.
 * @return Le chevalet distribué.
 */
char distribuer_chevalet(pioche* p, int i);

/**
 * @brief Vérifie si un indice donné est valide pour la pioche.
 * @param[in] p La pioche à vérifier.
 * @param[in] i L'indice à valider.
 * @return 1 si l'indice est valide, sinon 0.
 */
int indice_valide(const pioche* p, int i);

/**
 * @brief Ajoute un chevalet à la pioche.
 *
 * Cette fonction ajoute un caractère (chevalet) à la pioche et augmente le nombre de chevalets dans la pioche.
 *
 * @param p La pioche à laquelle on ajoute un chevalet.
 * @param che Le chevalet à ajouter (un caractère).
 */

void ajouter_element_pioche(pioche* p, char che);

/**
 * @brief Sélectionne un chevalet à partir de la pioche.
 *
 * Cette fonction retourne le chevalet à un indice donné dans la pioche.
 *
 * @param p La pioche dont on sélectionne le chevalet.
 * @param n L'indice du chevalet à sélectionner.
 * @return Le chevalet à l'indice spécifié (un caractère).
 */
char selectionner_chevalet(const pioche* p, int n);

/**
 * @brief Obtient la taille actuelle de la pioche.
 *
 * Cette fonction retourne le nombre actuel de chevalets dans la pioche.
 *
 * @param p La pioche dont on veut connaître la taille.
 * @return Le nombre de chevalets dans la pioche.
 */
int taille_pioche(const pioche* p);

/**
 * @brief Modifie la taille de la pioche.
 *
 * Cette fonction met à jour le nombre de chevalets dans la pioche. Cela peut être utilisé pour ajouter ou retirer des chevalets.
 *
 * @param p La pioche dont on veut modifier la taille.
 * @param n La nouvelle taille de la pioche.
 */
void mod_taille_pioche(pioche* p, int n);
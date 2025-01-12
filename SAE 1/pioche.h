#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

enum { MAX_pioche = 88, VIDE = 0, TEST = 5};
/**
 * @brief fr�quence de remplissage des lettres dans la pioche
 */
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

/**
 * @brief Permet d'afficher une pioche
 * @param p la pioche � afficher
 */
void affichage_pioche(const pioche* p);

/**
 * @brief Distribue un chevalet sp�cifique depuis la pioche.
 * @param[in, out] p La pioche dont le chevalet est distribu�.
 * @param[in] i L'indice du chevalet � distribuer.
 * @return Le chevalet distribu�.
 */
char distribuer_chevalet(pioche* p, int i);

/**
 * @brief V�rifie si un indice donn� est valide pour la pioche.
 * @param[in] p La pioche � v�rifier.
 * @param[in] i L'indice � valider.
 * @return 1 si l'indice est valide, sinon 0.
 */
int indice_valide(const pioche* p, int i);

/**
 * @brief Ajoute un chevalet � la pioche.
 *
 * Cette fonction ajoute un caract�re (chevalet) � la pioche et augmente le nombre de chevalets dans la pioche.
 *
 * @param p La pioche � laquelle on ajoute un chevalet.
 * @param che Le chevalet � ajouter (un caract�re).
 */

void ajouter_element_pioche(pioche* p, char che);

/**
 * @brief S�lectionne un chevalet � partir de la pioche.
 *
 * Cette fonction retourne le chevalet � un indice donn� dans la pioche.
 *
 * @param p La pioche dont on s�lectionne le chevalet.
 * @param n L'indice du chevalet � s�lectionner.
 * @return Le chevalet � l'indice sp�cifi� (un caract�re).
 */
char selectionner_chevalet(const pioche* p, int n);

/**
 * @brief Obtient la taille actuelle de la pioche.
 *
 * Cette fonction retourne le nombre actuel de chevalets dans la pioche.
 *
 * @param p La pioche dont on veut conna�tre la taille.
 * @return Le nombre de chevalets dans la pioche.
 */
int taille_pioche(const pioche* p);

/**
 * @brief Modifie la taille de la pioche.
 *
 * Cette fonction met � jour le nombre de chevalets dans la pioche. Cela peut �tre utilis� pour ajouter ou retirer des chevalets.
 *
 * @param p La pioche dont on veut modifier la taille.
 * @param n La nouvelle taille de la pioche.
 */
void mod_taille_pioche(pioche* p, int n);
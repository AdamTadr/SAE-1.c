#pragma once
#include "joueur.h"

enum { TAILLE_ALPHABET = 26, PREMIERE_LETTRE = 0, DEUXIEME_LETTRE = 1, PAS_TROUVER = -1, A = 0};

/**
 * Structure repr�sentant l index des mots dans le dictionnaire
 * Chaque index contient l indice du premier mot correspondant � une lettre donn�e et un tableau pour les indices des mots en fonction de la deuxi�me lettre
 */
typedef struct {
    int ind_premiere; /**< Indice du premier mot pour une lettre donn�e */
    int ind_deuxieme[TAILLE_ALPHABET]; /**< Tableau des indices des mots pour chaque deuxi�me lettre */
}index;

/**
 * Structure repr�sentant un dictionnaire
 * Contient un tableau de mots une taille et un index pour un acc�s rapide aux mots par leur premi�re et deuxi�me lettre
 */
typedef struct {
    index index[TAILLE_ALPHABET]; /**< Index primaire et secondaire pour les mots */
    char** dico; /**< Tableau dynamique contenant les mots du dictionnaire */
    int taille; /**< Nombre total de mots dans le dictionnaire */
}dictionnaire;

/**
 * Recherche la taille d un dictionnaire en comptant le nombre de mots dans un fichier
 *
 * @param nom_dico Le nom du fichier contenant les mots du dictionnaire
 * @return Le nombre de mots dans le fichier
 */
size_t recherche_taille_dico(const char* nom_dico);

/**
 * Retourne la taille actuelle du dictionnaire
 *
 * @param dico Pointeur vers le dictionnaire
 * @return La taille du dictionnaire
 */

int taille_dico(const dictionnaire* dico);

/**
 * Cr�e et initialise un dictionnaire � partir d un fichier de mots
 *
 * @param dico Pointeur vers le dictionnaire � initialiser
 * @param taille Nombre de mots � lire
 * @param nom_dico Nom du fichier contenant les mots
 */
void creation_dico(dictionnaire* dico, size_t taille, const char* nom_dico);

/**
 * Cr�e un index primaire pour acc�der rapidement aux mots en fonction de leur premi�re lettre
 *
 * @param dico Pointeur vers le dictionnaire � indexer
 */
void indexage_dico(dictionnaire* dico);


void init_index(dictionnaire* dico);

/**
 * Cr�e un index secondaire pour les mots commen�ant par une lettre donn�e
 *
 * @param dico Pointeur vers le dictionnaire � indexer
 * @param ref Lettre de r�f�rence pour l index secondaire
 * @param depart Position de d�part pour l indexation
 */
void indexage_secondaire(dictionnaire* dico, char ref, int depart);

/**
 * Affiche l index primaire du dictionnaire pour chaque lettre de l alphabet
 *
 * @param dico Pointeur constant vers le dictionnaire
 */
void affichage_index(const dictionnaire* dico);

/**
 * Recherche un mot sp�cifique dans le dictionnaire en utilisant les index primaires et secondaires
 *
 * @param dico Pointeur constant vers le dictionnaire
 * @param mot Mot � rechercher
 * @return L indice du mot dans le dictionnaire ou PAS_TROUVER si le mot est absent
 */
int trouver_mot(const dictionnaire* dico, const char* mot);

char* addr_mot(const dictionnaire* dico, int indice);

/**
 * V�rifie si un mot est bien en majuscules et sans caract�res invalides
 *
 * @param mot Le mot � v�rifier
 * @return 1 si le mot est valide sinon PAS_TROUVER
 */
int bonne_casse(const char* mot);

/**
 * Rend un mot injouable en le rempla�ant par une cha�ne vide
 *
 * @param dico Pointeur vers le dictionnaire
 * @param indice Indice du mot � rendre injouable
 */
void rendre_mot_injouable(dictionnaire* dico, int indice);

void mod_taille_dico(dictionnaire* dico, int taille);

int dico_vide(const dictionnaire* dico);


int indice_premiere_lettre(const dictionnaire* dico, int val_alphanum_l);


void add_ind_prem_l(dictionnaire* dico, int val_alphanum_l, int indice);


void add_ind_deuxieme_l(dictionnaire* dico, int val_alphanum_l1, int val_alphanum_l2, int indice);

int indice_deuxieme_lettre(const dictionnaire* dico, int val_num_l, int val_ref);

void changer_taille_dico(dictionnaire* dico, int valeur);

void dico_alloc(dictionnaire* dico, size_t taille);


int val_permiere_lettre(const dictionnaire* dico, int indice);

/**
 * @brief Obtient la valeur num�rique de la deuxi�me lettre d'un mot.
 *
 * @param dico Pointeur vers le dictionnaire.
 * @param indice Indice du mot dans le dictionnaire.
 * @return La valeur num�rique de la deuxi�me lettre du mot.
 */
int val_deuxieme_lettre(const dictionnaire* dico, int indice);

#pragma once
#include "pioche.h"

enum {
	MAX_CHEVALETS = 16, CHEVALETS_INIT = 12, NB_TABLEAU = 2, PAS_JOUABLE = -1, JOUABLE = 1, JOUE = 1, TAILLE_MOT_MAX = 11, TAILLE_MOT_MIN = 5, TAILLE_MOT_SANS_P = 9, TAILLE_MOT_MIN_SANS_P = 3, RIEN = 0, JEU_ACTUEL = 0, JEU_PRECEDENT = 1
};

/**
 * Structure repr�sentant le jeu d'un joueur avec les chevalets actuels et pr�c�dents
 */
typedef struct {
	int nb[NB_TABLEAU];
	char jeu_actuel[MAX_CHEVALETS];
	char jeu_precedent[MAX_CHEVALETS];
} jeu;

/**
 * Structure repr�sentant une liste noire des indices de lettres d�j� comptabilis�s
 */
typedef struct {
	int nb;
	int list[TAILLE_MOT_MAX];
} black_list;

/**
 * Initialise une liste noire vide
 *
 * @param[out] bl Liste noire � initialiser
 */
void init_bl(black_list* bl);

/**
 * R�cup�re la taille actuelle du jeu
 *
 * @param[in] j Le jeu pour lequel la taille est demand�e
 *
 * @return La taille actuelle du jeu
 */
int taille_jeu_actuel(const jeu* j);

/**
 * Initialisation d'un jeu avec une capacit� initiale
 *
 * @param[out] j Le jeu � initialiser
 * @pre Le jeu doit �tre vide avant l'appel de cette fonction
 */
void init_jeu(jeu* j); // la capacit� initiale (12), le nb pour les 2 cases est nul et correspond � la taille des 2 jeux

/**
 * V�rifie si le paquet est vide
 *
 * @param[in] j Le jeu � v�rifier
 *
 * @return 1 si le paquet est vide, 0 sinon
 */
int paquet_vide(const jeu* j);

/**
 * Remplissage du paquet avec des chevalets de la pioche
 *
 * @param[in,out] j Le jeu � remplir avec des chevalets
 * @param[in] p La pioche contenant les chevalets � distribuer
 */
void remplir_paquet(jeu* j, pioche* p); // autant que sa capacit�

/**
 * Trie les chevalets du jeu par ordre alphab�tique
 *
 * @param[in,out] j Le jeu dont les chevalets doivent �tre tri�s
 */
void trie_alphabetique(jeu* j);

/**
 * Affiche le jeu actuel d'un joueur
 *
 * @param[in] j Le jeu � afficher
 * @param[in] jnb Le num�ro du joueur
 */
void affichage_jeu(const jeu* j, int jnb);

/**
 * Affiche le jeu pr�c�dent d'un joueur
 *
 * @param[in] j Le jeu � afficher
 * @param[in] jnb Le num�ro du joueur
 */
void affichage_jeu_precedent(const jeu* j, int jnb);

/**
 * Distribue un chevalet � partir de la pioche
 *
 * @param[in,out] p La pioche d'o� le chevalet est distribu�
 * @param[in] i L'indice du chevalet � distribuer
 *
 * @return Le chevalet distribu�
 */
char distribuer_chevalet(pioche* p, int i);

/**
 * Ajoute un chevalet au jeu du joueur
 *
 * @param[in,out] j Le jeu auquel le chevalet est ajout�
 * @param[in] che Le chevalet � ajouter
 */
void recevoir_chevalet(jeu* j, char che);

/**
 * Joue un chevalet du jeu du joueur
 *
 * @param[in,out] j Le jeu du joueur
 * @param[in] che Le chevalet jou�
 *
 * @return Le chevalet jou�
 */
char jouer_chevalet(jeu* j, char che);

/**
 * Sauvegarde le jeu actuel du joueur
 *
 * @param[in,out] j Le jeu � sauvegarder
 */
void save_jeu(jeu* j);

/**
 * V�rifie si un mot est jouable avec les chevalets du joueur
 *
 * @param[in] j Le jeu du joueur
 * @param[in] che Le mot � tester
 *
 * @return 1 si le mot est jouable, -1 sinon
 */
int jouable(jeu* j, char* che);

/**
 * V�rifie si un mot est jouable � partir du jeu pr�c�dent d'un autre joueur
 *
 * @param[in] j_autre Le jeu du joueur adverse
 * @param[in] che Le mot � tester
 *
 * @return 1 si le mot est jouable, -1 sinon
 */
int precedent_jouable(jeu* j_autre, char* che);

/**
 * @brief Modifie la taille du jeu actuel.
 *
 * @param[out] j Le jeu � modifier.
 * @param[in] taille La nouvelle taille du jeu.
 */
void modif_j_taille_jeu(jeu* j, int taille);

/**
 * @brief Modifie la taille du jeu pr�c�dent.
 *
 * @param[out] j Le jeu � modifier.
 * @param[in] taille La nouvelle taille du jeu pr�c�dent.
 */
void modif_j_taille_jeu_precedent(jeu* j, int taille);

/**
 * @brief Ajoute un chevalet au jeu actuel.
 *
 * @param[out] j Le jeu auquel le chevalet est ajout�.
 * @param[in] che Le chevalet � ajouter.
 */
void ajouter_che(jeu* j, char che);

/**
 * @brief Ajoute un chevalet au jeu pr�c�dent.
 *
 * @param[out] j Le jeu auquel le chevalet est ajout�.
 * @param[in] ind L'indice o� le chevalet doit �tre ajout�.
 * @param[in] che Le chevalet � ajouter.
 */
void ajouter_che_precedent(jeu* j, int ind, char che);

/**
 * @brief S�lectionne un chevalet dans le jeu actuel.
 *
 * @param[in] j Le jeu dans lequel s�lectionner le chevalet.
 * @param[in] indice L'indice du chevalet � s�lectionner.
 *
 * @return Le chevalet s�lectionn�.
 */
char selec_che_j_actuel(const jeu* j, int indice);

/**
 * @brief S�lectionne un chevalet dans le jeu pr�c�dent.
 *
 * @param[in] j Le jeu dans lequel s�lectionner le chevalet.
 * @param[in] indice L'indice du chevalet � s�lectionner.
 *
 * @return Le chevalet s�lectionn�.
 */
char selec_che_j_precendent(const jeu* j, int indice);

/**
 * @brief Remplace un chevalet dans le jeu actuel.
 *
 * @param[out] j Le jeu dans lequel le remplacement est effectu�.
 * @param[in] indice L'indice du chevalet � remplacer.
 * @param[in] che Le nouveau chevalet.
 */
void remp_che_j_actuel(jeu* j, int indice, char che);

/**
 * @brief D�cr�mente la taille du jeu actuel.
 *
 * @param[out] j Le jeu dont la taille doit �tre d�cr�ment�e.
 */
void decr_j_actuel(jeu* j);

/**
 * @brief Ajoute un indice � la liste noire.
 *
 * @param[out] bl La liste noire � modifier.
 * @param[in] n L'indice � ajouter.
 */
void ajouter_ele_bl(black_list* bl, int n);

/**
 * @brief Trouve l'indice d'un chevalet dans le jeu actuel.
 *
 * @param[in] j Le jeu � analyser.
 * @param[in] che Le chevalet � rechercher.
 *
 * @return L'indice du chevalet, ou `PAS_JOUABLE` si non trouv�.
 */
int indice_chevalet_paquet(jeu* j, char che);

/**
 * @brief Retourne la taille du jeu pr�c�dent.
 *
 * @param[in] j Le jeu � analyser.
 *
 * @return La taille du jeu pr�c�dent.
 */
int taille_jeu_precent(const jeu* j);

/**
 * @brief S�lectionne un �l�ment de la liste noire.
 *
 * @param[in] bl La liste noire � analyser.
 * @param[in] indice L'indice de l'�l�ment � s�lectionner.
 *
 * @return L'�l�ment s�lectionn�.
 */
int selec_ele_bl(black_list* bl, int indice);

/**
 * @brief V�rifie si un indice est d�j� comptabilis� dans la liste noire.
 *
 * @param[in] indice L'indice � v�rifier.
 * @param[in] bl La liste noire � analyser.
 *
 * @return 1 si l'indice est comptabilis�, 0 sinon.
 */
int deja_comptabiliser(int indice, const black_list* bl);

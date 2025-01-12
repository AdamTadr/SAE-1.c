#pragma once
#include "pioche.h"

enum {
	MAX_CHEVALETS = 16, CHEVALETS_INIT = 12, NB_TABLEAU = 2, PAS_JOUABLE = -1, JOUABLE = 1, JOUE = 1, TAILLE_MOT_MAX = 11, TAILLE_MOT_MIN = 5, TAILLE_MOT_SANS_P = 9, TAILLE_MOT_MIN_SANS_P = 3, RIEN = 0, JEU_ACTUEL = 0, JEU_PRECEDENT = 1
};

/**
 * Structure représentant le jeu d'un joueur avec les chevalets actuels et précédents
 */
typedef struct {
	int nb[NB_TABLEAU];
	char jeu_actuel[MAX_CHEVALETS];
	char jeu_precedent[MAX_CHEVALETS];
} jeu;

/**
 * Structure représentant une liste noire des indices de lettres déjà comptabilisés
 */
typedef struct {
	int nb;
	int list[TAILLE_MOT_MAX];
} black_list;

/**
 * Initialise une liste noire vide
 *
 * @param[out] bl Liste noire à initialiser
 */
void init_bl(black_list* bl);

/**
 * Récupère la taille actuelle du jeu
 *
 * @param[in] j Le jeu pour lequel la taille est demandée
 *
 * @return La taille actuelle du jeu
 */
int taille_jeu_actuel(const jeu* j);

/**
 * Initialisation d'un jeu avec une capacité initiale
 *
 * @param[out] j Le jeu à initialiser
 * @pre Le jeu doit être vide avant l'appel de cette fonction
 */
void init_jeu(jeu* j); // la capacité initiale (12), le nb pour les 2 cases est nul et correspond à la taille des 2 jeux

/**
 * Vérifie si le paquet est vide
 *
 * @param[in] j Le jeu à vérifier
 *
 * @return 1 si le paquet est vide, 0 sinon
 */
int paquet_vide(const jeu* j);

/**
 * Remplissage du paquet avec des chevalets de la pioche
 *
 * @param[in,out] j Le jeu à remplir avec des chevalets
 * @param[in] p La pioche contenant les chevalets à distribuer
 */
void remplir_paquet(jeu* j, pioche* p); // autant que sa capacité

/**
 * Trie les chevalets du jeu par ordre alphabétique
 *
 * @param[in,out] j Le jeu dont les chevalets doivent être triés
 */
void trie_alphabetique(jeu* j);

/**
 * Affiche le jeu actuel d'un joueur
 *
 * @param[in] j Le jeu à afficher
 * @param[in] jnb Le numéro du joueur
 */
void affichage_jeu(const jeu* j, int jnb);

/**
 * Affiche le jeu précédent d'un joueur
 *
 * @param[in] j Le jeu à afficher
 * @param[in] jnb Le numéro du joueur
 */
void affichage_jeu_precedent(const jeu* j, int jnb);

/**
 * Distribue un chevalet à partir de la pioche
 *
 * @param[in,out] p La pioche d'où le chevalet est distribué
 * @param[in] i L'indice du chevalet à distribuer
 *
 * @return Le chevalet distribué
 */
char distribuer_chevalet(pioche* p, int i);

/**
 * Ajoute un chevalet au jeu du joueur
 *
 * @param[in,out] j Le jeu auquel le chevalet est ajouté
 * @param[in] che Le chevalet à ajouter
 */
void recevoir_chevalet(jeu* j, char che);

/**
 * Joue un chevalet du jeu du joueur
 *
 * @param[in,out] j Le jeu du joueur
 * @param[in] che Le chevalet joué
 *
 * @return Le chevalet joué
 */
char jouer_chevalet(jeu* j, char che);

/**
 * Sauvegarde le jeu actuel du joueur
 *
 * @param[in,out] j Le jeu à sauvegarder
 */
void save_jeu(jeu* j);

/**
 * Vérifie si un mot est jouable avec les chevalets du joueur
 *
 * @param[in] j Le jeu du joueur
 * @param[in] che Le mot à tester
 *
 * @return 1 si le mot est jouable, -1 sinon
 */
int jouable(jeu* j, char* che);

/**
 * Vérifie si un mot est jouable à partir du jeu précédent d'un autre joueur
 *
 * @param[in] j_autre Le jeu du joueur adverse
 * @param[in] che Le mot à tester
 *
 * @return 1 si le mot est jouable, -1 sinon
 */
int precedent_jouable(jeu* j_autre, char* che);

/**
 * @brief Modifie la taille du jeu actuel.
 *
 * @param[out] j Le jeu à modifier.
 * @param[in] taille La nouvelle taille du jeu.
 */
void modif_j_taille_jeu(jeu* j, int taille);

/**
 * @brief Modifie la taille du jeu précédent.
 *
 * @param[out] j Le jeu à modifier.
 * @param[in] taille La nouvelle taille du jeu précédent.
 */
void modif_j_taille_jeu_precedent(jeu* j, int taille);

/**
 * @brief Ajoute un chevalet au jeu actuel.
 *
 * @param[out] j Le jeu auquel le chevalet est ajouté.
 * @param[in] che Le chevalet à ajouter.
 */
void ajouter_che(jeu* j, char che);

/**
 * @brief Ajoute un chevalet au jeu précédent.
 *
 * @param[out] j Le jeu auquel le chevalet est ajouté.
 * @param[in] ind L'indice où le chevalet doit être ajouté.
 * @param[in] che Le chevalet à ajouter.
 */
void ajouter_che_precedent(jeu* j, int ind, char che);

/**
 * @brief Sélectionne un chevalet dans le jeu actuel.
 *
 * @param[in] j Le jeu dans lequel sélectionner le chevalet.
 * @param[in] indice L'indice du chevalet à sélectionner.
 *
 * @return Le chevalet sélectionné.
 */
char selec_che_j_actuel(const jeu* j, int indice);

/**
 * @brief Sélectionne un chevalet dans le jeu précédent.
 *
 * @param[in] j Le jeu dans lequel sélectionner le chevalet.
 * @param[in] indice L'indice du chevalet à sélectionner.
 *
 * @return Le chevalet sélectionné.
 */
char selec_che_j_precendent(const jeu* j, int indice);

/**
 * @brief Remplace un chevalet dans le jeu actuel.
 *
 * @param[out] j Le jeu dans lequel le remplacement est effectué.
 * @param[in] indice L'indice du chevalet à remplacer.
 * @param[in] che Le nouveau chevalet.
 */
void remp_che_j_actuel(jeu* j, int indice, char che);

/**
 * @brief Décrémente la taille du jeu actuel.
 *
 * @param[out] j Le jeu dont la taille doit être décrémentée.
 */
void decr_j_actuel(jeu* j);

/**
 * @brief Ajoute un indice à la liste noire.
 *
 * @param[out] bl La liste noire à modifier.
 * @param[in] n L'indice à ajouter.
 */
void ajouter_ele_bl(black_list* bl, int n);

/**
 * @brief Trouve l'indice d'un chevalet dans le jeu actuel.
 *
 * @param[in] j Le jeu à analyser.
 * @param[in] che Le chevalet à rechercher.
 *
 * @return L'indice du chevalet, ou `PAS_JOUABLE` si non trouvé.
 */
int indice_chevalet_paquet(jeu* j, char che);

/**
 * @brief Retourne la taille du jeu précédent.
 *
 * @param[in] j Le jeu à analyser.
 *
 * @return La taille du jeu précédent.
 */
int taille_jeu_precent(const jeu* j);

/**
 * @brief Sélectionne un élément de la liste noire.
 *
 * @param[in] bl La liste noire à analyser.
 * @param[in] indice L'indice de l'élément à sélectionner.
 *
 * @return L'élément sélectionné.
 */
int selec_ele_bl(black_list* bl, int indice);

/**
 * @brief Vérifie si un indice est déjà comptabilisé dans la liste noire.
 *
 * @param[in] indice L'indice à vérifier.
 * @param[in] bl La liste noire à analyser.
 *
 * @return 1 si l'indice est comptabilisé, 0 sinon.
 */
int deja_comptabiliser(int indice, const black_list* bl);

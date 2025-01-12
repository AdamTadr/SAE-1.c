/**
 * @file rail.h
 * @brief Déclaration des fonctions et structures pour gérer le rail et la partie
 */


#pragma once
#include "dictionnaire.h"
#pragma warning(disable:4996)

typedef enum { FAUX, VRAI }bool;

enum { TAILLE_RAIL = 9, MOT_DEPART = 5, MOT_TEST_MAX =50, PAS_ENCORE_JOUE = 0, JOUEUR_1 = 1, JOUEUR_2 = 2, RANG_PREM_L = 0
};

typedef struct {
    char recto[TAILLE_RAIL];
    char verso[TAILLE_RAIL];
    char ancien_recto[TAILLE_RAIL];
    char ancien_verso[TAILLE_RAIL];
    int t_drn_mot_joue;
} rail;

/**
 * @brief Initialise le rail
 *
 * Met à zéro l'état du rail et réinitialise les variables liées au mot joué
 *
 * @param r Rail à initialiser
 */
void init_rail(rail* r);

/**
 * @brief Initialise la partie
 *
 * Demande aux joueurs leurs mots de départ et les place sur le rail
 *
 * @param dico Dictionnaire pour valider les mots
 * @param p Pioche (non utilisé ici)
 * @param j1 Joueur 1
 * @param j2 Joueur 2
 * @param r Rail sur lequel les mots sont placés
 * @return Le joueur qui commence
 */
int init_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r);

/**
 * @brief Valide le mot de départ d'un joueur
 *
 * Vérifie si le mot est valide en longueur, existence dans le dictionnaire et jouable
 *
 * @param dico Dictionnaire pour valider le mot
 * @param mot Mot à valider
 * @param joueur Joueur qui propose le mot
 * @return 0 si le mot n'est pas jouable, 1 sinon
 */
int depart_valide(dictionnaire* dico, const char* mot, jeu* joueur);

/**
 * @brief Demande à un joueur de fournir son mot de départ
 *
 * Répète la demande tant que le mot proposé n'est pas valide
 *
 * @param dico Dictionnaire pour valider le mot
 * @param j Joueur qui doit proposer un mot
 * @param mot Mot proposé par le joueur
 * @param nbj Numéro du joueur
 */
void demander_mot_depart(dictionnaire* dico, jeu* j, char* mot, int nbj);

/**
 * @brief Place les mots de départ sur le rail
 *
 * Place les mots sur le rail en fonction de leur ordre lexicographique
 *
 * @param j1 Joueur 1
 * @param j2 Joueur 2
 * @param mot1 Mot du joueur 1
 * @param mot2 Mot du joueur 2
 * @param r Rail sur lequel les mots sont placés
 * @return Le joueur qui commence la partie
 */
int placement_de_depart(jeu* j1, jeu* j2, const char* mot1, const char* mot2, rail* r);

/**
 * @brief Affiche l'état actuel du rail
 *
 * Affiche le contenu des côtés recto et verso du rail
 *
 * @param r Rail à afficher
 */
void affiche_rail(const rail* r);

/**
 * @brief Copie le côté recto dans le côté verso du rail
 *
 * Inverse le contenu du côté recto pour le placer dans le côté verso
 *
 * @param r Rail dont les côtés recto et verso sont modifiés
 */
void copie_recto_verso(rail* r);

/**
 * @brief Copie le côté verso dans le côté recto du rail
 *
 * Inverse le contenu du côté verso pour le placer dans le côté recto
 *
 * @param r Rail dont les côtés recto et verso sont modifiés
 */
void copie_verso_recto(rail* r);

/**
 * @brief Copie l'ancien verso dans l'ancien recto
 *
 * Sauvegarde l'état précédent du verso dans l'ancien recto
 *
 * @param r Rail dont les côtés sont modifiés
 */
void copie_averso_arecto(rail* r);

/**
 * @brief Copie l'ancien recto dans l'ancien verso
 *
 * Sauvegarde l'état précédent du recto dans l'ancien verso
 *
 * @param r Rail dont les côtés sont modifiés
 */
void copie_arecto_averso(rail* r);

/**
 * @brief Sauvegarde l'état actuel du rail
 *
 * Sauvegarde l'état du recto ou du verso selon le côté spécifié
 *
 * @param r Rail à sauvegarder
 * @param cote Côté du rail à sauvegarder ('R' pour recto, 'V' pour verso)
 */
void save_rail(rail* r);

/**
 * @brief Ajoute un caractère au recto du rail.
 *
 * @param r Rail où le caractère doit être ajouté.
 * @param indice Indice du caractère à ajouter.
 * @param che Caractère à ajouter.
 */
void ajouter_rail_recto(rail* r, int indice, char che);

/**
 * @brief Ajoute un caractère au verso du rail.
 *
 * @param r Rail où le caractère doit être ajouté.
 * @param indice Indice du caractère à ajouter.
 * @param che Caractère à ajouter.
 */
void ajouter_rail_verso(rail* r, int indice, char che);

/**
 * @brief Ajoute un caractère à l'ancien recto du rail.
 *
 * @param r Rail où le caractère doit être ajouté.
 * @param indice Indice du caractère à ajouter.
 * @param che Caractère à ajouter.
 */
void ajouter_rail_arecto(rail* r, int indice, char che);

/**
 * @brief Ajoute un caractère à l'ancien verso du rail.
 *
 * @param r Rail où le caractère doit être ajouté.
 * @param indice Indice du caractère à ajouter.
 * @param che Caractère à ajouter.
 */
void ajouter_rail_averso(rail* r, int indice, char che);

/**
 * @brief Obtient la valeur du recto à un indice donné.
 *
 * @param r Rail d'où la valeur doit être obtenue.
 * @param indice Indice de la valeur à obtenir.
 * @return La valeur du recto à l'indice spécifié.
 */

char valeur_rail_recto(const rail* r, int indice);

/**
 * @brief Obtient la valeur du verso à un indice donné.
 *
 * @param r Rail d'où la valeur doit être obtenue.
 * @param indice Indice de la valeur à obtenir.
 * @return La valeur du verso à l'indice spécifié.
 */
char valeur_rail_verso(const rail* r, int indice);

/**
 * @brief Obtient la valeur de l'ancien recto à un indice donné.
 *
 * @param r Rail d'où la valeur doit être obtenue.
 * @param indice Indice de la valeur à obtenir.
 * @return La valeur de l'ancien recto à l'indice spécifié.
 */
char valeur_rail_arecto(const rail* r, int indice);

/**
 * @brief Obtient la valeur de l'ancien verso à un indice donné.
 *
 * @param r Rail d'où la valeur doit être obtenue.
 * @param indice Indice de la valeur à obtenir.
 * @return La valeur de l'ancien verso à l'indice spécifié.
 */
char valeur_rail_averso(const rail* r, int indice);

/**
 * @brief Récupère la valeur du nombre de tours du mot joué.
 *
 * @param r Rail dont la valeur doit être récupérée.
 * @return La valeur de `t_drn_mot_joue`.
 */
int valeur_t_drn_mot_joue(const rail* r);

/**
 * @brief Modifie la valeur du nombre de tours du mot joué.
 *
 * @param r Rail où la valeur doit être modifiée.
 * @param n Nouvelle valeur à affecter.
 */
void modif_t_drn_mot_joue(rail* r, int n);

/**
 * @brief Change le numéro du mot joué sur le rail.
 *
 * @param r Pointeur vers la structure du rail.
 * @param n Le nouveau numéro du mot joué.
 */
void changer_t_dnr_mot_joue(rail* r, int n);

/**
 * @brief Vérifie si le mot peut être placé sur le rail au début d'une position donnée.
 *
 * @param mot Le mot à vérifier.
 * @param r Pointeur vers la structure du rail.
 * @param lettres_parenthese Lettres entre parenthèses dans le rail.
 * @param indice_ferm Indice de fermeture.
 * @param indice_ouv Indice d'ouverture.
 * @param taille_mot La taille du mot à vérifier.
 * @param cote Le côté (recto ou verso) à vérifier.
 * @return 1 si le mot peut être placé, 0 sinon.
 */
int t_drn_mot_joue(rail* r);

/**
 * @brief Modifie un caractère du côté recto du rail à l'indice spécifié.
 *
 * @param r Pointeur vers la structure du rail.
 * @param indice L'indice du caractère à modifier.
 * @param che Le nouveau caractère à assigner.
 */
void mod_r_recto(rail* r, int indice, char che);

/**
 * @brief Modifie un caractère du côté verso du rail à l'indice spécifié.
 *
 * @param r Pointeur vers la structure du rail.
 * @param indice L'indice du caractère à modifier.
 * @param che Le nouveau caractère à assigner.
 */
void mod_r_verso(rail* r, int indice, char che);

/**
 * @brief Sélectionne un caractère du côté recto du rail à l'indice spécifié.
 *
 * @param r Pointeur vers la structure du rail.
 * @param indice L'indice du caractère à récupérer.
 * @return Le caractère du côté recto du rail à l'indice spécifié.
 */
char selec_rail_recto(rail* r, int indice);

/**
 * @brief Sélectionne un caractère du côté verso du rail à l'indice spécifié.
 *
 * @param r Pointeur vers la structure du rail.
 * @param indice L'indice du caractère à récupérer.
 * @return Le caractère du côté verso du rail à l'indice spécifié.
 */
char selec_rail_verso(rail* r, int indice);

/**
 * @brief Sort une lettre du chevalet à droite
 *
 * Extrait une lettre du chevalet à droite en fonction de la taille du mot à jouer.
 *
 * @param[in] r Rail des mots joués
 * @param[in] cote Côté du rail (recto ou verso)
 * @param[in] taille_mot Taille du mot à jouer
 * @return Lettre extraite du chevalet
 */
char sortir_chevalet_droite(rail* r, char cote, int taille_mot);

/**
 * @brief Sort une lettre du chevalet à gauche
 *
 * Extrait une lettre du chevalet à gauche en fonction de la taille du mot à jouer.
 *
 * @param[in] r Rail des mots joués
 * @param[in] cote Côté du rail (recto ou verso)
 * @param[in] taille_mot Taille du mot à jouer
 * @return Lettre extraite du chevalet
 */
char sortir_chevalet_gauche(rail* r, char cote, int taille_mot);

/**
 * @brief Insère une lettre dans le chevalet à droite
 * 
 * Insère une lettre dans le chevalet à droite en fonction du côté du rail.
 * 
 * @param[in] r Rail des mots joués
 * @param[in] che Lettre à insérer
 * @param[in] cote Côté du rail (recto ou verso)
 */
void inserer_chevalet_droite(rail* r, char che, char cote);

/**
 * @brief Insère une lettre dans le chevalet à gauche
 *
 * Insère une lettre dans le chevalet à gauche en fonction du côté du rail.
 *
 * @param[in] r Rail des mots joués
 * @param[in] che Lettre à insérer
 * @param[in] cote Côté du rail (recto ou verso)
 */
void inserer_chevalet_gauche(rail* r, char che, char cote);


char* rail_recto(rail* r);
char* rail_arecto(rail* r);
char* rail_verso(rail* r);
char* rail_averso(rail* r);
#pragma once
#include "rail.h"

/**
 * @brief Statut de la partie
 *
 * @enum représentant l'état actuel du jeu Octo Verso.
 */
typedef enum {
    TOUR_J1 = 1, /**< Tour du joueur 1 */
    TOUR_J1_OCTO = -1, /**< Tour du joueur 1 avec la condition Octo */
    TOUR_J2 = 2, /**< Tour du joueur 2 */
    TOUR_J2_OCTO = -2, /**< Tour du joueur 2 avec la condition Octo */
    FINI = 0 /**< Partie terminée */
} statut_partie;

enum{ L_MAX_PARENTH= 7, L_MAX_H_PARENTH = 8, PAS_ASSEZ_ENTRE= 1, TAILLE_LETTRE = 1, UN_MOT= 1, P_FIN_MIN = 3 };





/**
 * @brief Joue une partie d'Octo Verso
 *
 * Gère les tours des joueurs et vérifie la fin de la partie dans Octo Verso.
 *
 * @param[in] dico Dictionnaire des mots valides
 * @param[in] p Pioche des lettres
 * @param[in] j1 Premier joueur
 * @param[in] j2 Deuxième joueur
 * @param[in] r Rail des mots joués
 * @param[in] joueur_actuel Joueur dont c'est le tour
 * @return Statut de la partie après le tour
 */
int jouer_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r, statut_partie joueur_actuel);

/**
 * @brief Demande un mot à un joueur et le valide
 *
 * Le joueur entre un mot qui est validé. Si valide, il est joué. Sinon, une nouvelle tentative est demandée.
 *
 * @param[in] dico Dictionnaire des mots valides
 * @param[in] p Pioche des lettres
 * @param[in] j Joueur qui propose le mot
 * @param[in] j_autre L'autre joueur
 * @param[out] mot Mot proposé par le joueur
 * @param[in] nbj Numéro du joueur
 * @param[in] r Rail des mots joués
 * @param[in] joueur_actuel Joueur dont c'est le tour
 * @return Statut de la partie après l'action du joueur
 */
statut_partie demander_mot(dictionnaire* dico, pioche* p, jeu* j, jeu* j_autre, char* mot, int nbj, rail* r, statut_partie joueur_actuel);

/**
 * @brief Joue un mot sur le rail
 *
 * Joue un mot sur le rail en fonction de sa position, de son format et des lettres utilisées dans Octo Verso.
 *
 * @param[in] j Joueur qui joue
 * @param[in] j_autre L'autre joueur
 * @param[in] r Rail des mots joués
 * @param[in] dico Dictionnaire des mots valides
 * @param[in] mot Mot joué
 * @param[in] lettre_parenthese Lettre à insérer dans la parenthèse
 * @param[in] lettre_hors_p Lettre à insérer hors parenthèse
 * @param[in] cote Côté du rail (recto ou verso)
 * @param[in] joueur_actuel Joueur dont c'est le tour
 */
void jouer_mot(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico, char* mot, char* lettre_parenthese, char* lettre_hors_p, char cote, statut_partie joueur_actuel);





/**
 * @brief Vérifie le format du mot avec les parenthèses
 *
 * Vérifie que le mot proposé respecte le format avec les parenthèses dans Octo Verso.
 *
 * @param[in] mot Mot à vérifier
 * @param[out] indice_ouv Indice de la parenthèse ouvrante
 * @param[out] indice_ferm Indice de la parenthèse fermante
 * @return Résultat de la vérification
 */
int verif_format_mot(char* mot, int* indice_ouv, int* indice_ferm);



/**
 * @brief Effectue une tentative de placement du mot
 *
 * Tente de placer un mot sur le rail en fonction de sa position et de sa validité.
 *
 * @param[in] j Joueur qui tente de placer le mot
 * @param[in] j_autre L'autre joueur
 * @param[in] r Rail des mots joués
 * @param[in] dico Dictionnaire des mots valides
 * @param[in] mot Mot à jouer
 * @param[in] cote Côté du rail (recto ou verso)
 * @param[in] joueur_actuel Joueur dont c'est le tour
 * @return Statut de la partie après la tentative
 */
int tentative(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico, char* mot, char cote, statut_partie joueur_actuel);


/**
 * @brief Initialise un mot avant de le jouer
 *
 * Prépare un mot en enlevant les parenthèses et en séparant les lettres hors et dans les parenthèses.
 *
 * @param[out] mot Mot à initialiser
 * @param[out] mot_sans_parenthese Mot sans parenthèses
 * @param[out] lettres_hors_parenthese Lettres hors des parenthèses
 * @param[out] lettre_parenthese Lettres dans les parenthèses
 * @param[in] cote Côté du rail (recto ou verso)
 * @param[in] j Joueur qui joue
 * @param[in] r Rail des mots joués
 * @return Résultat de l'initialisation
 */
int init_mot(char* mot, char* mot_sans_parenthese, char* lettres_hors_parenthese, char* lettre_parenthese, char cote, jeu* j, rail* r);



/**
 * @brief Supprime les parenthèses du mot
 *
 * Retire les parenthèses et déplace les lettres dans et hors parenthèses.
 *
 * @param[in] mot Mot à traiter
 * @param[out] lettre_parenthese Lettres dans les parenthèses
 * @param[out] lettre_hors_parenthese Lettres hors des parenthèses
 * @param[out] mot_sans_parenthese Mot sans les parenthèses
 */
void supprime_parenthese(char* mot, char* lettre_parenthese, char* lettre_hors_parenthese, char* mot_sans_parenthese);


/**
 * @brief Vérifie si la lettre jouée est valide
 *
 * Vérifie si la lettre peut être jouée sur le rail dans la position spécifiée.
 *
 * @param[in] r Rail des mots joués
 * @param[in] j Joueur qui joue
 * @param[in] mot Mot joué
 * @param[in] lettres_hors_parenthese Lettres hors des parenthèses
 * @param[in] lettres_parenthese Lettres dans les parenthèses
 * @param[in] cote Côté du rail (recto ou verso)
 * @param[in] indice_ouv Indice de la parenthèse ouvrante
 * @param[in] indice_ferm Indice de la parenthèse fermante
 * @return Résultat de la vérification
 */
int lettre_joue_valide(rail* r, jeu* j, char* mot, char* lettres_hors_parenthese, char* lettres_parenthese, char cote, int indice_ouv, int indice_ferm);




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
int verif_debut(char* mot, rail* r, char* lettres_parenthese, int indice_ferm, int indice_ouv, int taille_mot, char cote);

/**
 * @brief Vérifie si le mot peut être placé sur le rail à la fin d'une position donnée.
 *
 * @param mot Le mot à vérifier.
 * @param r Pointeur vers la structure du rail.
 * @param lettres_parenthese Lettres entre parenthèses dans le rail.
 * @param indice_ouv Indice d'ouverture.
 * @param indice_ferm Indice de fermeture.
 * @param taille_mot La taille du mot à vérifier.
 * @param cote Le côté (recto ou verso) à vérifier.
 * @return 1 si le mot peut être placé, 0 sinon.
 */
int verif_fin(char* mot, rail* r, char* lettres_parenthese, int indice_ouv,int indice_ferm, int taille_mot, char cote);



/**
 * @brief Vérifie si le mot peut être placé au début sur le côté recto du rail.
 *
 * @param mot Le mot à vérifier.
 * @param rail_recto Le côté recto du rail.
 * @param lettres_parenthese Lettres entre parenthèses dans le rail.
 * @param indice_ferm Indice de fermeture.
 * @param indice_ouv Indice d'ouverture.
 * @param taille_mot La taille du mot à vérifier.
 * @return 1 si le mot peut être placé, 0 sinon.
 */
int verif_Recto_debut(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ferm, int indice_ouv, int taille_mot);

/**
 * @brief Vérifie si le mot peut être placé à la fin sur le côté recto du rail.
 *
 * @param mot Le mot à vérifier.
 * @param rail_recto Le côté recto du rail.
 * @param lettres_parenthese Lettres entre parenthèses dans le rail.
 * @param indice_ouv Indice d'ouverture.
 * @param indice_ferm Indice de fermeture.
 * @param taille_mot La taille du mot à vérifier.
 * @return 1 si le mot peut être placé, 0 sinon.
 */
int verif_Recto_fin(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ouv, int indice_ferm, int taille_mot);

/**
 * @brief Vérifie si le mot peut être placé au début sur le côté verso du rail.
 *
 * @param mot Le mot à vérifier.
 * @param rail_verso Le côté verso du rail.
 * @param lettres_parenthese Lettres entre parenthèses dans le rail.
 * @param indice_ferm Indice de fermeture.
 * @param indice_ouv Indice d'ouverture.
 * @param taille_mot La taille du mot à vérifier.
 * @return 1 si le mot peut être placé, 0 sinon.
 */
int verif_Verso_debut(char* mot, char* rail_verso, char* lettres_parenthese, int indice_ferm,int indice_ouv, int taille_mot);

/**
 * @brief Vérifie si le mot peut être placé à la fin sur le côté verso du rail.
 *
 * @param mot Le mot à vérifier.
 * @param rail_verso Le côté verso du rail.
 * @param lettres_parenthese Lettres entre parenthèses dans le rail.
 * @param indice_ouv Indice d'ouverture.
 * @param indice_ferm Indice de fermeture.
 * @param taille_mot La taille du mot à vérifier.
 * @return 1 si le mot peut être placé, 0 sinon.
 */
int verif_Verso_fin(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ouv, int indice_ferm, int taille_mot);


/**
 * @brief Vérifie si une lettre est valide à placer sur le rail.
 *
 * @param r Pointeur vers la structure du rail.
 * @param mot Le mot à vérifier.
 * @param lettres_hors_parenthese Lettres hors parenthèses dans le rail.
 * @param lettres_parenthese Lettres entre parenthèses dans le rail.
 * @param cote Le côté (recto ou verso) à vérifier.
 * @param j Pointeur vers la structure du jeu.
 * @param indice_ouv Indice d'ouverture.
 * @param indice_ferm Indice de fermeture.
 * @return 1 si la lettre est valide, 0 sinon.
 */
int lettre_rail_valide(rail* r, char* mot, char* lettres_hors_parenthese, char* lettres_parenthese, char cote, jeu* j, int indice_ouv, int indice_ferm);

/**
 * @brief Permet de jouer une lettre de son jeu quand on fait un octo
 * @param j le joueur ayant fait un octo
 * @param j_autre le joueur qui recevra une lettre suplémentaire
 * @param joueur_actuel le numéro du joueur (j) qui joue
 * @return 1 si le coup a réussi, 0 sinon.
 */
int octo_chevalet(jeu* j, jeu* j_autre,rail *r, statut_partie joueur_actuel);


/**
 * @brief Échange une lettre du chevalet du joueur avec une lettre de la pioche.
 *
 * @param p Pointeur vers la structure de la pioche.
 * @param j Pointeur vers la structure du jeu.
 * @param chevalet La lettre du chevalet à échanger.
 * @return 1 si l'échange a réussi, 0 sinon.
 */
int echanger_chevalet(pioche* p, jeu* j, char che);


/**
 * @brief Affiche les informations des deux joueurs et du rail.
 *
 * @param j1 Pointeur vers la structure du joueur 1.
 * @param j2 Pointeur vers la structure du joueur 2.
 * @param r Pointeur vers la structure du rail.
 */
void affichage_tour(jeu* j1, jeu* j2, rail* r);


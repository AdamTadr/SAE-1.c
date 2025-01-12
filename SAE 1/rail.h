/**
 * @file rail.h
 * @brief D�claration des fonctions et structures pour g�rer le rail et la partie
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
 * Met � z�ro l'�tat du rail et r�initialise les variables li�es au mot jou�
 *
 * @param r Rail � initialiser
 */
void init_rail(rail* r);

/**
 * @brief Initialise la partie
 *
 * Demande aux joueurs leurs mots de d�part et les place sur le rail
 *
 * @param dico Dictionnaire pour valider les mots
 * @param p Pioche (non utilis� ici)
 * @param j1 Joueur 1
 * @param j2 Joueur 2
 * @param r Rail sur lequel les mots sont plac�s
 * @return Le joueur qui commence
 */
int init_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r);

/**
 * @brief Valide le mot de d�part d'un joueur
 *
 * V�rifie si le mot est valide en longueur, existence dans le dictionnaire et jouable
 *
 * @param dico Dictionnaire pour valider le mot
 * @param mot Mot � valider
 * @param joueur Joueur qui propose le mot
 * @return 0 si le mot n'est pas jouable, 1 sinon
 */
int depart_valide(dictionnaire* dico, const char* mot, jeu* joueur);

/**
 * @brief Demande � un joueur de fournir son mot de d�part
 *
 * R�p�te la demande tant que le mot propos� n'est pas valide
 *
 * @param dico Dictionnaire pour valider le mot
 * @param j Joueur qui doit proposer un mot
 * @param mot Mot propos� par le joueur
 * @param nbj Num�ro du joueur
 */
void demander_mot_depart(dictionnaire* dico, jeu* j, char* mot, int nbj);

/**
 * @brief Place les mots de d�part sur le rail
 *
 * Place les mots sur le rail en fonction de leur ordre lexicographique
 *
 * @param j1 Joueur 1
 * @param j2 Joueur 2
 * @param mot1 Mot du joueur 1
 * @param mot2 Mot du joueur 2
 * @param r Rail sur lequel les mots sont plac�s
 * @return Le joueur qui commence la partie
 */
int placement_de_depart(jeu* j1, jeu* j2, const char* mot1, const char* mot2, rail* r);

/**
 * @brief Affiche l'�tat actuel du rail
 *
 * Affiche le contenu des c�t�s recto et verso du rail
 *
 * @param r Rail � afficher
 */
void affiche_rail(const rail* r);

/**
 * @brief Copie le c�t� recto dans le c�t� verso du rail
 *
 * Inverse le contenu du c�t� recto pour le placer dans le c�t� verso
 *
 * @param r Rail dont les c�t�s recto et verso sont modifi�s
 */
void copie_recto_verso(rail* r);

/**
 * @brief Copie le c�t� verso dans le c�t� recto du rail
 *
 * Inverse le contenu du c�t� verso pour le placer dans le c�t� recto
 *
 * @param r Rail dont les c�t�s recto et verso sont modifi�s
 */
void copie_verso_recto(rail* r);

/**
 * @brief Copie l'ancien verso dans l'ancien recto
 *
 * Sauvegarde l'�tat pr�c�dent du verso dans l'ancien recto
 *
 * @param r Rail dont les c�t�s sont modifi�s
 */
void copie_averso_arecto(rail* r);

/**
 * @brief Copie l'ancien recto dans l'ancien verso
 *
 * Sauvegarde l'�tat pr�c�dent du recto dans l'ancien verso
 *
 * @param r Rail dont les c�t�s sont modifi�s
 */
void copie_arecto_averso(rail* r);

/**
 * @brief Sauvegarde l'�tat actuel du rail
 *
 * Sauvegarde l'�tat du recto ou du verso selon le c�t� sp�cifi�
 *
 * @param r Rail � sauvegarder
 * @param cote C�t� du rail � sauvegarder ('R' pour recto, 'V' pour verso)
 */
void save_rail(rail* r);

/**
 * @brief Ajoute un caract�re au recto du rail.
 *
 * @param r Rail o� le caract�re doit �tre ajout�.
 * @param indice Indice du caract�re � ajouter.
 * @param che Caract�re � ajouter.
 */
void ajouter_rail_recto(rail* r, int indice, char che);

/**
 * @brief Ajoute un caract�re au verso du rail.
 *
 * @param r Rail o� le caract�re doit �tre ajout�.
 * @param indice Indice du caract�re � ajouter.
 * @param che Caract�re � ajouter.
 */
void ajouter_rail_verso(rail* r, int indice, char che);

/**
 * @brief Ajoute un caract�re � l'ancien recto du rail.
 *
 * @param r Rail o� le caract�re doit �tre ajout�.
 * @param indice Indice du caract�re � ajouter.
 * @param che Caract�re � ajouter.
 */
void ajouter_rail_arecto(rail* r, int indice, char che);

/**
 * @brief Ajoute un caract�re � l'ancien verso du rail.
 *
 * @param r Rail o� le caract�re doit �tre ajout�.
 * @param indice Indice du caract�re � ajouter.
 * @param che Caract�re � ajouter.
 */
void ajouter_rail_averso(rail* r, int indice, char che);

/**
 * @brief Obtient la valeur du recto � un indice donn�.
 *
 * @param r Rail d'o� la valeur doit �tre obtenue.
 * @param indice Indice de la valeur � obtenir.
 * @return La valeur du recto � l'indice sp�cifi�.
 */

char valeur_rail_recto(const rail* r, int indice);

/**
 * @brief Obtient la valeur du verso � un indice donn�.
 *
 * @param r Rail d'o� la valeur doit �tre obtenue.
 * @param indice Indice de la valeur � obtenir.
 * @return La valeur du verso � l'indice sp�cifi�.
 */
char valeur_rail_verso(const rail* r, int indice);

/**
 * @brief Obtient la valeur de l'ancien recto � un indice donn�.
 *
 * @param r Rail d'o� la valeur doit �tre obtenue.
 * @param indice Indice de la valeur � obtenir.
 * @return La valeur de l'ancien recto � l'indice sp�cifi�.
 */
char valeur_rail_arecto(const rail* r, int indice);

/**
 * @brief Obtient la valeur de l'ancien verso � un indice donn�.
 *
 * @param r Rail d'o� la valeur doit �tre obtenue.
 * @param indice Indice de la valeur � obtenir.
 * @return La valeur de l'ancien verso � l'indice sp�cifi�.
 */
char valeur_rail_averso(const rail* r, int indice);

/**
 * @brief R�cup�re la valeur du nombre de tours du mot jou�.
 *
 * @param r Rail dont la valeur doit �tre r�cup�r�e.
 * @return La valeur de `t_drn_mot_joue`.
 */
int valeur_t_drn_mot_joue(const rail* r);

/**
 * @brief Modifie la valeur du nombre de tours du mot jou�.
 *
 * @param r Rail o� la valeur doit �tre modifi�e.
 * @param n Nouvelle valeur � affecter.
 */
void modif_t_drn_mot_joue(rail* r, int n);

/**
 * @brief Change le num�ro du mot jou� sur le rail.
 *
 * @param r Pointeur vers la structure du rail.
 * @param n Le nouveau num�ro du mot jou�.
 */
void changer_t_dnr_mot_joue(rail* r, int n);

/**
 * @brief V�rifie si le mot peut �tre plac� sur le rail au d�but d'une position donn�e.
 *
 * @param mot Le mot � v�rifier.
 * @param r Pointeur vers la structure du rail.
 * @param lettres_parenthese Lettres entre parenth�ses dans le rail.
 * @param indice_ferm Indice de fermeture.
 * @param indice_ouv Indice d'ouverture.
 * @param taille_mot La taille du mot � v�rifier.
 * @param cote Le c�t� (recto ou verso) � v�rifier.
 * @return 1 si le mot peut �tre plac�, 0 sinon.
 */
int t_drn_mot_joue(rail* r);

/**
 * @brief Modifie un caract�re du c�t� recto du rail � l'indice sp�cifi�.
 *
 * @param r Pointeur vers la structure du rail.
 * @param indice L'indice du caract�re � modifier.
 * @param che Le nouveau caract�re � assigner.
 */
void mod_r_recto(rail* r, int indice, char che);

/**
 * @brief Modifie un caract�re du c�t� verso du rail � l'indice sp�cifi�.
 *
 * @param r Pointeur vers la structure du rail.
 * @param indice L'indice du caract�re � modifier.
 * @param che Le nouveau caract�re � assigner.
 */
void mod_r_verso(rail* r, int indice, char che);

/**
 * @brief S�lectionne un caract�re du c�t� recto du rail � l'indice sp�cifi�.
 *
 * @param r Pointeur vers la structure du rail.
 * @param indice L'indice du caract�re � r�cup�rer.
 * @return Le caract�re du c�t� recto du rail � l'indice sp�cifi�.
 */
char selec_rail_recto(rail* r, int indice);

/**
 * @brief S�lectionne un caract�re du c�t� verso du rail � l'indice sp�cifi�.
 *
 * @param r Pointeur vers la structure du rail.
 * @param indice L'indice du caract�re � r�cup�rer.
 * @return Le caract�re du c�t� verso du rail � l'indice sp�cifi�.
 */
char selec_rail_verso(rail* r, int indice);

/**
 * @brief Sort une lettre du chevalet � droite
 *
 * Extrait une lettre du chevalet � droite en fonction de la taille du mot � jouer.
 *
 * @param[in] r Rail des mots jou�s
 * @param[in] cote C�t� du rail (recto ou verso)
 * @param[in] taille_mot Taille du mot � jouer
 * @return Lettre extraite du chevalet
 */
char sortir_chevalet_droite(rail* r, char cote, int taille_mot);

/**
 * @brief Sort une lettre du chevalet � gauche
 *
 * Extrait une lettre du chevalet � gauche en fonction de la taille du mot � jouer.
 *
 * @param[in] r Rail des mots jou�s
 * @param[in] cote C�t� du rail (recto ou verso)
 * @param[in] taille_mot Taille du mot � jouer
 * @return Lettre extraite du chevalet
 */
char sortir_chevalet_gauche(rail* r, char cote, int taille_mot);

/**
 * @brief Ins�re une lettre dans le chevalet � droite
 * 
 * Ins�re une lettre dans le chevalet � droite en fonction du c�t� du rail.
 * 
 * @param[in] r Rail des mots jou�s
 * @param[in] che Lettre � ins�rer
 * @param[in] cote C�t� du rail (recto ou verso)
 */
void inserer_chevalet_droite(rail* r, char che, char cote);

/**
 * @brief Ins�re une lettre dans le chevalet � gauche
 *
 * Ins�re une lettre dans le chevalet � gauche en fonction du c�t� du rail.
 *
 * @param[in] r Rail des mots jou�s
 * @param[in] che Lettre � ins�rer
 * @param[in] cote C�t� du rail (recto ou verso)
 */
void inserer_chevalet_gauche(rail* r, char che, char cote);


char* rail_recto(rail* r);
char* rail_arecto(rail* r);
char* rail_verso(rail* r);
char* rail_averso(rail* r);
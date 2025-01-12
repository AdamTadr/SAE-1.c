#pragma once
#include "rail.h"

/**
 * @brief Statut de la partie
 *
 * @enum repr�sentant l'�tat actuel du jeu Octo Verso.
 */
typedef enum {
    TOUR_J1 = 1, /**< Tour du joueur 1 */
    TOUR_J1_OCTO = -1, /**< Tour du joueur 1 avec la condition Octo */
    TOUR_J2 = 2, /**< Tour du joueur 2 */
    TOUR_J2_OCTO = -2, /**< Tour du joueur 2 avec la condition Octo */
    FINI = 0 /**< Partie termin�e */
} statut_partie;

enum{ L_MAX_PARENTH= 7, L_MAX_H_PARENTH = 8, PAS_ASSEZ_ENTRE= 1, TAILLE_LETTRE = 1, UN_MOT= 1, P_FIN_MIN = 3 };





/**
 * @brief Joue une partie d'Octo Verso
 *
 * G�re les tours des joueurs et v�rifie la fin de la partie dans Octo Verso.
 *
 * @param[in] dico Dictionnaire des mots valides
 * @param[in] p Pioche des lettres
 * @param[in] j1 Premier joueur
 * @param[in] j2 Deuxi�me joueur
 * @param[in] r Rail des mots jou�s
 * @param[in] joueur_actuel Joueur dont c'est le tour
 * @return Statut de la partie apr�s le tour
 */
int jouer_partie(dictionnaire* dico, pioche* p, jeu* j1, jeu* j2, rail* r, statut_partie joueur_actuel);

/**
 * @brief Demande un mot � un joueur et le valide
 *
 * Le joueur entre un mot qui est valid�. Si valide, il est jou�. Sinon, une nouvelle tentative est demand�e.
 *
 * @param[in] dico Dictionnaire des mots valides
 * @param[in] p Pioche des lettres
 * @param[in] j Joueur qui propose le mot
 * @param[in] j_autre L'autre joueur
 * @param[out] mot Mot propos� par le joueur
 * @param[in] nbj Num�ro du joueur
 * @param[in] r Rail des mots jou�s
 * @param[in] joueur_actuel Joueur dont c'est le tour
 * @return Statut de la partie apr�s l'action du joueur
 */
statut_partie demander_mot(dictionnaire* dico, pioche* p, jeu* j, jeu* j_autre, char* mot, int nbj, rail* r, statut_partie joueur_actuel);

/**
 * @brief Joue un mot sur le rail
 *
 * Joue un mot sur le rail en fonction de sa position, de son format et des lettres utilis�es dans Octo Verso.
 *
 * @param[in] j Joueur qui joue
 * @param[in] j_autre L'autre joueur
 * @param[in] r Rail des mots jou�s
 * @param[in] dico Dictionnaire des mots valides
 * @param[in] mot Mot jou�
 * @param[in] lettre_parenthese Lettre � ins�rer dans la parenth�se
 * @param[in] lettre_hors_p Lettre � ins�rer hors parenth�se
 * @param[in] cote C�t� du rail (recto ou verso)
 * @param[in] joueur_actuel Joueur dont c'est le tour
 */
void jouer_mot(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico, char* mot, char* lettre_parenthese, char* lettre_hors_p, char cote, statut_partie joueur_actuel);





/**
 * @brief V�rifie le format du mot avec les parenth�ses
 *
 * V�rifie que le mot propos� respecte le format avec les parenth�ses dans Octo Verso.
 *
 * @param[in] mot Mot � v�rifier
 * @param[out] indice_ouv Indice de la parenth�se ouvrante
 * @param[out] indice_ferm Indice de la parenth�se fermante
 * @return R�sultat de la v�rification
 */
int verif_format_mot(char* mot, int* indice_ouv, int* indice_ferm);



/**
 * @brief Effectue une tentative de placement du mot
 *
 * Tente de placer un mot sur le rail en fonction de sa position et de sa validit�.
 *
 * @param[in] j Joueur qui tente de placer le mot
 * @param[in] j_autre L'autre joueur
 * @param[in] r Rail des mots jou�s
 * @param[in] dico Dictionnaire des mots valides
 * @param[in] mot Mot � jouer
 * @param[in] cote C�t� du rail (recto ou verso)
 * @param[in] joueur_actuel Joueur dont c'est le tour
 * @return Statut de la partie apr�s la tentative
 */
int tentative(jeu* j, jeu* j_autre, rail* r, dictionnaire* dico, char* mot, char cote, statut_partie joueur_actuel);


/**
 * @brief Initialise un mot avant de le jouer
 *
 * Pr�pare un mot en enlevant les parenth�ses et en s�parant les lettres hors et dans les parenth�ses.
 *
 * @param[out] mot Mot � initialiser
 * @param[out] mot_sans_parenthese Mot sans parenth�ses
 * @param[out] lettres_hors_parenthese Lettres hors des parenth�ses
 * @param[out] lettre_parenthese Lettres dans les parenth�ses
 * @param[in] cote C�t� du rail (recto ou verso)
 * @param[in] j Joueur qui joue
 * @param[in] r Rail des mots jou�s
 * @return R�sultat de l'initialisation
 */
int init_mot(char* mot, char* mot_sans_parenthese, char* lettres_hors_parenthese, char* lettre_parenthese, char cote, jeu* j, rail* r);



/**
 * @brief Supprime les parenth�ses du mot
 *
 * Retire les parenth�ses et d�place les lettres dans et hors parenth�ses.
 *
 * @param[in] mot Mot � traiter
 * @param[out] lettre_parenthese Lettres dans les parenth�ses
 * @param[out] lettre_hors_parenthese Lettres hors des parenth�ses
 * @param[out] mot_sans_parenthese Mot sans les parenth�ses
 */
void supprime_parenthese(char* mot, char* lettre_parenthese, char* lettre_hors_parenthese, char* mot_sans_parenthese);


/**
 * @brief V�rifie si la lettre jou�e est valide
 *
 * V�rifie si la lettre peut �tre jou�e sur le rail dans la position sp�cifi�e.
 *
 * @param[in] r Rail des mots jou�s
 * @param[in] j Joueur qui joue
 * @param[in] mot Mot jou�
 * @param[in] lettres_hors_parenthese Lettres hors des parenth�ses
 * @param[in] lettres_parenthese Lettres dans les parenth�ses
 * @param[in] cote C�t� du rail (recto ou verso)
 * @param[in] indice_ouv Indice de la parenth�se ouvrante
 * @param[in] indice_ferm Indice de la parenth�se fermante
 * @return R�sultat de la v�rification
 */
int lettre_joue_valide(rail* r, jeu* j, char* mot, char* lettres_hors_parenthese, char* lettres_parenthese, char cote, int indice_ouv, int indice_ferm);




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
int verif_debut(char* mot, rail* r, char* lettres_parenthese, int indice_ferm, int indice_ouv, int taille_mot, char cote);

/**
 * @brief V�rifie si le mot peut �tre plac� sur le rail � la fin d'une position donn�e.
 *
 * @param mot Le mot � v�rifier.
 * @param r Pointeur vers la structure du rail.
 * @param lettres_parenthese Lettres entre parenth�ses dans le rail.
 * @param indice_ouv Indice d'ouverture.
 * @param indice_ferm Indice de fermeture.
 * @param taille_mot La taille du mot � v�rifier.
 * @param cote Le c�t� (recto ou verso) � v�rifier.
 * @return 1 si le mot peut �tre plac�, 0 sinon.
 */
int verif_fin(char* mot, rail* r, char* lettres_parenthese, int indice_ouv,int indice_ferm, int taille_mot, char cote);



/**
 * @brief V�rifie si le mot peut �tre plac� au d�but sur le c�t� recto du rail.
 *
 * @param mot Le mot � v�rifier.
 * @param rail_recto Le c�t� recto du rail.
 * @param lettres_parenthese Lettres entre parenth�ses dans le rail.
 * @param indice_ferm Indice de fermeture.
 * @param indice_ouv Indice d'ouverture.
 * @param taille_mot La taille du mot � v�rifier.
 * @return 1 si le mot peut �tre plac�, 0 sinon.
 */
int verif_Recto_debut(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ferm, int indice_ouv, int taille_mot);

/**
 * @brief V�rifie si le mot peut �tre plac� � la fin sur le c�t� recto du rail.
 *
 * @param mot Le mot � v�rifier.
 * @param rail_recto Le c�t� recto du rail.
 * @param lettres_parenthese Lettres entre parenth�ses dans le rail.
 * @param indice_ouv Indice d'ouverture.
 * @param indice_ferm Indice de fermeture.
 * @param taille_mot La taille du mot � v�rifier.
 * @return 1 si le mot peut �tre plac�, 0 sinon.
 */
int verif_Recto_fin(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ouv, int indice_ferm, int taille_mot);

/**
 * @brief V�rifie si le mot peut �tre plac� au d�but sur le c�t� verso du rail.
 *
 * @param mot Le mot � v�rifier.
 * @param rail_verso Le c�t� verso du rail.
 * @param lettres_parenthese Lettres entre parenth�ses dans le rail.
 * @param indice_ferm Indice de fermeture.
 * @param indice_ouv Indice d'ouverture.
 * @param taille_mot La taille du mot � v�rifier.
 * @return 1 si le mot peut �tre plac�, 0 sinon.
 */
int verif_Verso_debut(char* mot, char* rail_verso, char* lettres_parenthese, int indice_ferm,int indice_ouv, int taille_mot);

/**
 * @brief V�rifie si le mot peut �tre plac� � la fin sur le c�t� verso du rail.
 *
 * @param mot Le mot � v�rifier.
 * @param rail_verso Le c�t� verso du rail.
 * @param lettres_parenthese Lettres entre parenth�ses dans le rail.
 * @param indice_ouv Indice d'ouverture.
 * @param indice_ferm Indice de fermeture.
 * @param taille_mot La taille du mot � v�rifier.
 * @return 1 si le mot peut �tre plac�, 0 sinon.
 */
int verif_Verso_fin(char* mot, char* rail_recto, char* lettres_parenthese, int indice_ouv, int indice_ferm, int taille_mot);


/**
 * @brief V�rifie si une lettre est valide � placer sur le rail.
 *
 * @param r Pointeur vers la structure du rail.
 * @param mot Le mot � v�rifier.
 * @param lettres_hors_parenthese Lettres hors parenth�ses dans le rail.
 * @param lettres_parenthese Lettres entre parenth�ses dans le rail.
 * @param cote Le c�t� (recto ou verso) � v�rifier.
 * @param j Pointeur vers la structure du jeu.
 * @param indice_ouv Indice d'ouverture.
 * @param indice_ferm Indice de fermeture.
 * @return 1 si la lettre est valide, 0 sinon.
 */
int lettre_rail_valide(rail* r, char* mot, char* lettres_hors_parenthese, char* lettres_parenthese, char cote, jeu* j, int indice_ouv, int indice_ferm);

/**
 * @brief Permet de jouer une lettre de son jeu quand on fait un octo
 * @param j le joueur ayant fait un octo
 * @param j_autre le joueur qui recevra une lettre supl�mentaire
 * @param joueur_actuel le num�ro du joueur (j) qui joue
 * @return 1 si le coup a r�ussi, 0 sinon.
 */
int octo_chevalet(jeu* j, jeu* j_autre,rail *r, statut_partie joueur_actuel);


/**
 * @brief �change une lettre du chevalet du joueur avec une lettre de la pioche.
 *
 * @param p Pointeur vers la structure de la pioche.
 * @param j Pointeur vers la structure du jeu.
 * @param chevalet La lettre du chevalet � �changer.
 * @return 1 si l'�change a r�ussi, 0 sinon.
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


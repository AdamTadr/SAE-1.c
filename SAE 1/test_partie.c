#include"partie.h"


test_partie() {

	// Initialisation de la partie et des composants
	srand(time(NULL));
	pioche p;
	jeu j1,j2;
	rail r;
	dictionnaire dico;
	init_rail(&r);
	init_pioche(&p);
	remplissage_pioche(&p);
	init_jeu(&j1);
	for (int i = 0; i < CHEVALETS_INIT; i++) {
		j1.jeu_actuel[i] = i % 2 ? 'S' : 'T';
	}
	modif_j_taille_jeu(&j1, CHEVALETS_INIT);
	init_jeu(&j2);
	modif_j_taille_jeu(&j1, CHEVALETS_INIT);
	remplir_paquet(&j2, &p);
	init_dico(&dico);
	size_t taille = recherche_taille_dico("ods4.txt");
	creation_dico(&dico, taille, "ods4.txt");
	indexage_dico(&dico);
	int joueur_dep = TOUR_J1;
	for (int i = 0; i < TAILLE_RAIL-1; i++) {
		r.recto[i] = i % 2 == 0 ? 'T' : 'E';
	}
	r.recto[TAILLE_RAIL - 1] = '\0';
	// Fin de l'initialisation rail.recto = "TETETETE"


	char test[] = "(TETE)ST";
	// La fonction est cens� retourner JOUE pour indiquer que le mot est jou�
	assert(tentative(&j1, &j2, &r, &dico, test, 'R', joueur_dep)==JOUE);
	// le mot jou� doit correspondre � ce qui attendue sur le rail
	assert(strcmp(r.recto, "TETETEST") == 0);
	// les tailles des paquets des joueurs doivent �tres modif�s selon les r�gles du jeu
	assert(taille_jeu_actuel(&j1) == CHEVALETS_INIT - 2);
	assert(taille_jeu_actuel(&j2) == CHEVALETS_INIT + 2);
	// Ressayer de jouer une deuxieme fois la m�me chose est censer �tre impossible car les �l�ments ont �t� modifi�s
	assert(tentative(&j1, &j2, &r, &dico, test, 'R', joueur_dep) == PAS_JOUABLE);
	// Le rail et les mains des joueurs n'ont subit aucun changement
	assert(strcmp(r.recto, "TETETEST") == 0);
	assert(taille_jeu_actuel(&j1) == CHEVALETS_INIT - 2);
	assert(taille_jeu_actuel(&j2) == CHEVALETS_INIT + 2);
	// La lettre de l'extr�mit� sortie � droite doit �tre un T
	assert(sortir_chevalet_droite(&r, 'R', strlen(r.recto)) == 'T');
	inserer_chevalet_gauche(&r, 'E', 'R');
	// Un fois le mot ins�rer le rail doit correspondre � "ETETETES"
	assert(strcmp(r.recto, "ETETETES") == 0);
	// manipulation similaires
	assert(sortir_chevalet_gauche(&r, 'R', strlen(r.recto))=='E');
	inserer_chevalet_droite(&r, 'E', 'R');
	assert(strcmp(r.recto, "TETETESE") == 0);
	// Si on �hange un chevalet du jeu d'un joueur sa taille doit rester inchang�
	echanger_chevalet(&p, &j1, 'A');
	assert(taille_jeu_actuel(&j1) == CHEVALETS_INIT - 2);
	// Test de la validit� du mot jou� et des mots cr�er de part les donctions d'initialisation du mot (pour enlever ses parenth�ses)
	char test_2[] = "(SE)TE", lettres_h_p[L_MAX_H_PARENTH], lettres_p[L_MAX_PARENTH];
	assert(lettre_rail_valide(&r, test_2, lettres_h_p, lettres_p, 'R', &j1, 0, P_FIN_MIN) == JOUABLE);
	assert(strcmp(lettres_h_p, "TE"));
	assert(strcmp(lettres_p, "SE") == 0);
	suppr_dico(&dico);
}






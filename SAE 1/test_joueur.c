#include "joueur.h"




void test_joueur() {
	jeu j1;
	jeu j2;
	pioche p;
	init_pioche(&p);
	remplissage_pioche(&p);

	init_jeu(&j1);
	assert(taille_jeu_actuel(&j1) == VIDE);
	assert(paquet_vide(&j1));
	remplir_paquet(&j1, &p);
	assert(taille_jeu_actuel(&j1) == CHEVALETS_INIT);
	char test[] = "ZZZZZ";
	assert(jouable(&j1, test) == PAS_JOUABLE);
	int i;
	for (i = 0; i < TEST; i++) {
		test[i] = selec_che_j_actuel(&j1, i);
	}
	test[i] = '\0';
	assert(jouable(&j1, test) == JOUABLE);
	save_jeu(&j1);
	for (int i = 0; i < taille_jeu_actuel(&j1); i++) {
		assert(selec_che_j_actuel(&j1, i) == selec_che_j_precendent(&j1, i));
	}

	for (int i = 0; i < TEST; i++) {
		char tp = jouer_chevalet(&j1, selec_che_j_actuel(&j1, i));
	}
	assert(jouable(&j1, test) == PAS_JOUABLE);
	assert(precedent_jouable(&j1, test) == JOUABLE);

}

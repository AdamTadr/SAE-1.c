#include "partie.h"




main() {

	srand(time(NULL));
	pioche p;
	jeu j1;
	jeu j2;
	rail r;
	dictionnaire dico;

	init_rail(&r);
	init_pioche(&p);
	remplissage_pioche(&p);
	init_jeu(&j1);
	remplir_paquet(&j1, &p);
	init_jeu(&j2);
	remplir_paquet(&j2, &p);

	init_dico(&dico);
	size_t taille = recherche_taille_dico("ods4.txt");
	creation_dico(&dico, taille, "ods4.txt");
	indexage_dico(&dico);

	affichage_jeu(&j1, 1);
	affichage_jeu(&j2, 2);
	printf("\n");
	int joueur_dep = init_partie(&dico, &p, &j1, &j2, &r);

	jouer_partie(&dico, &p, &j1, &j2, &r, joueur_dep);


}


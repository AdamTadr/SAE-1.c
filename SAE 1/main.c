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

	for (int i = 0; i < taille_dico(&dico); i++) {
		printf("%s et leur indice %d\n", dico.dico[i], trouver_mot(&dico, dico.dico[i]));
	}


	/*printf("\nL'indice du mot est : %d, %s\n", trouver_mot(&dico, "NORD"), dico.dico[trouver_mot(&dico, "NORD")]);
	printf("\nPour une 2 eme fois L'indice du mot est : %d\n", trouver_mot(&dico, "NORD"));
	rendre_mot_injouable(&dico, trouver_mot(&dico, "NORD"));
	printf("\nL'indice du mot est : %d ?\n", trouver_mot(&dico, "NORD"));
	printf("\nL'indice du mot est : %d, %s\n", trouver_mot(&dico, "CHIEN"), dico.dico[trouver_mot(&dico, "CHIEN")]);
	printf("\n\n");
	*/
	affichage_jeu(&j1, 1);
	affichage_jeu(&j2, 2);
	printf("\n");
	int valeur = init_partie(&dico, &p, &j1, &j2, &r);

	jouer_partie(&dico, &p, &j1, &j2, &r, valeur);



}



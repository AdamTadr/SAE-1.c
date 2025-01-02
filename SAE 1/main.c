#include "rail.h"

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

	size_t taille = recherche_taille_dico("ods4.txt");
	creation_dico(&dico, taille, "ods4.txt");
	indexage_dico(&dico);
	/*printf("\nL'indice du mot est : %d, %s\n", trouver_mot(&dico, "PIGEON"), dico.dico[trouver_mot(&dico, "PIGEON")]);
	printf("\nPour une 2 eme fois L'indice du mot est : %d\n", trouver_mot(&dico, "PIGEON"));
	rendre_mot_injouable(&dico, trouver_mot(&dico, "PIGEON"));
	printf("\nL'indice du mot est : %d ?\n", trouver_mot(&dico, "PIGEON"));
	printf("\nL'indice du mot est : %d, %s\n", trouver_mot(&dico, "CHIEN"), dico.dico[trouver_mot(&dico, "CHIEN")]);
	printf("\n\n");*/

	affichage_jeu(&j1, 1);
	affichage_jeu(&j2, 2);
	printf("\n");
	int valeur = init_partie(&dico, &p, &j1, &j2, &r);

	jouer_partie(&dico, &p, &j1, &j2, &r, valeur);



}
#include "rail.h"

main() {

	srand(time(NULL));
	pioche p;
	jeu j1;
	jeu j2;
	rail r;
	dictionnaire dico;

	init_pioche(&p);
	remplissage_pioche(&p);

	init_jeu(&j1);
	remplir_paquet(&j1, &p);
	init_jeu(&j2);
	remplir_paquet(&j2, &p);

	printf("Le jeu du j1 : ");
	affichage_jeu(&j1);
	printf("\n");
	printf("Le jeu du j2 : ");
	affichage_jeu(&j2);
	printf("\n");

	size_t taille = recherche_taille_dico("ods4.txt");
	printf("\n le nb mot : %zu\n", taille);

	creation_dico(&dico,taille, "ods4.txt");

	affichage_dico(&dico);
	
	indexage_dico(&dico);

	affichage_index(&dico);

	printf("\nL'indice du mot est : %d, %s\n", trouver_mot(&dico, "PIGEON"), dico.dico[trouver_mot(&dico, "PIGEON")]);

	init_partie(&dico, &p, &j1, &j2, &r);
	

}
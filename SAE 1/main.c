#include "partie.h"

void test_ini_dico() {
	int taille = recherche_taille_dico("ods4.txt");
	assert(taille >= RIEN);
	dictionnaire dico;
	init_dico(&dico);
	creation_dico(&dico, (size_t)taille, "ods4.txt");
	printf("%d ", taille_dico(&dico));
	assert(taille_dico(&dico) == taille);
	assert(addr_mot(&dico, taille_dico(&dico)-1)!=NULL);
	suppr_dico(&dico);
}


void test_ind_dico() {
	int taille = recherche_taille_dico("ods4.txt");
	dictionnaire dico;
	init_dico(&dico);
	creation_dico(&dico, (size_t)taille, "ods4.txt");
	init_index(&dico);
	assert(indice_premiere_lettre(&dico, 0) == PAS_TROUVER);
	indexage_dico(&dico);
	assert(indice_premiere_lettre(&dico, 0) != PAS_TROUVER);

	assert(strcmp(dico.dico[taille_dico(&dico) - 1], dico.dico[trouver_mot(&dico, dico.dico[taille_dico(&dico) - 1])]) == 0);
	assert(val_permiere_lettre(&dico, taille_dico(&dico) - 1) == dico.dico[taille_dico(&dico) - 1][PREMIERE_LETTRE]);
	assert(val_deuxieme_lettre(&dico, taille_dico(&dico) - 1) == dico.dico[taille_dico(&dico) - 1][DEUXIEME_LETTRE]);
	printf("%s\n", dico.dico[taille_dico(&dico) - 1]);

}

main() {

	srand(time(NULL));
	pioche p;
	jeu j1;
	jeu j2;
	rail r;
	dictionnaire dico;

	test_ini_dico();
	test_ind_dico();


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


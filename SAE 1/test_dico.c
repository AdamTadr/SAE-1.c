#pragma once
#include "dictionnaire.h"

void test_ini_dico() {
	// Cr�ation du dico avec lequel on vas tester les diff�rents composants
	int taille = recherche_taille_dico("ods4.txt");
	//Test la taille du dico
	assert(taille > RIEN);
	dictionnaire dico;
	init_dico(&dico);
	// Le dico est cens� �tre vide � l'initialisation
	assert(dico_vide(&dico));
	creation_dico(&dico, (size_t)taille, "ods4.txt");
	// La fonction taille_dico doit retourner la valeur avec laquelle � la �t� init (taille)
	assert(taille_dico(&dico) == taille);
	// L'adresse de tout les mot du dico et notamment du dernier sont cens� �tre valide
	assert(addr_mot(&dico, taille_dico(&dico) - 1) != NULL);
	changer_taille_dico(&dico, TEST);
	// La taille du dico doit avoir �t� modifi�
	assert(taille_dico(&dico) == TEST);
	suppr_dico(&dico);
}


void test_ind_dico() {
	// Cr�ation du dico avec lequel on vas tester les diff�rents composants
	int taille = recherche_taille_dico("ods4.txt");
	dictionnaire dico;
	init_dico(&dico);
	creation_dico(&dico, (size_t)taille, "ods4.txt");
	// Mise en place du syst�me d'indexiation du dictionnaire
	init_index(&dico);
	// L'ensemble des indices sont initialis�es avec PAS_TROUVER
	assert(indice_premiere_lettre(&dico, A) == PAS_TROUVER);
	assert(indice_deuxieme_lettre(&dico, A, A) == PAS_TROUVER);
	// Indexage du dico
	indexage_dico(&dico);
	// Si il y a un mot commen�ant par AA dans le dico alors la fct trouve son indice !=PAS_TROUVER (avec celui utilis� oui)
	assert(indice_premiere_lettre(&dico, A) != PAS_TROUVER);
	assert(indice_deuxieme_lettre(&dico, A, A) != PAS_TROUVER);

	// On inscrit une nouvelle valeur de TEST pour l'indice du premier mot commen�ant par A et AA
	add_ind_prem_l(&dico, A, TEST);
	add_ind_deuxieme_l(&dico, A, A, TEST);
	// Cela est cens� trouver TEST � chaque appel de la fct permettant de trouver l'indice
	assert(indice_premiere_lettre(&dico, A) == TEST);
	assert(indice_deuxieme_lettre(&dico, A, A) == TEST);

	//L'indice du mot � taille_dico - 1 est cens� correpondre � l'indice de trouver mot qui recoie le mot � taille_dico - 1
	assert(taille_dico(&dico) - 1 == trouver_mot(&dico, dico.dico[taille_dico(&dico) - 1]));
	// Les valeurs (premi�re et deuxieme lettre du mo � l'indice i) sont cens� correspondrent � celle du mot i pour la case 0(PREMIERE_LETTRE) et 1 (DEUXIEME_LETTRE)
	assert(val_permiere_lettre(&dico, taille_dico(&dico) - 1) == dico.dico[taille_dico(&dico) - 1][PREMIERE_LETTRE]);
	assert(val_deuxieme_lettre(&dico, taille_dico(&dico) - 1) == dico.dico[taille_dico(&dico) - 1][DEUXIEME_LETTRE]);
	suppr_dico(&dico);
}


void test_dico_injouable() {
	// Cr�ation du dico avec lequel on vas tester les diff�rents composants
	int taille = recherche_taille_dico("ods4.txt");
	dictionnaire dico;
	init_dico(&dico);
	creation_dico(&dico, (size_t)taille, "ods4.txt");
	indexage_dico(&dico);
	// Ici le mot ne respecte pas le bon format
	assert(bonne_casse("AsasaAZ") == PAS_JOUABLE);
	// Ici le mot respecte le bon format
	bonne_casse("AAA");
	// Si il existe un mot nomm� ARBRE dans le dictionnaire alors la focntion doit trouver  son indice
	assert(trouver_mot(&dico, "ARBRE") != PAS_TROUVER);

	rendre_mot_injouable(&dico, trouver_mot(&dico, "ARBRE"));
	// Le mot doit �tre PAS_TROUVER
	assert(trouver_mot(&dico, "ARBRE") == PAS_TROUVER);
	// Le mot ZZZZZ n'existe pas normalement
	assert(trouver_mot(&dico, "ZZZZZ") == PAS_TROUVER);
	suppr_dico(&dico);
}
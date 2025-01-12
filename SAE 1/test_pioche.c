#pragma once
#include "pioche.h"


void test_pioche() {
	pioche p;
	init_pioche(&p);
	assert(taille_pioche(&p) == VIDE);
	remplissage_pioche(&p);
	assert(taille_pioche(&p) == MAX_pioche);
	char test = selectionner_chevalet(&p, TEST);
	assert(test == distribuer_chevalet(&p, TEST));
	assert(taille_pioche(&p) == MAX_pioche - 1);
	assert(indice_valide(&p, MAX_pioche - 1) == 0);
	ajouter_element_pioche(&p, 'C');
	assert(taille_pioche(&p) == MAX_pioche);
	mod_taille_pioche(&p, TEST);
	assert(taille_pioche(&p) == TEST);
}




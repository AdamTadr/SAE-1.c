#include "pioche.h"


void init_pioche(pioche* p) {
	assert(p != NULL);
	mod_taille_pioche(p, VIDE);
}


int pioche_remplis(pioche* p) {
	assert(p != NULL);
	return taille_pioche(p) == MAX_pioche;
}

int pioche_vide(pioche* p) {
	assert(p != NULL);
	return taille_pioche(p) == 0;
}

void ajouter_element_pioche(pioche* p, char che) {
	assert(p != NULL);
	p->pioche[p->nb++] = che;
}



void remplissage_pioche(pioche* p) {
	assert(p != NULL);
	int frequence[] = { UNE_L,UNE_L,UNE_L,UNE_L,UNE_L,UNE_L, NB_E, NB_A, NB_IS,NB_IS,
	NB_NTR,NB_NTR,NB_NTR, NB_ULO,NB_ULO,NB_ULO, NB_MD,NB_MD, NB_CVP,NB_CVP,NB_CVP };
	char lettres[] = { 'F','G','H','J','Q','B','E','A','I','S','N','T','R','U','L','O','M','D','C','V','P' };
	assert(pioche_vide(p));
	for (int i = 0; i < sizeof(frequence) / sizeof(int); i++) {
		for (int j = 0; j < frequence[i]; j++) {
			ajouter_element_pioche(p, lettres[i]);
		}
	}
}
void affichage_pioche(pioche* p) {
	assert(p != NULL);
	assert(!pioche_vide(p));
	printf("\n");
	for (int i = 0; i < taille_pioche(p); i++)
		printf("%c", selectionner_chevalet(p,i));
	printf("\n");
}

int indice_valide(const pioche* p, int i) {
	assert(p != NULL);
	return i >= 0 && i < taille_pioche(p);
}

char distribuer_chevalet(pioche* p, int i) {
	assert(indice_valide(p, i));

	char temp = selectionner_chevalet(p, i);
	--p->nb;
	for (int d = i; d < taille_pioche(p); d++) {
		p->pioche[d] = selectionner_chevalet(p, d + 1);
	}

	return temp;
}

char selectionner_chevalet(const pioche* p, int n) {
	assert(p != NULL);
	return p->pioche[n];
}

int taille_pioche(const pioche* p) {
	assert(p != NULL);
	return  p->nb;
}
void mod_taille_pioche(pioche* p, int n) {
	assert(p != NULL && n >= 0);
	p->nb = n;
}

void modif_che_pioche(pioche* p, int indice, char che) {
	assert(p != NULL);
	p->pioche[indice] = che;
}


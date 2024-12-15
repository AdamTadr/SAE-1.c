#include "pioche.h"


void init_pioche(pioche* p) {
	p->nb = 0;
}


int pioche_remplis(pioche* p) {
	return p->nb == MAX_pioche;
}

int pioche_vide(pioche* p) {
	return p->nb == 0;
}



void remplissage_pioche(pioche* p) {

	assert(pioche_vide(p));

	int freq_lettre;

	p->pioche[p->nb++] = 'F';
	p->pioche[p->nb++] = 'G';
	p->pioche[p->nb++] = 'H';
	p->pioche[p->nb++] = 'J';
	p->pioche[p->nb++] = 'Q';
	p->pioche[p->nb++] = 'B';

	for (int i = 0; i < NB_E; i++)
		p->pioche[p->nb++] = 'E';

	for (int i = 0; i < NB_A; i++)
		p->pioche[p->nb++] = 'A';

	for (int i = 0; i < NB_IS; i++)
		p->pioche[p->nb++] = 'I';
	for (int i = 0; i < NB_IS; i++)
		p->pioche[p->nb++] = 'S';

	for (int i = 0; i < NB_NTR; i++)
		p->pioche[p->nb++] = 'N';
	for (int i = 0; i < NB_NTR; i++)
		p->pioche[p->nb++] = 'T';
	for (int i = 0; i < NB_NTR; i++)
		p->pioche[p->nb++] = 'R';

	for (int i = 0; i < NB_ULO; i++)
		p->pioche[p->nb++] = 'U';
	for (int i = 0; i < NB_ULO; i++)
		p->pioche[p->nb++] = 'L';
	for (int i = 0; i < NB_ULO; i++)
		p->pioche[p->nb++] = 'O';

	for (int i = 0; i < NB_MD; i++)
		p->pioche[p->nb++] = 'M';
	for (int i = 0; i < NB_MD; i++)
		p->pioche[p->nb++] = 'D';

	for (int i = 0; i < NB_CVP; i++)
		p->pioche[p->nb++] = 'C';
	for (int i = 0; i < NB_CVP; i++)
		p->pioche[p->nb++] = 'V';
	for (int i = 0; i < NB_CVP; i++)
		p->pioche[p->nb++] = 'P';

}

void affichage_pioche(pioche* p) {
	assert(!pioche_vide(p));
	printf("\n");
	for (int i = 0; i < p->nb; i++)
		printf("%c ", p->pioche[i]);
	printf("\n");
}

int indice_valide(const pioche* p, int i) {
	return i >= 0 && i < p->nb;
}

char distribuer_chevalet(pioche* p, int i) {

	assert(indice_valide(p, i));

	char temp = p->pioche[i];
	--p->nb;
	for (int d = i; d < p->nb; d++) {
		p->pioche[d] = p->pioche[d + 1];
	}

	return temp;
}

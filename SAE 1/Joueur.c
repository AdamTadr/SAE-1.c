#include "joueur.h"


void init_bl(black_list* bl) {
	bl->nb = 0;
}

int taille_bl(black_list* bl) {
	return bl->nb;
}

void init_jeu(jeu* j) {
	j->nb[0] = 0;
	j->nb[1] = 0;
}

int paquet_vide(const jeu* j) {
	return j->nb == 0;
}

void remplir_paquet(jeu* j, pioche* p) {
	assert(paquet_vide);

	for (int i = 0; i < CHEVALETS_INIT; i++) {

		int d = rand() % p->nb;
		j->jeu_actuel[j->nb[0]++] = distribuer_chevalet(p, d);
	}

}


void save_jeu(jeu* j) {
	j->nb[1] = j->nb[0];
	for (int i = 0; i < j->nb[0]; i++) {
		j->jeu_precedent[i] = j->jeu_actuel[i];
	}
}

void recevoir_chevalet(jeu* j, char che) {
	assert(j->nb[0] < MAX_CHEVALETS);
	j->jeu_actuel[j->nb[0]++] = che;
}

void trie_alphabetique(jeu* j) {
	for (int i = 0; i < j->nb[0] - 1; i++) {
		for (int d = 0; d < j->nb[0] - i - 1; d++) {
			if (j->jeu_actuel[d] > j->jeu_actuel[d + 1]) {
				char temp = j->jeu_actuel[d + 1];
				j->jeu_actuel[d + 1] = j->jeu_actuel[d];
				j->jeu_actuel[d] = temp;
			}
		}
	}
}

void affichage_jeu(jeu* j, int jnb) {
	trie_alphabetique(j);
	assert(paquet_vide != 1);
	printf("%d : ", jnb);
	for (int i = 0; i < j->nb[0]; i++)
		printf("%c", j->jeu_actuel[i]);
	printf("\n");
}

void affichage_jeu_precedent(jeu* j, int jnb) {
	trie_alphabetique(j);
	assert(paquet_vide != 1);
	printf("%d : ", jnb);
	for (int i = 0; i < j->nb[1]; i++)
		printf("%c", j->jeu_precedent[i]);
	printf("\n");
}

int deja_comptabiliser(int indice, const black_list* bl) {
	for (int i = 0; i < bl->nb; i++) {
		if (indice == bl->list[i])
			return 1;
	}
	return 0;

}

int jouable(jeu* j, char* che) {
	black_list bl;
	init_bl(&bl);

	int taille_mot = strlen(che);

	for (int i = 0; i < taille_mot; i++) {
		for (int d = 0; d < taille_jeu_actuel(j); d++) {
			if (deja_comptabiliser(d, &bl))
				continue;
			if (che[i] == j->jeu_actuel[d]) {
				bl.list[bl.nb++] = d;
				break;
			}
		}
		if (bl.nb != i + 1) {
			return PAS_JOUABLE;
		}
	}
	return JOUABLE;

}

int precedent_jouable(jeu* j_autre, char* che) {
	black_list bl;
	init_bl(&bl);

	int taille_mot = strlen(che);
	;
	for (int i = 0; i < taille_mot; i++) {
		for (int d = 0; d < taille_jeu_actuel(j_autre); d++) {
			if (deja_comptabiliser(d, &bl))
				continue;
			if (che[i] == j_autre->jeu_precedent[d]) {
				bl.list[bl.nb++] = d;
				break;
			}
		}
		if (bl.nb != i + 1) {
			return PAS_JOUABLE;
		}
	}
	return JOUABLE;

}



int indice_chevalet_paquet(jeu* j, char che) {
	int indice = PAS_JOUABLE;
	for (int i = 0; i < taille_jeu_actuel(j); i++) {
		if (j->jeu_actuel[i] == che)
			indice = i;
	}
	return indice;
}

int taille_jeu_actuel(const jeu* j) {
	return j->nb[0];
}
int taille_jeu_precent(const jeu* j) {
	return j->nb[1];
}


char jouer_chevalet(jeu* j, char che) {

	int indice = indice_chevalet_paquet(j, che);

	char temp = j->jeu_actuel[indice];
	j->jeu_actuel[indice] = j->jeu_actuel[j->nb[0] - 1];
	j->jeu_actuel[--j->nb[0]] = temp;

	return temp;
}


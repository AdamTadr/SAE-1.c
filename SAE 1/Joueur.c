#include "joueur.h"


void init_bl(black_list* bl) {
	assert(bl != NULL);
	bl->nb = 0;
}


void init_jeu(jeu* j) {
	assert(j != NULL);
	 modif_j_taille_jeu(j, RIEN);
	 modif_j_taille_jeu_precedent(j, RIEN);
}

int paquet_vide(const jeu* j) {
	assert(j != NULL);
	return taille_jeu_actuel(j) == 0;
}

void modif_j_taille_jeu(jeu* j, int taille) {
	assert(j != NULL && taille >= 0);
	j->nb[JEU_ACTUEL] = taille;
}
void modif_j_taille_jeu_precedent(jeu* j, int taille) {
	assert(j != NULL && taille >= 0);
	j->nb[JEU_PRECEDENT] = taille;
}


void remplir_paquet(jeu* j, pioche* p) {
	assert(p != NULL && j != NULL);
	assert(paquet_vide);

	for (int i = 0; i < CHEVALETS_INIT; i++) {

		int d = rand() % taille_pioche(p);
		char che = distribuer_chevalet(p, d);
		ajouter_che(j, che);
	}

}

void ajouter_che(jeu* j, char che) {
	assert(j != NULL);
	j->jeu_actuel[j->nb[JEU_ACTUEL]++] = che;
}

void save_jeu(jeu* j) {
	assert(j != NULL);
	modif_j_taille_jeu_precedent(j, taille_jeu_actuel(j));
	for (int i = 0; i < taille_jeu_actuel(j); i++) {
		char che = selec_che_j_actuel(j, i);
		ajouter_che_precedent(j, i, che);
	}
}

char selec_che_j_actuel(const jeu* j, int indice) {
	assert(j != NULL && indice >= 0 && indice < taille_jeu_actuel(j));
	return j->jeu_actuel[indice];
}

void ajouter_che_precedent(jeu * j,int ind, char che){
	assert(j != NULL && ind >= 0 && ind < MAX_CHEVALETS);
	j->jeu_precedent[ind] = che;
}

void recevoir_chevalet(jeu* j, char che) {
	assert(j != NULL);
	assert(taille_jeu_actuel(j) < MAX_CHEVALETS);
	j->jeu_actuel[j->nb[0]++] = che;
}

void trie_alphabetique(jeu* j) {
	assert(j != NULL);
	for (int i = 0; i < taille_jeu_actuel(j) - 1; i++) {
		for (int d = 0; d < taille_jeu_actuel(j) - i - 1; d++) {
			if (selec_che_j_actuel(j, d) > selec_che_j_actuel(j, d + 1)) {
				char temp = selec_che_j_actuel(j, d+1);
				remp_che_j_actuel(j, d+1, selec_che_j_actuel(j, d));
				remp_che_j_actuel(j, d, temp);
			}
		}
	}
}

void remp_che_j_actuel(jeu* j, int indice, char che) {
	assert(j != NULL);
	j->jeu_actuel[indice] = che;
}

void affichage_jeu(const jeu* j, int jnb) {
	assert(j != NULL);
	trie_alphabetique(j);
	assert(paquet_vide != 1);
	printf("%d : ", jnb);
	for (int i = 0; i < taille_jeu_actuel(j); i++)
		printf("%c", selec_che_j_actuel(j,i));
	printf("\n");
}

/**
 * @brief debug
 * @param j 
 * @param jnb 
 */
void affichage_jeu_precedent(const jeu* j, int jnb) {
	assert(j != NULL);
	trie_alphabetique(j);
	assert(paquet_vide != 1);
	printf("P %d : ", jnb);
	for (int i = 0; i < taille_jeu_precent(j); i++)
		printf("%c", selec_che_j_precendent(j,i));
	printf("\n");
}


char selec_che_j_precendent(const jeu* j, int indice) {
	assert(j != NULL);
	assert(indice >= 0 && indice < taille_jeu_precent(j));
	return j->jeu_precedent[indice];
}

int taille_bl(black_list* bl) {
	assert(bl != NULL);
	return bl->nb;
}

int deja_comptabiliser(int indice, const black_list* bl) {
	assert(bl != NULL);
	for (int i = 0; i < taille_bl(bl); i++) {
		if (indice == selec_ele_bl(bl,i))
			return 1;
	}
	return 0;

}

int selec_ele_bl(black_list* bl, int indice) {
	assert(bl != NULL && indice < taille_bl(bl));
	return bl->list[indice];
}

int jouable(jeu* j, char* che) {
	assert(j != NULL && che != NULL);
	black_list bl;
	init_bl(&bl);

	int taille_mot = strlen(che);

	for (int i = 0; i < taille_mot; i++) {
		for (int d = 0; d < taille_jeu_actuel(j); d++) {
			if (deja_comptabiliser(d, &bl))
				continue;
			if (che[i] == selec_che_j_actuel(j, d)) {
				ajouter_ele_bl(&bl, d);
				break;
			}
		}
		if (taille_bl(&bl)!= i + 1) {
			return PAS_JOUABLE;
		}
	}
	return JOUABLE;

}

int precedent_jouable(jeu* j_autre, char* che) {
	assert(j_autre != NULL && che != NULL);
	black_list bl;
	init_bl(&bl);

	int taille_mot = strlen(che);
	;
	for (int i = 0; i < taille_mot; i++) {
		for (int d = 0; d < taille_jeu_actuel(j_autre); d++) {
			if (deja_comptabiliser(d, &bl))
				continue;
			if (che[i] == selec_che_j_precendent(j_autre, d)) {
				ajouter_ele_bl(&bl, d);
				break;
			}
		}
		if (taille_bl(&bl) != i + 1) {
			return PAS_JOUABLE;
		}
	}
	return JOUABLE;

}

void ajouter_ele_bl(black_list* bl, int n) {
	assert(bl != NULL);
	bl->list[bl->nb++] = n;
}

int indice_chevalet_paquet(jeu* j, char che) {
	assert(j != NULL);
	int indice = PAS_JOUABLE;
	for (int i = 0; i < taille_jeu_actuel(j); i++) {
		if (selec_che_j_actuel(j, i)== che)
			indice = i;
	}
	return indice;
}

int taille_jeu_actuel(const jeu* j) {
	assert(j != NULL);
	return j->nb[JEU_ACTUEL];
}
int taille_jeu_precent(const jeu* j) {
	assert(j != NULL);
	return j->nb[JEU_PRECEDENT];
}


char jouer_chevalet(jeu* j, char che) {
	assert(j != NULL);
	int indice = indice_chevalet_paquet(j, che);
	if (indice == PAS_JOUABLE)
		return PAS_JOUABLE;

	char temp = selec_che_j_actuel(j, indice);
	remp_che_j_actuel(j, indice, selec_che_j_actuel(j, taille_jeu_actuel(j) - 1));
	remp_che_j_actuel(j, taille_jeu_actuel(j), temp);
	decr_j_actuel(j);

	return temp;
}


void decr_j_actuel(jeu* j) {
	assert(j != NULL);
	--j->nb[0];
}

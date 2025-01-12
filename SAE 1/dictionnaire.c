#include "dictionnaire.h"
#pragma warning (disable : 4996)


int taille_dico(const dictionnaire* dico) {
	assert(dico != NULL);
	return dico->taille;
}


size_t recherche_taille_dico(const char* nom_dico) {
	assert(nom_dico != NULL);
	FILE* f = fopen(nom_dico, "r");
	if (f == NULL) {
		printf("fichier non accessible\n");
		return;
	}
	size_t nbm = 0;
	char mot[30] = { 0 };
	int n;
	n = fscanf(f, "%29s", mot);
	while (n == 1) {
		++nbm;
		n = fscanf(f, "%29s", mot);
	}
	if (ferror(f))
		printf("erreur - %s\n", strerror(errno));
	fclose(f);
	return nbm;
}



void init_dico(dictionnaire* dico) {
	assert(dico != NULL);
	mod_taille_dico(dico, VIDE);
}

int dico_vide(dictionnaire* dico) {
	assert(dico != NULL);
	return taille_dico(dico) == VIDE;
}

void changer_taille_dico(dictionnaire* dico, int valeur) {
	assert(dico != NULL && valeur >= 0);
	dico->taille = valeur;
}

void dico_alloc(dictionnaire* dico, size_t taille) {
	assert(dico != NULL && taille >= 0);
	dico->dico = (char**)malloc(sizeof(char*) * taille);
	if (dico->dico == NULL) {
		printf("Erreur. Pas assez d'espace.\n");
		free(dico->dico);
		return;
	}
}

void creation_dico(dictionnaire* dico, size_t taille, const char* nom_dico) {
	assert(dico != NULL && nom_dico !=NULL && taille >= 0);
	FILE* f = fopen(nom_dico, "r");
	if (f == NULL) {
		printf("fichier non accessible\n");
		return;
	}

	changer_taille_dico(dico, (int)taille);
	dico_alloc(dico, taille);

	char mot[30] = { 0 };
	int n = 1;
	for (int i = 0; i < taille && n == 1; i++) {

		n = fscanf(f, "%29s", mot);
		int taille_mot = strlen(mot);

		dico->dico[i] = (char*)malloc(taille_mot + 1);

		if (dico->dico[i] == NULL) {
			printf("Erreur. Pas assez d'espace.\n");
			for (int j = 0; j < i; j++) {
				free(dico->dico[j]);
			}
			free(dico->dico);
			return;
		}

		strcpy(dico->dico[i], mot);
	}
	if (ferror(f))
		printf("erreur - %s\n", strerror(errno));
}


void suppr_dico(dictionnaire* dico) {
	assert(dico != NULL);
	for (int j = 0; j < taille_dico(dico); j++) {
		free(dico->dico[j]);
	}
	free(dico->dico);
	return;
}


// Il faut que le dico est ordonnées dans l'ordre croissant (comme tout les dico)...

void init_index(dictionnaire* dico) {
	assert(dico != NULL);
	for (int i = 0; i < TAILLE_ALPHABET; i++) {
		add_ind_prem_l(dico, i, PAS_TROUVER);
		for (int j = 0; j < TAILLE_ALPHABET; j++) {
			add_ind_deuxieme_l(dico, i, j, PAS_TROUVER);
		}
	}
}

void indexage_dico(dictionnaire* dico) {
	assert(dico != NULL);
	assert(taille_dico(dico) > 0);

	init_index(dico);
	for (int i = 0, j = 0, d = 'A'; i < taille_dico(dico); ++i) {
		if (val_permiere_lettre(dico, i) == d) {
			add_ind_prem_l(dico, j, i);
			indexage_secondaire(dico, d, i);
			j++;
			d++;
		}
		if (val_permiere_lettre(dico, i) > d) {
			char ecart = (char)val_permiere_lettre(dico, i);
			for (j, d; d < ecart; j++, d++) {
				add_ind_prem_l(dico, j, PAS_TROUVER);
			}
			add_ind_prem_l(dico, j, i);
			indexage_secondaire(dico, d, i);
			d++;
			j++;
		}

	}

}


void indexage_secondaire(dictionnaire* dico, char ref, int depart) {
	assert(dico != NULL && depart >= 0);
	assert(ref >= 'A' && ref <= 'Z');

	int ind_lettre_tab = ref - 'A';

	for (int i = depart, j = 0, d = 'A'; i < taille_dico(dico) && val_permiere_lettre(dico, i) == ref; ++i) {

		if (val_deuxieme_lettre(dico, i) == d) {
			add_ind_deuxieme_l(dico, ind_lettre_tab, j, i);
			j++;
			d++;
		}
		if (val_deuxieme_lettre(dico, i) > d) {
			char dernier = val_deuxieme_lettre(dico, i);
			for (; d < dernier; j++, d++) {
				add_ind_deuxieme_l(dico, ind_lettre_tab, j, PAS_TROUVER);
			}
			add_ind_deuxieme_l(dico, ind_lettre_tab, j, i);
			j++;
			d++;
		}

	}
}

int val_permiere_lettre(dictionnaire* dico, int indice) {
	assert(dico != NULL && indice >= 0);
	return dico->dico[indice][PREMIERE_LETTRE];
}

int val_deuxieme_lettre(dictionnaire* dico, int indice) {
	assert(dico != NULL && indice >= 0);
	return dico->dico[indice][DEUXIEME_LETTRE];
}



int indice_premiere_lettre(dictionnaire* dico, int val_alphanum_l) {
	assert(dico != NULL);
	assert(val_alphanum_l >= 0 && val_alphanum_l < TAILLE_ALPHABET);
	return dico->index[val_alphanum_l].ind_premiere;
}

int indice_deuxieme_lettre(dictionnaire* dico, int val_num_l, int val_ref) {
	assert(dico != NULL);
	assert(val_num_l >= 0 && val_num_l < TAILLE_ALPHABET);
	assert(val_ref >= 0 && val_ref < TAILLE_ALPHABET);
	return dico->index[val_ref].ind_deuxieme[val_num_l];
}

void add_ind_prem_l(dictionnaire* dico, int val_alphanum_l, int indice) {
	assert(dico != NULL);
	assert(val_alphanum_l >= 0 && val_alphanum_l < TAILLE_ALPHABET);

	dico->index[val_alphanum_l].ind_premiere = indice;
}

void add_ind_deuxieme_l(dictionnaire* dico, int val_alphanum_l1, int val_alphanum_l2, int indice) {
	assert(dico != NULL);
	assert(val_alphanum_l1 >= 0 && val_alphanum_l1 < TAILLE_ALPHABET);
	assert(val_alphanum_l2 >= 0 && val_alphanum_l2 < TAILLE_ALPHABET);

	dico->index[val_alphanum_l1].ind_deuxieme[val_alphanum_l2] = indice;
}

int trouver_mot(const dictionnaire* dico, const char* mot) {
	assert(dico != NULL && mot != NULL);

	if (bonne_casse(mot) == PAS_TROUVER)
		return PAS_TROUVER;

	int case_lettre_1 = mot[PREMIERE_LETTRE] - 'A';
	int case_lettre_2 = mot[DEUXIEME_LETTRE] - 'A';
	char mot_limite = mot[DEUXIEME_LETTRE] + 1;
	if (indice_premiere_lettre(dico, case_lettre_1) == PAS_TROUVER) {
		return PAS_TROUVER;
	}
	int depart = dico->index[case_lettre_1].ind_deuxieme[case_lettre_2];
	if (depart == PAS_TROUVER) {
		return PAS_TROUVER;
	}

	for (int i = depart; dico->dico[i][DEUXIEME_LETTRE] < mot_limite && i < dico->taille; i++) {
		if (strcmp(addr_mot(dico, i), mot) == 0) {
			return i;
		}
	}
	return PAS_TROUVER;
}

int bonne_casse(const char* mot) {
	assert(mot != NULL);

	int taille_mot = strlen(mot);

	for (int i = 0; i < taille_mot; i++) {
		if (mot[i] < 'A' || mot[i]>'Z')
			return PAS_TROUVER;
	}
	return 1;
}

void rendre_mot_injouable(dictionnaire* dico, int indice) {
	assert(dico != NULL && indice >= 0 && indice < taille_dico(dico));
	strcpy(dico->dico[indice], "\0");
}

void mod_taille_dico(dictionnaire* dico, int taille) {
	assert(dico != NULL && taille >= 0);
	dico->taille = taille;
}


char* addr_mot(const dictionnaire* dico, int indice) {
	assert(dico != NULL && indice >= 0);
	return dico->dico[indice];
}
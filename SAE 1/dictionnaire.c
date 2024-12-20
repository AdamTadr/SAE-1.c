#include "dictionnaire.h"
#pragma warning (disable : 4996)


int taille_dico(dictionnaire* dico) {
	return dico->taille;
}


size_t recherche_taille_dico(char* nom_dico) {
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
	dico->taille = 0;
}



void creation_dico(dictionnaire* dico, size_t taille, char* nom_dico) {

	FILE* f = fopen(nom_dico, "r");
	if (f == NULL) {
		printf("fichier non accessible\n");
		return;
	}

	dico->taille = (int)taille;
	dico->dico = (char**)malloc(sizeof(char*) * taille);
	if (dico->dico == NULL) {
		printf("Erreur. Pas assez d'espace.\n");
		free(dico->dico);
		return;
	}

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


void affichage_dico(const dictionnaire* dico) {
	for (int i = 0; i < 10; i++)
		printf("%s\n", dico->dico[i]);
}

// Il faut que le dico est ordonnées dans l'ordre croissant (comme tout les dico)...

void indexage_dico(dictionnaire* dico) {
	assert(taille_dico(dico) > 0);

	for (int i = 0, j = 0, d = 'A'; i < taille_dico(dico); i++) {
		if (dico->dico[i][PREMIERE_LETTRE] == d) {
			dico->index[j].ind_premiere = i;
			indexage_secondaire(dico, d, i);
			j++;
			d++;
		}
		if (dico->dico[i][PREMIERE_LETTRE] > d) {
			char ecart = dico->dico[i][DEUXIEME_LETTRE];
			for (j, d; d < ecart; j++, d++) {
				dico->index[j].ind_premiere = PAS_TROUVER;
			}
			dico->index[j].ind_premiere = i;
			indexage_secondaire(dico, d, i);
		}

	}

}


void indexage_secondaire(dictionnaire* dico, char ref, int depart) {

	int ind_lettre_tab = ref - 'A'; // Indice de la case correspondant à la lettre de référence, utilisée pour indexer les mots commençant par cette lettre.

	for (int i = depart, j = 0, d = 'A'; i < taille_dico(dico) && dico->dico[i][PREMIERE_LETTRE] == ref; i++) {

		if (dico->dico[i][DEUXIEME_LETTRE] == d) {
			dico->index[ind_lettre_tab].ind_deuxieme[j] = i;
			j++;
			d++;
		}
		if (dico->dico[i][DEUXIEME_LETTRE] > d) {
			char dernier = dico->dico[i][DEUXIEME_LETTRE];
			for (j, d; d < dernier; j++, d++) {
				dico->index[ind_lettre_tab].ind_deuxieme[j] = PAS_TROUVER;
			}
			dico->index[ind_lettre_tab].ind_deuxieme[j] = i;
		}

	}
}


void affichage_index(const dictionnaire* dico) {
	for (int i = 0; i < TAILLE_ALPHABET; i++)
		printf("l'index pour '%c' : %d\n", 'A' + i, dico->index[i].ind_premiere);
}


int trouver_mot(const dictionnaire* dico, const char* mot) {

	if (bonne_casse(mot) == PAS_TROUVER)
		return PAS_TROUVER;

	int case_lettre_1 = mot[PREMIERE_LETTRE] - 'A';
	int case_lettre_2 = mot[DEUXIEME_LETTRE] - 'A';
	char mot_limite = mot[DEUXIEME_LETTRE] + 1;
	int depart = dico->index[case_lettre_1].ind_deuxieme[case_lettre_2];
	if (depart == PAS_TROUVER) {
		return PAS_TROUVER;
	}

	for (int i = depart; dico->dico[i][DEUXIEME_LETTRE]<mot_limite && i < dico->taille; i++) {
		if (strcmp(dico->dico[i], mot) == 0) {
			return i;
		}
	}
	return PAS_TROUVER;
}

int bonne_casse(const char* mot) {

	int taille_mot = strlen(mot);

	for (int i = 0; i < taille_mot; i++) {
		if (mot[i] < 'A' || mot[i]>'Z')
			return PAS_TROUVER;
	}
	return 1;
}

void rendre_mot_injouable(dictionnaire* dico, int indice) {
	strcpy(dico->dico[indice], "\0");
}
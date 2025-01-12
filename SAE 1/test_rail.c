#include "rail.h"


void test_rail() {
	rail r;
	init_rail(&r);
	assert(t_drn_mot_joue(&r) == RIEN);
	for (int i = 0; i < TAILLE_RAIL-1; i++) {
		ajouter_rail_recto(&r, i, i%2 == 0 ? 'A' : 'B');
	}
	ajouter_rail_recto(&r, TAILLE_RAIL - 1, '\0');
	assert(strcmp(r.recto,"ABABABAB") == 0);
	copie_recto_verso(&r);
	assert(strcmp(r.verso, "BABABABA") == 0);
	copie_verso_recto(&r);
	assert(strcmp(r.recto, "ABABABAB") == 0);
	save_rail(&r);
	assert(strcmp(r.ancien_recto, "ABABABAB") == 0);
	assert(strcmp(r.ancien_verso, "BABABABA") == 0);
	assert(valeur_rail_recto(&r, TEST) == 'B');
	assert(valeur_rail_verso(&r, TEST) == 'A');
	assert(valeur_rail_arecto(&r, TEST - 1) == valeur_rail_recto(&r, TEST - 1));
	assert(valeur_rail_averso(&r, TEST - 1) == valeur_rail_verso(&r, TEST - 1));
	ajouter_rail_verso(&r, TEST, 'Z');
	assert(strcmp(r.ancien_verso, r.verso) != 0);
	ajouter_rail_averso(&r, TEST, 'Z');
	assert(strcmp(r.ancien_verso, r.verso) == 0);
	modif_t_drn_mot_joue(&r, VIDE);
	int acienne_val = valeur_t_drn_mot_joue(&r);
	modif_t_drn_mot_joue(&r, TEST);
	assert(valeur_t_drn_mot_joue(&r)!=acienne_val);

}
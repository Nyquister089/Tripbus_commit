#pragma once
#include "../model/trpdb.h"

typedef enum {
	REVISIONI_SCADUTE,
	CONSULTA_MAGAZZINO,
	INSERT_MODELLO,
	INSERT_RICAMBIO,
	INSERT_MEZZO,
	INSERT_TAGLIANDO, 
	MODIFICA_RICAMBIO, 
	QUIT
}mch_act;

	

extern void show_expired_revisions(struct revisioni_scadute *revisioni_scadute); // Procedura visualizazzione revisioni scadute
extern void show_sparepart(struct ricambio *ricambio); // procedura visualizazzione ricambio
extern void update_sparepart_number(struct ricambio *ricambio);// Procedura modifica quantità in magazzino


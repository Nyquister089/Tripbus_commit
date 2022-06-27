
#pragma once
#include "../model/trpdb.h"

typedef enum {
	VIAGGI_ASSEGNATI,
	METE_VISITATE,
	MAPPE,
	ORARIO_APERTURA,
	AGGIORNA_KM, 
	QUIT
} drvr_act;

extern void get_drvr_actions(void); 
extern bool exe_drvr_act(drvr_act sel); 
extern void show_assigned_trip(struct viaggio *viaggio); 
extern void show_opening_hour(struct meta *meta); 
extern void show_map(struct mappa *mappa); 
extern void update_km(struct mezzo *mezzo); 
extern void show_tour_destination(struct mete_viaggio *mete_viaggio); 
extern void show_destination (struct meta *meta, struct visita *visita, struct viaggio *viaggio);

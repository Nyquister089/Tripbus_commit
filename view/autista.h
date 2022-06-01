
#pragma once
#include "../model/trpdb.h"

typedef enum {
	VIAGGI_ASSEGNATI,
	ORARIO_APERTURA,
	MAPPE,
	AGGIORNA_KM, 
	QUIT
} drvr_act;

extern void get_drvr_actions(void); 
extern bool exe_drvr_act(drvr_act sel); 
extern void show_assigned_trip(struct viaggio *viaggio); 
extern void show_opening_hour(struct meta *meta); 
extern void show_map(struct mappa *mappa); 
extern void update_km(struct mezzo *mezzo); 


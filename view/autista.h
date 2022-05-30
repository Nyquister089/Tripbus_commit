
#pragma once
#include "../model/trpdb.h"

enum actions {
	VIAGGI_ASSEGNATI,
	ORARIO_APERTURA,
	MAPPE,
	AGGIORNA_KM, 
	QUIT
} drv_act;

extern void get_driver_actions(void); 
extern bool exe_drvr_act(drv_act sel); 
extern void show_assigned_trip(struct viaggio *viaggio); 
extern void show_opening_hour(struct meta *meta, struct visita *visita); 
extern void show_map(struct mappa *mappa); 
extern void update_km(struct mezzo *mezzo); 


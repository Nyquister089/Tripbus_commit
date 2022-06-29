
#pragma once
#include "../model/trpdb.h"

typedef enum {
	VIAGGI_ASSEGNATI,
	ORARI_VISITE,
	MAPPE,
	AGGIORNA_KM, 
	QUIT_DRVR
} drvr_act;

extern void run_drvr_interface (void); 

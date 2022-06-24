#pragma once

#include "../model/trpdb.h"

typedef enum  {
	TOUR_INFO,
	METE_TOUR,
	SERVIZI_ALBERGO,
	COMFORT_MODELLO, 
	QUIT_CSTMR
} cstmr_act;

extern void show_tour_information(void);
extern void show_tour_destination(void);
extern void show_service_destination(void);
extern void show_comfort_model(void); 
extern void run_cstmr_interface (void);
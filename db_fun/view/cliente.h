#pragma once

#include "../model/trpdb.h"

typedef enum  {
	TOUR_INFO,
	METE_TOUR,
	VIAGGI_TOUR,
	SERVIZI_ALBERGO,
	COMFORT_MODELLO, 
	QUIT_CSTMR
} cstmr_act;


//extern char select_tour(struct tour *tour);
extern void show_tour_information(struct tour *tour);
/*extern void show_tour_destination(struct mete_tour *mete_tour, struct foto_mete *foto_mete);
extern void show_trip_tour(struct viaggi_tour *viaggi_tour, struct viaggio *viaggio);
extern void show_service_destination(struct servizi_albergo *servizi_albergo);
extern void show_comfort_model(struct comfort_mezzo *comfort_mezzo, struct elenco_modelli *elenco_modelli);*/
extern void run_cstmr_interface (void);
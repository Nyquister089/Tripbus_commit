#pragma once
#include "../model/trpdb.h"

typedef enum{
	INFO_PRENOTAZIONI,
	INSERT_CLIENTE,
	INSERT_PRENOTAZIONE,
	INSERT_POSTPRENOTATO,
	POSTI_VIAGGIO,
	CONFERMA_PRENOTAZIONE, 
	UPDATE_DATA_DOC,
	QUIT
} hstss_act;

extern void show_prenotation_details(struct prenotazione *prenotazione ); 
extern void mod_trip_seat (struct viaggio *viaggio); 
extern void validate_prenotation(struct prenotazione *prenotazione, struct postoprenotato *postoprenotato);
extern void update_d_doc(struct cliente  *cliente); 





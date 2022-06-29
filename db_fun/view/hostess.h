#pragma once
#include <string.h>
#include <mysql/mysql.h>
#include <assert.h>

#include "../model/trpdb.h"

typedef enum{
	INFO_PRENOTAZIONI,
	INSERT_CLIENTE,
	INSERT_PRENOTAZIONE,
	POSTI_VIAGGIO,
	CONFERMA_PRENOTAZIONE, 
	UPDATE_DATA_DOC,
	QUIT_HSST
} hstss_act;
 


extern void run_hstss_interface (void);

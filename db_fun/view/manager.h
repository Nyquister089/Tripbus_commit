#pragma once
#include <string.h>
#include <mysql/mysql.h>
#include <assert.h>

#include "../model/trpdb.h"

typedef enum{
	GESTIONE_DIPENDENTI,
	GESTIONE_TOUR,
	GESTIONE_OFFICINA,
    GESTIONE_CLIENTI,
	QUIT_GEST_GROUP
} gest_act;


typedef enum{
	GESTIONE_SELECT,
	GESTIONE_INSERT,
	GESTIONE_DELETE,
	QUIT_GEST_OP
} gest_op;

typedef enum{
    TABELLA_DIPENDENTI,
    TABELLA_UTENTI,
    TABELLA_ASSOCIATA, 
    TABELLA_OFFRE, 
    TABELLA_SERVIZI,
    TABELLA_TOME,
    TABELLA_FMO, 
    TABELLA_FME,
    QUIT_ANAG
}gest_str;

typedef enum{
    TABELLA_TOUR,
    TABELLA_VIAGGIO, 
    TABELLA_META, 
    TABELLA_VISITA, 
    TABELLA_CAMERA, 
    TABELLA_LOCALITA,
    TABELLA_MAPPA,
    TABELLA_DOCUMENTAZIONEFOTOGRAFICA,
    QUIT_GEST_TOUR
}gest_tour;

typedef enum{
    TABELLA_MODELLO,
    TABELLA_MEZZO, 
    TABELLA_RICAMBIO, 
    TABELLA_REVISIONE, 
    TABELLA_TAGLIANDO,
    TABELLA_COMFORT,
    TABELLA_COMPETENZE,
    QUIT_GEST_OFFICINA
}gest_workshop;

typedef enum{
    TABELLA_CLIENTE,
    TABELLA_PRENOTAZIONE, 
    TABELLA_POSTO_PRENOTATO,
    QUIT_GEST_CLIENTE
}gest_costumer;




 
extern void run_mngr_interface (void);

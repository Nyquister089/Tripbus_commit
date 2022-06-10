#pragma once
#include <stdbool.h>
#include <stdlib.h>	

#include "../utils/io.h"

extern bool init_db(void);
extern void fini_db(void);
							
#define DATE_LEN 11
#define TIME_LEN 6
#define DATETIME_LEN (DATE_LEN + TIME_LEN)
#define NUM_LEN 45
#define DEC_LEN 45 
#define USERNAME_LEN 45
#define PASSWORD_LEN 8
#define PIC 45
#define BIT_LEN 2
#define VARCHAR_LEN 45
#define DES_LEN 5000

struct credentials {
	char username[USERNAME_LEN];
	char password[PASSWORD_LEN];
};

typedef enum {
	LOGIN_ROLE,
	AUTISTA,
	CLIENTE,
	HOSTESS,
	MECCANICO,
	FAILED_LOGIN
} role_t;

extern void db_switch_to_login(void);
extern role_t attempt_login(struct credentials *cred);
extern void db_switch_to_administrator(void);

struct associata{
	char  cameraprenotata[NUM_LEN]; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char  ospite[NUM_LEN]; 						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char  albergoinquestione[NUM_LEN]; 			//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct camera {
	char numerocamera [NUM_LEN];//Corretto trasformandolo da carattere a puntatore di carattere
	char albergo [NUM_LEN];						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char tipologia[VARCHAR_LEN];
	char costo [NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	
};

struct cliente {
	char emailcliente[VARCHAR_LEN];
	char nomecliente[VARCHAR_LEN];
	char cognomecliente[VARCHAR_LEN];
	char indirizzocliente[VARCHAR_LEN];
	char codicefiscale[VARCHAR_LEN];
	char datadocumentazione[DATETIME_LEN];
	int recapitotelefonico; //Corretto trasformandolo da carattere a puntatore di carattere
	int fax; //Corretto trasformandolo da carattere a puntatore di carattere
};

struct comfort {
	char idcomfort [NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomecomfort[VARCHAR_LEN]; 
	char descrizionecomfort[DES_LEN]; 

};

struct comfort_mezzo{
	size_t num_comfort; 
	struct comfort comfort_mezzo[]; 
};

struct competenze {
	char meccanicocompetente [NUM_LEN]; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char modelloassociato [NUM_LEN]; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct dipendente{
	char iddipendente [NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomedipendente[VARCHAR_LEN];
	char cognomedipendente[VARCHAR_LEN];
	char tipologiadipendente[VARCHAR_LEN];
	char telefonoaziendale [NUM_LEN];  //Corretto trasformandolo da carattere a puntatore di carattere
};

struct documentazionefotografica {
	 char idfoto [NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	 char foto [PIC]; 
	 
};

struct foto_mete {
	size_t num_pic;
	struct documentazionefotografica foto_mete[]; 
}; 

struct localita {
	char nomelocalita[VARCHAR_LEN];
	char regione[VARCHAR_LEN];
	char stato[VARCHAR_LEN];
};

struct mappa {
	char idmappa[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char citta[VARCHAR_LEN];
	char livellodidettaglio[VARCHAR_LEN];
	char zona[VARCHAR_LEN];
	char localitarappresentata[VARCHAR_LEN]; 		//FK
};

struct meta { 
	char idmeta[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomemeta[VARCHAR_LEN]; 
	char emailmeta[VARCHAR_LEN]; 
	char telefonometa[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char faxmeta[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char indirizzo[VARCHAR_LEN]; 
	char tipologiameta[VARCHAR_LEN]; 
	char categoriaalbergo[VARCHAR_LEN]; 
	char orariodiapertura[TIME_LEN]; 
	char localitadiappartenenza[VARCHAR_LEN]; 		//FK
};

struct mete_tour{ 
	size_t num_met; 
  	struct  meta mete_tour [];
};

struct mete_viaggio{	
	size_t num_vme; 
	struct meta mete_viaggio[]; 
}; 

struct mezzo {
	char targa[VARCHAR_LEN];
	char modellomezzo[NUM_LEN]; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char ingombri[VARCHAR_LEN];	
	char autonomia[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char valorecontakm[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char dataultimarevisioneinmotorizzazione[DATE_LEN]; 
	char dataimmatricolazione[DATE_LEN]; 
};

struct modello {
	char idmodello[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomemodello[VARCHAR_LEN];
	char datitecnici[DES_LEN]; 
	char casacostruttrice[VARCHAR_LEN];
	char numeroposti[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct elenco_modelli {
	size_t num_modelli; 
	struct modello elenco_modelli[]; 
};

struct offre {
	char servizi[NUM_LEN]; 						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char albergoofferente[NUM_LEN]; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct postoprenotato {
	char numerodiposto[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char viaggioassociato[NUM_LEN]; 					//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	char prenotazioneassociata[NUM_LEN]; 				//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	char etapasseggero[NUM_LEN];  //Corretto trasformandolo da carattere a puntatore di carattere
	char nomepasseggero[VARCHAR_LEN]; 
	char cognomepasseggero[VARCHAR_LEN]; 
}; 

struct prenotazione {
	char numerodiprenotazione[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char clienteprenotante[VARCHAR_LEN]; 			//FK
	char datadiprenotazione[DATE_LEN]; 
	char datadiconferma[DATE_LEN]; 
	char datasaldo[DATE_LEN]; 
}; 

struct presenti {
	char comfortpresenti[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char modelloassciato[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
};

struct revisione {
	char idrevisione[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char mezzorevisionato[VARCHAR_LEN]; 			// Fk
	char addettoallarevisione[NUM_LEN];  				// Fk //Corretto trasformandolo da carattere a puntatore di carattere
	char datainizio[DATE_LEN]; 
	char datafine[DATE_LEN]; 
	char chilometraggio[NUM_LEN];//Corretto trasformandolo da carattere a puntatore di carattere
	char operazionieseguite[DES_LEN]; 
	char tipologiarevisione[VARCHAR_LEN]; 
	char motivazione[VARCHAR_LEN]; 
};
struct revisioni_scadute {
	size_t num_revisione; 
	struct revisione revisioni_scadute [];
};
struct ricambio {
	char codice [VARCHAR_LEN]; 
	char costounitario[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char quantitadiriordino[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char descrizione[DES_LEN]; 
	char scortaminima[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char quantitainmagazzino[NUM_LEN];  //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct rt {
	char  revisionerelativa[NUM_LEN]; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char  tagliandoassociato[NUM_LEN]; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct servizio {
	char idservizio[NUM_LEN]; 
	char nomeservizio[VARCHAR_LEN];
	char descrizioneservizio[DES_LEN]; 
}; 

struct  servizi_albergo{
	size_t num_servizi; 
	struct servizio servizi_albergo[]; 
};

struct sostituito{
	char revisioneassociata[NUM_LEN]; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char ricambioutilizzato [VARCHAR_LEN]; 			//FK
}; 


struct tagliando {
	char idtagliando[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char tipologiatagliando[VARCHAR_LEN]; 
	char validitasuperate[DES_LEN];
}; 

struct tome {
	char tourinquestione[VARCHAR_LEN]; 
	char metainquestione[NUM_LEN];  //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct tour {
	char denominazionetour[VARCHAR_LEN]; 
	char descrizionetour[DES_LEN]; 
	char minimopartecipanti[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char assicurazionemedica[DEC_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char bagaglio[DEC_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char accompagnatrice[VARCHAR_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct viaggio {
	unsigned int idviaggio; //Corretto trasformandolo da carattere a puntatore di carattere
	char tourassociato[VARCHAR_LEN]; 
	char conducente[NUM_LEN]; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char accompagnatrice[NUM_LEN]; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char mezzoimpiegato[VARCHAR_LEN]; 			// FK
	char datadipartenzaviaggio[DATETIME_LEN]; 
	char datadiritornoviaggio[DATETIME_LEN]; 
	char costodelviaggio[NUM_LEN];  //Corretto trasformandolo da carattere a puntatore di carattere
	char numerodikm[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char postidisponibili[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiannullamento[DATETIME_LEN]; 
};
struct viaggi_tour{
	size_t num_viaggi; 
	struct viaggio viaggi_tour[]; 
};
struct assigned_trip{
	size_t num_entries; //Corretto trasformandolo da carattere a puntatore di carattere
	struct viaggio assigned_trip[]; 
	
};

struct visita {
	char idvisita[NUM_LEN];  //Corretto trasformandolo da carattere a puntatore di carattere
	char viaggiorelativo[NUM_LEN]; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char metavisitata[NUM_LEN]; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiarrivo[DATE_LEN]; 
	char datadipartenza[DATE_LEN]; 
	char oradiarrivo[TIME_LEN]; 
	char oradipartenza[TIME_LEN]; 
	char guida[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char supplemento[NUM_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char trattamentoalberghiero[VARCHAR_LEN]; 
}; 


extern void do_insert_costumer(struct cliente *cliente);
extern void do_insert_reservation(struct prenotazione *prenotazione);
extern void do_insert_seat(struct postoprenotato *postoprenotato);
extern void do_insert_assoc(struct associata *associata);

extern void do_update_trip_seat(struct viaggio *viaggio);

extern void do_select_trip(struct viaggio *viaggio);
extern void do_select_costumer(struct cliente *cliente);
extern void do_select_reservation(struct prenotazione *prenotazione);

extern void do_update_data_doc(struct cliente *cliente); 
extern void do_validate_reservation(struct prenotazione *prenotazione); 

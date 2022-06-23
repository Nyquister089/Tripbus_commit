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
#define TAR_LEN 10
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
	QUIT,
	FAILED_LOGIN
} role_t;

extern void db_switch_to_login(void);
extern role_t attempt_login(struct credentials *cred);
extern void db_switch_to_administrator(void);

struct associata{
	int  cameraprenotata; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  ospite; 						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	int  albergoinquestione; 			//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char datainiziosoggiorno[DATE_LEN]; 
	char datafinesoggiorno[DATE_LEN];
}; 

struct camera {
	int numerocamera;//Corretto trasformandolo da carattere a puntatore di carattere
	int albergo;						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char tipologia[VARCHAR_LEN];
	float costo ; //Corretto trasformandolo da carattere a puntatore di carattere
	
};

struct cliente {
	char emailcliente[VARCHAR_LEN];
	char nomecliente[VARCHAR_LEN];
	char cognomecliente[VARCHAR_LEN];
	char indirizzocliente[VARCHAR_LEN];
	char codicefiscale[VARCHAR_LEN];
	char datadocumentazione[DATE_LEN];
	char recapitotelefonico[VARCHAR_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
	char fax[VARCHAR_LEN]; //Corretto trasformandolo da carattere a puntatore di carattere
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

struct mete_viaggio{	
	size_t num_vme; 
	struct meta mete_viaggio[]; 
}; 

struct mezzo {
	char targa[TAR_LEN];
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
	int numerodiposto; //Corretto trasformandolo da carattere a puntatore di carattere
	int viaggioassociato; 					//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	int prenotazioneassociata; 				//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	int etapasseggero;  //Corretto trasformandolo da carattere a puntatore di carattere
	char nomepasseggero[VARCHAR_LEN]; 
	char cognomepasseggero[VARCHAR_LEN]; 
}; 

struct prenotazione {
	int numerodiprenotazione; //Corretto trasformandolo da carattere a puntatore di carattere
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
	int minimopartecipanti; //Corretto trasformandolo da carattere a puntatore di carattere
	float assicurazionemedica; //Corretto trasformandolo da carattere a puntatore di carattere
	float bagaglio; //Corretto trasformandolo da carattere a puntatore di carattere
	float garanziaannullamento; 
	signed char accompagnatrice; //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct viaggio {
	int idviaggio; //Corretto trasformandolo da carattere a puntatore di carattere
	char tourassociato[VARCHAR_LEN]; 
	int conducente; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	int accompagnatrice; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char mezzoimpiegato[TAR_LEN]; 			// FK
	char datadipartenzaviaggio[DATETIME_LEN]; 
	char datadiritornoviaggio[DATETIME_LEN]; 
	float costodelviaggio;  //Corretto trasformandolo da carattere a puntatore di carattere
	int numerodikm; //Corretto trasformandolo da carattere a puntatore di carattere
	int postidisponibili; //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiannullamento[DATETIME_LEN]; 
};

struct tour_viaggi{
	char denominazionetour[VARCHAR_LEN]; 
	char descrizionetour[DES_LEN]; 
	int minimopartecipanti; //Corretto trasformandolo da carattere a puntatore di carattere
	float assicurazionemedica; //Corretto trasformandolo da carattere a puntatore di carattere
	float bagaglio; //Corretto trasformandolo da carattere a puntatore di carattere
	float garanziaannullamento; 
	signed char accompagnatrice;
	char datadipartenzaviaggio[DATETIME_LEN]; 
	char datadiritornoviaggio[DATETIME_LEN]; 
	float costodelviaggio;
	int postidisponibili;
	int codiceviaggio; 
}; 

struct tour_info{
	size_t num_tour; 
	struct tour_viaggi tour_info[]; 
}; 


struct visita {
	int idvisita;  //Corretto trasformandolo da carattere a puntatore di carattere
	int viaggiorelativo; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	int metavisitata; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiarrivo[DATE_LEN]; 
	char datadipartenza[DATE_LEN]; 
	char oradiarrivo[TIME_LEN]; 
	char oradipartenza[TIME_LEN]; 
	signed char guida; //Corretto trasformandolo da carattere a puntatore di carattere
	float supplemento; //Corretto trasformandolo da carattere a puntatore di carattere
	char trattamentoalberghiero[VARCHAR_LEN]; 
}; 
struct mete_tour{
	char nome[VARCHAR_LEN];
	char darrivo[DATE_LEN];
	char oarrivo[TIME_LEN];
	char dpartenza[DATE_LEN];
   	char opartenza[TIME_LEN];
   	float supplemento;
	char tipologiameta[VARCHAR_LEN];
	signed char guida;
   	char oapertura[TIME_LEN];
   	char trattamento[VARCHAR_LEN];
	char categoriaalbergo[VARCHAR_LEN];
}; 

struct info_mete{
	size_t num_mete; 
	struct mete_tour info_mete[]; 
};

extern void do_insert_costumer(struct cliente *cliente);
extern void do_insert_reservation(struct prenotazione *prenotazione);
extern void do_insert_seat(struct postoprenotato *postoprenotato);
extern void do_insert_assoc(struct associata *associata);

extern void do_update_trip_seat(struct viaggio *viaggio);

extern void do_select_trip(struct viaggio *viaggio);
extern void do_select_costumer(struct cliente *cliente);
extern void do_select_reservation(struct prenotazione *prenotazione);
extern void do_select_tour( struct tour *tour);

extern struct tour_info *get_tour_info (void);
extern struct info_mete *get_mete_info(int idv);

extern void do_update_data_doc(struct cliente *cliente); 
extern void do_validate_reservation(struct prenotazione *prenotazione); 

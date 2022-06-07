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
#define PASSWORD_LEN 45
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
	AMMINISTRATORE,
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
	char *cameraprenotata; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char *ospite; 						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char *albergoinquestione; 			//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct camera {
	char *numerocamera;//Corretto trasformandolo da carattere a puntatore di carattere
	char *albergo;						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char tipologia[VARCHAR_LEN];
	char *costo; //Corretto trasformandolo da carattere a puntatore di carattere
	
};

//extern void do_register_flight(struct flight *flight);


struct cliente {
	char emailcliente[VARCHAR_LEN];
	char nomecliente[VARCHAR_LEN];
	char cognomecliente[VARCHAR_LEN];
	char indirizzocliente[VARCHAR_LEN];
	char codicefiscale[VARCHAR_LEN];
	char datadocumentazione[DATETIME_LEN];
	char *recapitotelefonico; //Corretto trasformandolo da carattere a puntatore di carattere
	char *fax; //Corretto trasformandolo da carattere a puntatore di carattere
};

struct comfort {
	char *idcomfort; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomecomfort[VARCHAR_LEN]; 
	char descrizionecomfort[DES_LEN]; 

};

struct comfort_mezzo{
	size_t num_comfort; 
	struct comfort comfort_mezzo[]; 
};

struct competenze {
	char *meccanicocompetente; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char *modelloassociato; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

//extern struct occupancy *do_get_occupancy(void);
//extern void occupancy_dispose(struct occupancy *occupancy);


//extern void db_switch_to_agency(void);


struct dipendente{
	char *iddipendente; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomedipendente[VARCHAR_LEN];
	char cognomedipendente[VARCHAR_LEN];
	char tipologiadipendente[VARCHAR_LEN];
	char *telefonoaziendale;  //Corretto trasformandolo da carattere a puntatore di carattere
};

//externchar  do_booking(struct booking *info);

struct documentazionefotografica {
	 char *idfoto; //Corretto trasformandolo da carattere a puntatore di carattere
	 char foto [PIC]; 
	 
};

struct foto_mete {
	size_t num_pic;
	struct documentazionefotografica foto_mete[]; 
}; 


struct foto_modelli {
	char *modellorappresentato; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char *fotomodello; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct localita {
	char nomelocalita[VARCHAR_LEN];
	char regione[VARCHAR_LEN];
	char stato[VARCHAR_LEN];
};

struct mappa {
	char *idmappa; //Corretto trasformandolo da carattere a puntatore di carattere
	char citta[VARCHAR_LEN];
	char livellodidettaglio[VARCHAR_LEN];
	char zona[VARCHAR_LEN];
	char localitarappresentata[VARCHAR_LEN]; 		//FK
};

struct meta { 
	char *idmeta; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomemeta[VARCHAR_LEN]; 
	char emailmeta[VARCHAR_LEN]; 
	char *telefonometa; //Corretto trasformandolo da carattere a puntatore di carattere
	char *faxmeta; //Corretto trasformandolo da carattere a puntatore di carattere
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
	char  * modellomezzo; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char ingombri[VARCHAR_LEN];	
	char  *autonomia; //Corretto trasformandolo da carattere a puntatore di carattere
	char  *valorecontakm; //Corretto trasformandolo da carattere a puntatore di carattere
	char dataultimarevisioneinmotorizzazione[DATE_LEN]; 
	char dataimmatricolazione[DATE_LEN]; 
};

struct modello {
	char *idmodello; //Corretto trasformandolo da carattere a puntatore di carattere
	char nomemodello[VARCHAR_LEN];
	char datitecnici[DES_LEN]; 
	char casacostruttrice[VARCHAR_LEN];
	char *numeroposti; //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct elenco_modelli {
	size_t num_modelli; 
	struct modello elenco_modelli[]; 
};

struct offre {
	char *servizi; 						//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char *albergoofferente; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct postoprenotato {
	char *numerodiposto; //Corretto trasformandolo da carattere a puntatore di carattere
	char *viaggioassociato; 					//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	char *prenotazioneassociata; 				//Fk //Corretto trasformandolo da carattere a puntatore di carattere
	char *etapasseggero;  //Corretto trasformandolo da carattere a puntatore di carattere
	char nomepasseggero[VARCHAR_LEN]; 
	char cognomepasseggero[VARCHAR_LEN]; 
}; 

struct prenotazione {
	char *numerodiprenotazione; //Corretto trasformandolo da carattere a puntatore di carattere
	char clienteprenotante[VARCHAR_LEN]; 			//FK
	char datadiprenotazione[DATE_LEN]; 
	char datadiconferma[DATE_LEN]; 
	char datasaldo[DATE_LEN]; 
}; 

struct presenti {
	char *comfortpresenti; //Corretto trasformandolo da carattere a puntatore di carattere
	char *modelloassciato; //Corretto trasformandolo da carattere a puntatore di carattere
};

struct revisione {
	char *idrevisione; //Corretto trasformandolo da carattere a puntatore di carattere
	char mezzorevisionato[VARCHAR_LEN]; 			// Fk
	char *addettoallarevisione;  				// Fk //Corretto trasformandolo da carattere a puntatore di carattere
	char datainizio[DATE_LEN]; 
	char datafine[DATE_LEN]; 
	char *chilometraggio;//Corretto trasformandolo da carattere a puntatore di carattere
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
	char *costounitario; //Corretto trasformandolo da carattere a puntatore di carattere
	char *quantitadiriordino; //Corretto trasformandolo da carattere a puntatore di carattere
	char descrizione[DES_LEN]; 
	char *scortaminima; //Corretto trasformandolo da carattere a puntatore di carattere
	char *quantitainmagazzino;  //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct rt {
	char  *revisionerelativa; 					//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char  *tagliandoassociato; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
}; 

struct servizio {
	char* idservizio; 
	char nomeservizio[VARCHAR_LEN];
	char descrizioneservizio[DES_LEN]; 
}; 

struct  servizi_albergo{
	size_t num_servizi; 
	struct servizio servizi_albergo[]; 
};

struct sostituito{
	char *revisioneassociata; 				//FK //Corretto trasformandolo da carattere a puntatore di carattere
	char ricambioutilizzato [VARCHAR_LEN]; 			//FK
}; 


struct tagliando {
	char *idtagliando; //Corretto trasformandolo da carattere a puntatore di carattere
	char tipologiatagliando[VARCHAR_LEN]; 
	char validitasuperate[DES_LEN];
}; 

struct tome {
	char tourinquestione[VARCHAR_LEN]; 
	char *metainquestione;  //Corretto trasformandolo da carattere a puntatore di carattere
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
	char *idviaggio; //Corretto trasformandolo da carattere a puntatore di carattere
	char tourassociato[VARCHAR_LEN]; 
	char *conducente; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char *accompagnatrice; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char mezzoimpiegato[VARCHAR_LEN]; 			// FK
	char datadipartenzaviaggio[DATETIME_LEN]; 
	char datadiritornoviaggio[DATETIME_LEN]; 
	char *costodelviaggio;  //Corretto trasformandolo da carattere a puntatore di carattere
	char *numerodikm; //Corretto trasformandolo da carattere a puntatore di carattere
	char *postidisponibili; //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiannullamento[DATETIME_LEN]; 
};
struct viaggi_tour{
	size_t num_viaggi; 
	struct viaggio viaggi_tour[]; 
};
struct assigned_trip{
	char *num_entries; //Corretto trasformandolo da carattere a puntatore di carattere
	struct viaggio assigned_trip[]; 
	
};

extern struct assigned_trip *do_get_occupancy(void); 
extern void assigned_trip_dispose (struct assigned_trip *assigned_trip); 

struct visita {
	char *idvisita;  //Corretto trasformandolo da carattere a puntatore di carattere
	char *viaggiorelativo; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char *metavisitata; 					// FK //Corretto trasformandolo da carattere a puntatore di carattere
	char datadiarrivo[DATE_LEN]; 
	char datadipartenza[DATE_LEN]; 
	char oradiarrivo[TIME_LEN]; 
	char oradipartenza[TIME_LEN]; 
	char *guida; //Corretto trasformandolo da carattere a puntatore di carattere
	char *supplemento; //Corretto trasformandolo da carattere a puntatore di carattere
	char trattamentoalberghiero[VARCHAR_LEN]; 
}; 

extern void do_insert_tour( struct tour *tour);
extern void do_insert_destination(struct meta *meta);
extern void do_insert_trip(struct viaggio *viaggio);
extern void do_insert_visit(struct visita *visita);
extern void do_insert_picture(struct documentazionefotografica *documentazionefotografica);
extern void do_insert_employee(struct dipendente *dipendente);
extern void do_insert_room(struct camera *camera);
extern void do_insert_location(struct localita *localita);
extern void do_insert_map(struct mappa *mappa);
extern void do_insert_costumer(struct cliente *cliente);
extern void do_insert_reservation(struct prenotazione *prenotazione);
extern void do_insert_seat(struct postoprenotato *postoprenotato);
extern void do_insert_review(struct revisione *revisione);
extern void do_insert_model(struct modello *modello);
extern void do_insert_sparepart(struct ricambio *ricambio);
extern void do_insert_bus(struct mezzo *mezzo);
extern void do_insert_certify(struct tagliando *tagliando);
extern void do_insert_comfort(struct comfort *comfort);
extern void do_insert_service(struct servizio *servizio);
extern void do_delete_tour( struct tour *tour);
extern void do_delete_destination(struct meta *meta);
extern void do_delete_trip(struct viaggio *viaggio);
extern void do_delete_visit(struct visita *visita);
extern void do_delete_picture(struct documentazionefotografica *documentazionefotografica);
extern void do_delete_employee(struct dipendente *dipendente);
extern void do_delete_room(struct camera *camera);
extern void do_delete_location(struct localita *localita);
extern void do_delete_map(struct mappa *mappa);
extern void do_delete_costumer(struct cliente *cliente);
extern void do_delete_reservation(struct prenotazione *prenotazione);
extern void do_delete_seat(struct postoprenotato *postoprenotato);
extern void do_delete_review(struct revisione *revisione);
extern void do_delete_model(struct modello *modello);
extern void do_delete_sparepart(struct ricambio *ricambio);
extern void do_delete_bus(struct mezzo *mezzo);
extern void do_delete_certify(struct tagliando *tagliando);
extern void do_delete_service(struct servizio *servizio);
extern void do_delete_comfort(struct comfort *comfort);
extern void do_update_tour( struct tour *tour);
extern void do_update_destination(struct meta *meta);
extern void do_update_trip(struct viaggio *viaggio);
extern void do_update_visit(struct visita *visita);
extern void do_update_picture(struct documentazionefotografica *documentazionefotografica);
extern void do_update_employee(struct dipendente *dipendente);
extern void do_update_room(struct camera *camera);
extern void do_update_location(struct localita *localita);
extern void do_update_map(struct mappa *mappa);
extern void do_update_costumer(struct cliente *cliente);
extern void do_update_reservation(struct prenotazione *prenotazione);
extern void do_update_seat(struct postoprenotato *postoprenotato);
extern void do_update_review(struct revisione *revisione);
extern void do_update_model(struct modello *modello);
extern void do_update_sparepart(struct ricambio *ricambio);
extern void do_update_bus(struct mezzo *mezzo);
extern void do_update_certify(struct tagliando *tagliando);
extern void do_update_service(struct servizio *servizio);
extern void do_update_comfort(struct comfort *comfort);
extern void do_update_trip_seat(struct viaggio *viaggio);
extern void do_update_pullman_km(struct mezzo *mezzo);
extern void do_update_sparepart_number(struct ricambio *ricambio);
extern void do_select_tour( struct tour *tour);
extern void do_select_destination(struct meta *meta);
extern void do_select_trip(struct viaggio *viaggio);
extern void do_select_visit(struct visita *visita);
extern void do_select_picture(struct documentazionefotografica *documentazionefotografica);
extern void do_select_employee(struct dipendente *dipendente);
extern void do_select_room(struct camera *camera);
extern void do_select_location(struct localita *localita);
extern void do_select_map(struct mappa *mappa);
extern void do_select_costumer(struct cliente *cliente);
extern void do_select_reservation(struct prenotazione *prenotazione);
extern void do_select_seat(struct postoprenotato *postoprenotato);
extern void do_select_review(struct revisione *revisione);
extern void do_select_model(struct modello *modello);
extern void do_select_sparepart(struct ricambio *ricambio);
extern void do_select_bus(struct mezzo *mezzo);
extern void do_select_certify(struct tagliando *tagliando);
extern void do_select_service(struct servizio *servizio);
extern void do_select_comfort(struct comfort *comfort);
extern void do_select_assigned_trip(struct viaggio *viaggio);
extern void do_select_visit_details(struct visita *visita, struct documentazionefotografica *documentazionefotografica);
extern void do_select_tour_destination(struct tour *tour, struct meta *meta, struct documentazionefotografica *documentazionefotografica);
extern void do_select_model_comfort(struct modello *modello, struct comfort *comfort);
extern void do_select_hotel_service(struct meta *meta, struct servizio *servizio);
extern void do_select_expired_review(struct revisione *revisione);
extern void do_select_spareparts_warehouse(struct ricambio *ricambio);
extern void do_update_data_doc(struct cliente *cliente); 
extern void do_validate_reservation(struct prenotazione *prenotazione); 
extern void do_insert_assoc(struct associata *associata); 
extern void do_select_trip_destination(struct meta *meta, struct viaggio *viaggio, struct visita *visita); 





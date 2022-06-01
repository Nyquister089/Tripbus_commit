#include <stdlib.h> //CONFRONTARE CON db IN model
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <assert.h>


#include "trpdb.h"
#include "../utils/db.h"

static MYSQL *conn;

static MYSQL_STMT *login_procedure;


static MYSQL_STMT *insert_costumer; 
static MYSQL_STMT *insert_reservation; 
static MYSQL_STMT *insert_seat; 
static MYSQL_STMT *insert_review; 
static MYSQL_STMT *insert_model; 
static MYSQL_STMT *insert_bus; 
static MYSQL_STMT *insert_sparepart; 
static MYSQL_STMT *insert_certify;

static MYSQL_STMT *validate_reservation; 


static MYSQL_STMT *select_tour;
static MYSQL_STMT *select_destination;
static MYSQL_STMT *select_trip;
static MYSQL_STMT *select_visit; 
static MYSQL_STMT *select_picture; 
static MYSQL_STMT *select_room; 
static MYSQL_STMT *select_location;
static MYSQL_STMT *select_map;
static MYSQL_STMT *select_costumer; 
static MYSQL_STMT *select_reservation; 
static MYSQL_STMT *select_seat; 
static MYSQL_STMT *select_review; 
static MYSQL_STMT *select_model; 
static MYSQL_STMT *select_bus; 
static MYSQL_STMT *select_sparepart; 
static MYSQL_STMT *select_certify;
static MYSQL_STMT *select_comfort;
static MYSQL_STMT *select_service;

// Statement speciali

static MYSQL_STMT *update_trip_seat;
static MYSQL_STMT *update_pullman_km; 
static MYSQL_STMT *update_sparepart_number; 

static MYSQL_STMT *select_assigned_trip; // procedura che seleziona il tuor in base a data e conducente
static MYSQL_STMT *select_visit_details; // procedure che selezione la visita e le foto ad essa associate in base a meta e data del viaggio 
static MYSQL_STMT *select_tour_destination; // procedura che seleziona le mete relative ad un tour 
static MYSQL_STMT *select_model_comfort;  // procedura che seleziona le mete relative 
static MYSQL_STMT *select_hotel_service;  // procedura che seleziona i servizi offerti da un albergo 
static MYSQL_STMT *select_expired_review; // procedura che seleziona i mezzi che hanno effettuato una revisione ordinaria da più di 6 mesi 
static MYSQL_STMT *select_sparepart_warehouse; // procedura che seleziona i ricambi la cui quantità in magazzino è inferiore alla scorta minima 

static void close_prepared_stmts(void)
{
	if(login_procedure) {
		mysql_stmt_close(login_procedure);
		login_procedure = NULL;
	}
		
	if(select_tour) {				// Procedura di update tour
		mysql_stmt_close(select_tour);
		select_tour = NULL;
	}						
	
	if(select_destination) {			// Procedura di select destinazione
		mysql_stmt_close(select_destination);
		select_destination = NULL;
	}						
	
	if(select_trip) {				// Procedura di select viaggi
		mysql_stmt_close(select_trip);
		select_trip = NULL;
	}				

	if(select_visit) {				// Procedura di select visita
		mysql_stmt_close(select_visit);
		select_visit = NULL;
	}							
	if(select_picture) {				// Procedura di select foto
		mysql_stmt_close(select_picture);
		select_picture = NULL;
	}									
	if(select_room) {				// Procedura di select camere
		mysql_stmt_close(select_room);
		select_room = NULL;
	}				
	if(select_location) {				// Procedura di select localita
		mysql_stmt_close(select_location);
		select_location = NULL;
	}						
	if(select_map) {				// Procedura di select mappe
		mysql_stmt_close(select_map);
		select_map = NULL;
	}	
					
	if(select_assigned_trip) {			// Procedura di visualizzazione viaggi assegnati (AUTISTA)
		mysql_stmt_close(select_assigned_trip);
		select_assigned_trip = NULL;
	}
	if(select_visit_details) {			// Procedura di visualizzazione dettagli visite (AUTISTA, CLIENTE) 
		mysql_stmt_close(select_visit_details);
		select_visit_details = NULL;
	}

	if(update_pullman_km) {				// Procedura di update chilometraggio pullman (AUTISTA, MECCANICO)
		mysql_stmt_close(update_pullman_km);
		update_pullman_km = NULL;
	}
	
	if(select_tour_destination) {			// Procedura di visualiazzazione mete incluse in un tour(CLIENTE) 
		mysql_stmt_close(select_tour_destination);
		select_tour_destination= NULL;
	}
	if(select_model_comfort) {			// Procedura di visualiazzazione comfort di un modello (CLIENTE) 
		mysql_stmt_close(select_model_comfort);
		select_model_comfort= NULL;
	}
	if(select_hotel_service) {			// Procedura di visualiazzazione servizi di un albergo (CLIENTE) 
		mysql_stmt_close(select_hotel_service);
		select_hotel_service= NULL;
	}
	if(select_picture) {				// Procedura di visualizzazione foto modelli/mete (CLIENTE)
		mysql_stmt_close(select_picture); 
		select_picture = NULL; 
	}
	if(insert_costumer) {				// Procedura di insert cliente (HOSTESS) 
		mysql_stmt_close(insert_costumer);
		insert_costumer= NULL;
	}
	if(insert_reservation) {			// Procedura di insert prenotazione (HOSTESS) 
		mysql_stmt_close(insert_reservation);
		insert_reservation= NULL;
	}
	if(insert_seat) {				// Procedura di insert posto prenotato (HOSTESS) 
		mysql_stmt_close(insert_seat);
		insert_seat= NULL;
	}
	if(select_costumer) {				// Procedura select cliente (HOSTESS) 
		mysql_stmt_close(select_costumer);
		select_costumer= NULL;
	}
	if(validate_reservation) {			// Procedura update  prenotazione (HOSTESS) 
		mysql_stmt_close(validate_reservation);
		validate_reservation= NULL;
	}
	if(select_reservation) {			// Procedura select  prenotazione (HOSTESS) 
		mysql_stmt_close(select_reservation);
		select_reservation= NULL;
	}
	if(select_seat) {				// Procedura select posto prenotato (HOSTESS) 
		mysql_stmt_close(select_seat);
		select_seat= NULL;
	}
	if(select_seat) {				// Procedura select posto prenotato (HOSTESS) 
		mysql_stmt_close(select_seat);
		select_seat= NULL;
	}
	
	if(select_expired_review) {			// Procedura di visualiazzazione revisioni scadute (MECCANICO) 
		mysql_stmt_close(select_expired_review);
		select_expired_review= NULL;
	}
	
	if(select_sparepart_warehouse) {			// Procedura di visualiazzazione ricambi in magazzino(MECCANICO) 
		mysql_stmt_close(select_sparepart_warehouse);
		select_sparepart_warehouse= NULL;
	}

	if(insert_review) {				// Procedura  insert revisione (MECCANICO) 
		mysql_stmt_close(insert_review);
		 insert_review= NULL;
	}
	if(insert_model) {				// Procedura  insert modelli (MECCANICO) 
		mysql_stmt_close(insert_model);
		 insert_model= NULL;
	}
	if(insert_sparepart) {				// Procedura  insert ricambi in magazzino(MECCANICO) 
		mysql_stmt_close(insert_sparepart);
		 insert_sparepart= NULL;
	}
	if(insert_bus) {				// Procedura  insert mezzo(MECCANICO) 
		mysql_stmt_close(insert_bus);
		 insert_bus= NULL;
	}
	if(insert_certify) {				// Procedura  insert tagliando(MECCANICO) 
		mysql_stmt_close(insert_certify);
		 insert_certify= NULL;
	}
	if(select_review) {				// Procedura  select revisione (MECCANICO) 
		mysql_stmt_close(select_review);
		 select_review= NULL;
	}
	if(select_model) {				// Procedura  select modelli (MECCANICO) 
		mysql_stmt_close(select_model);
		 select_model= NULL;
	}
	if(select_sparepart) {				// Procedura  select ricambi in magazzino(MECCANICO) 
		mysql_stmt_close(select_sparepart);
		select_sparepart= NULL;
	}
	if(select_bus) {				// Procedura  select mezzo(MECCANICO) 
		mysql_stmt_close(select_bus);
		select_bus= NULL;
	}
	if(select_certify) {				// Procedura  select tagliando(MECCANICO) 
		mysql_stmt_close(select_certify);
		select_certify= NULL;
	}
	if(update_trip_seat) {				// Procedura  update tagliando(MECCANICO) 
		mysql_stmt_close(update_trip_seat);
		update_trip_seat= NULL;
	}
	if(update_sparepart_number) {				// Procedura  update numero di pezzi di ricambio(MECCANICO) 
		mysql_stmt_close(update_sparepart_number);
		update_sparepart_number= NULL;
	}
	if(select_comfort) {				// Procedura  select comfort
		mysql_stmt_close(select_comfort);
		select_comfort= NULL;
	}
	if(select_service) {				// Procedura  select servizio
		mysql_stmt_close(select_service);
		select_service= NULL;
	}

}

static bool initialize_prepared_stmts(role_t for_role)
{
	switch(for_role) {

		case LOGIN_ROLE:
			if(!setup_prepared_stmt(&login_procedure, "call login(?, ?, ?)", conn)) {
				print_stmt_error(login_procedure, "Unable to initialize login statement\n");
				return false;
			}
			break;
			
		case AUTISTA:
			// Consultazione viaggi e mezzi a cui sono assegnati 
			// consultazione orario beni turistici 
			// Aggiornare il numero di km percorsi dal pullman utilizzato per un viaggio
			if(!setup_prepared_stmt(&select_assigned_trip, "call select_assigned_trip(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_assigned_trip, "Unable to initialize select_assigned_trip statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_visit_details, "call select_visit_details()", conn)) {
				print_stmt_error(select_visit_details, "Unable to initialize select_visit_details statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&update_pullman_km, "call update_pullman_km()", conn)) {
				print_stmt_error(update_pullman_km, "Unable to initialize update_pullman_km statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_map, "call select_map()", conn)) {
				print_stmt_error(select_map, "Unable to initialize select_map statement\n");
				return false;
			}
			
			break;
		case CLIENTE:
			// Consultazione tour 
			// Consultazione mete di un tour 
			// Consultazione visite tour 
			// Consultazione comfort presenti sui modelli 
			// consultazione servizi offerti dagli alberghi 
			// Consultazione documentazione fotografica 
			if(!setup_prepared_stmt(&select_visit_details, "call select_visit_details()", conn)) {
				print_stmt_error(select_visit_details, "Unable to initialize select_visit_details statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_tour_destination, "call select_tour_destination()", conn)) {
				print_stmt_error(select_tour_destination, "Unable to initialize select_tour_destination statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_model_comfort, "call select_model_comfort()", conn)) {
				print_stmt_error(select_model_comfort, "Unable to initialize select_model_comfort statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_hotel_service, "call select_hotel_service()", conn)) {
				print_stmt_error(select_hotel_service, "Unable to initialize select_hotel_service statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_picture, "call select_picture()", conn)) {
				print_stmt_error(select_picture, "Unable to initialize select_picture statement\n");
				return false;
			}
			break;
		case HOSTESS:
			//Registrazione cliente
			//Conferma prenotazione ed intestazione posti del viaggio
			//Consultazione prenotazioni
			//Aggiornamento posti disponibili per un viaggio
			//Inserire nuova prenotazione

			if(!setup_prepared_stmt(&insert_costumer, "call insert_costumer(?, ?, ?, ?, ?, ?, ?)", conn)) {		//Insert
				print_stmt_error(insert_costumer, "Unable to initialize insert costumer statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_reservation, "call insert reservation(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(insert_reservation, "Unable to initialize insert reservation statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_seat, "call insert_seat (?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(insert_seat, "Unable to initialize insert seat statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&validate_reservation, "call validate_reservation()", conn)) {
				print_stmt_error(validate_reservation, "Unable to initialize update reservation statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_costumer, "call select_costumer()", conn)) {
				print_stmt_error(select_costumer, "Unable to initialize select costumer statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_reservation, "call select_reservation()", conn)) {
				print_stmt_error(select_reservation, "Unable to initialize select reservation statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_seat, "call select_seat()", conn)) {
				print_stmt_error(select_seat, "Unable to initialize select seat statement\n");
				return false;
			}
			break;
			if(!setup_prepared_stmt(&update_trip_seat, "call update_trip_seat()", conn)) {
				print_stmt_error(update_trip_seat, "Unable to initialize update trip statement statement\n");
				return false;
			}
			break;
		case MECCANICO:
			//consultazione revisioni scadute
			//inserimento revisioni effettuate
			//consultazione magazzino ricambi
			//Inserire nuovi modelli 
			//Inserire nuovi ricambi
			//Modifica quantita ricambi
			//Inserire nuovi mezzi
			//Inserire nuovi tagliandi	
			if(!setup_prepared_stmt(&select_expired_review, "call select_expired_review(?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_expired_review, "Unable to initialize select_expired_review statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_sparepart_warehouse, "call select_sparepart_warehouse()", conn)) {
				print_stmt_error(select_sparepart_warehouse, "Unable to initialize select_sparepart_warehouse statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_review, "call insert_review(?, ?, ?, ?, ?, ?, ?)", conn)) {		//Insert
				print_stmt_error(insert_review, "Unable to initialize insert review statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_model, "call insert_model(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(insert_model, "Unable to initialize insert model statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_sparepart, "call insert_sparepart(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(insert_sparepart, "Unable to initialize insert sparepart statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_bus, "call insert_bus(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(insert_bus, "Unable to initialize insert bus statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_certify, "call insert_certify(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(insert_certify, "Unable to initialize insert certify statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&update_sparepart_number, "call update_sparepart_number(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(update_sparepart_number, "Unable to initialize update certify statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_review, "call select_review(?, ?, ?, ?, ?, ?, ?)", conn)) {	
				print_stmt_error(select_review, "Unable to initialize select review statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_model, "call select_model(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_model, "Unable to initialize select model statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_sparepart, "call select_sparepart(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_sparepart, "Unable to initialize select sparepart statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_bus, "call select_bus(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_bus, "Unable to initialize select bus statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_certify, "call select_certify(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_certify, "Unable to initialize select certify statement\n");
				return false;
			}
			break;
		default:
			fprintf(stderr, "[FATAL] Unexpected role to prepare statements.\n");
			exit(EXIT_FAILURE);
	}

	return true;
}

bool init_db(void) // OK ma ricontrollare in seguito
{
	unsigned int timeout = 300;
	bool reconnect = true;

	conn = mysql_init(NULL);
	if(conn == NULL) {
		finish_with_error(conn, "mysql_init() failed (probably out of memory)\n");
	}

	if(mysql_real_connect(conn, getenv("HOST"), getenv("LOGIN_USER"), getenv("LOGIN_PASS"), getenv("DB"),
			      atoi(getenv("PORT")), NULL,
			      CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS | CLIENT_COMPRESS | CLIENT_INTERACTIVE | CLIENT_REMEMBER_OPTIONS) == NULL) {
		finish_with_error(conn, "mysql_real_connect() failed\n");
	}

	if (mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout)) {
		print_error(conn, "[mysql_options] failed.");
	}
	if(mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect)) {
		print_error(conn, "[mysql_options] failed.");
	}
#ifndef NDEBUG
	mysql_debug("d:t:O,/tmp/client.trace");
	if(mysql_dump_debug_info(conn)) {
		print_error(conn, "[debug_info] failed.");
	}
#endif

	return initialize_prepared_stmts(LOGIN_ROLE);
}


void fini_db(void) // OK ma ricontrollare in seguito
{
	close_prepared_stmts();

	mysql_close(conn);
}


role_t attempt_login(struct credentials *cred) //OK
{
	MYSQL_BIND param[3]; // Used both for input and output
	int role = 0;

	// Prepare parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cred->username, strlen(cred->username));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cred->password, strlen(cred->password));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &role, sizeof(role));

	if(mysql_stmt_bind_param(login_procedure, param) != 0) { // Note _param
		print_stmt_error(login_procedure, "Could not bind parameters for login");
		role = FAILED_LOGIN;
		goto out;
	}

	// Run procedure
	if(mysql_stmt_execute(login_procedure) != 0) {
		print_stmt_error(login_procedure, "Could not execute login procedure");
		role = FAILED_LOGIN;
		goto out;
	}

	// Prepare output parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &role, sizeof(role));

	if(mysql_stmt_bind_result(login_procedure, param)) {
		print_stmt_error(login_procedure, "Could not retrieve output parameter");
		role = FAILED_LOGIN;
		goto out;
	}

	// Retrieve output parameter
	if(mysql_stmt_fetch(login_procedure)) {
		print_stmt_error(login_procedure, "Could not buffer results");
		role = FAILED_LOGIN;
		goto out;
	}

    out:
	// Consume the possibly-returned table for the output parameter
	while(mysql_stmt_next_result(login_procedure) != -1) {}

	mysql_stmt_free_result(login_procedure);
	mysql_stmt_reset(login_procedure);
	return role;
}


void db_switch_to_login(void) // OK ma ricontrollare in seguito
{
	close_prepared_stmts();
	if(mysql_change_user(conn, getenv("LOGIN_USER"), getenv("LOGIN_PASS"), getenv("DB"))) {
		fprintf(stderr, "mysql_change_user() failed: %s\n", mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	if(!initialize_prepared_stmts(LOGIN_ROLE)) {
		fprintf(stderr, "[FATAL] Cannot initialize prepared statements.\n");
		exit(EXIT_FAILURE);
	}
}


void db_switch_to_administrator(void) // OK ma ricontrollare in seguito
{
	close_prepared_stmts();
	if(mysql_change_user(conn, getenv("ADMINISTRATOR_USER"), getenv("ADMINISTRATOR_PASS"), getenv("DB"))) {
		fprintf(stderr, "mysql_change_user() failed: %s\n", mysql_error(conn));
		exit(EXIT_FAILURE);
	}
	if(!initialize_prepared_stmts(AMMINISTRATORE)) {
		fprintf(stderr, "[FATAL] Cannot initialize prepared statements.\n");
		exit(EXIT_FAILURE);
	}
}

										// Esecuzione insert statement


void do_insert_costumer(struct cliente *cliente)
{	MYSQL_BIND param[8]; 
	MYSQL_TIME datadocumentazione; 
	int recapitotelefonico; 
	int fax; 
	
	datetime_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, strlen(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, strlen(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, strlen(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, strlen(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATETIME, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_LONG, &recapitotelefonico, sizeof(recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_LONG, &fax, sizeof(fax));
	
	
	if(mysql_stmt_bind_param(insert_costumer, param) != 0) {
		print_stmt_error(insert_costumer, "Could not bind parameters for insert_costumer");
		return;
	}
	if(mysql_stmt_execute(insert_costumer) != 0) {
		print_stmt_error(insert_costumer, "Could not execute insert_costumer");
		return;
		}
	mysql_stmt_free_result(insert_costumer);
	mysql_stmt_reset(insert_costumer);
	
}

void do_insert_reservation(struct prenotazione *prenotazione)
{		
	MYSQL_BIND param[5]; 
	MYSQL_TIME datadiprenotazione; 
	MYSQL_TIME datadiconferma; 
	MYSQL_TIME datasaldo; 

	int numerodiprenotazione; 

	datetime_to_mysql_time(prenotazione->datadiprenotazione, &datadiprenotazione);
	datetime_to_mysql_time(prenotazione->datadiconferma, &datadiconferma);
	datetime_to_mysql_time(prenotazione->datasaldo, &datasaldo);
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiprenotazione, sizeof(numerodiprenotazione));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prenotazione->clienteprenotante, strlen(prenotazione->clienteprenotante));
	set_binding_param(&param[2], MYSQL_TYPE_DATETIME, &datadiprenotazione,sizeof(datadiprenotazione));
	set_binding_param(&param[3], MYSQL_TYPE_DATETIME, &datadiconferma, sizeof(datadiconferma));
	set_binding_param(&param[4], MYSQL_TYPE_DATETIME, &datasaldo, sizeof(datasaldo));
	
	
	if(mysql_stmt_bind_param(insert_reservation, param) != 0) {
		print_stmt_error(insert_reservation, "Could not bind parameters for insert_reservation");
		return;
	}
	if(mysql_stmt_execute(insert_reservation) != 0) {
		print_stmt_error(insert_reservation, "Could not execute insert_reservation");
		return;
		}
	mysql_stmt_free_result(insert_reservation);
	mysql_stmt_reset(insert_reservation);
	
}

void do_insert_seat(struct postoprenotato *postoprenotato)
{		
	MYSQL_BIND param[6]; 
	
	int numerodiposto; 
	int viaggioassociato; 
	int prenotazioneassociata; 
	int etapasseggero; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiposto, sizeof(numerodiposto));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &viaggioassociato, sizeof(viaggioassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &prenotazioneassociata,sizeof(prenotazioneassociata));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &etapasseggero, sizeof(etapasseggero));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, postoprenotato->nomepasseggero, strlen(postoprenotato->nomepasseggero));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, postoprenotato->cognomepasseggero, strlen(postoprenotato->cognomepasseggero));
	
	
	if(mysql_stmt_bind_param(insert_seat, param) != 0) {
		print_stmt_error(insert_seat, "Could not bind parameters for insert_seat");
		return;
	}
	if(mysql_stmt_execute(insert_seat) != 0) {
		print_stmt_error(insert_seat, "Could not execute insert_seat");
		return;
		}
	mysql_stmt_free_result(insert_seat);
	mysql_stmt_reset(insert_seat);
	
}

void do_insert_review(struct revisione *revisione)
{		
	MYSQL_BIND param[9]; 
	MYSQL_TIME datainizio;
	MYSQL_TIME datafine; 

	int idrevisione; 
	int addettoallarevisione; 
	int chilometraggio; 

	date_to_mysql_time(revisione->datainizio, &datainizio);
	date_to_mysql_time(revisione->datafine, &datafine); 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idrevisione, sizeof(idrevisione));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, revisione->mezzorevisionato, strlen(revisione->mezzorevisionato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &addettoallarevisione,sizeof(addettoallarevisione));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datainizio, sizeof(datainizio));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &chilometraggio, sizeof(chilometraggio));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, revisione->operazionieseguite, strlen(revisione->operazionieseguite));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, revisione->tipologiarevisione, strlen(revisione->tipologiarevisione));
	set_binding_param(&param[8], MYSQL_TYPE_VAR_STRING, revisione->motivazione, strlen(revisione->motivazione));
	
	
	if(mysql_stmt_bind_param(insert_review, param) != 0) {
		print_stmt_error(insert_review, "Could not bind parameters for insert_review");
		return;
	}
	if(mysql_stmt_execute(insert_review) != 0) {
		print_stmt_error(insert_review, "Could not execute insert_review");
		return;
		}
	mysql_stmt_free_result(insert_review);
	mysql_stmt_reset(insert_review);	
}

void do_insert_model(struct modello *modello)
{		
	MYSQL_BIND param[6]; 
	
	int idmodello; 
	int numerodiposti; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idmodello, sizeof(idmodello));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, modello->nomemodello, strlen(modello->nomemodello));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, modello->datitecnici, strlen(modello->datitecnici));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, modello->casacostruttrice, strlen(modello->casacostruttrice));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &numerodiposti, sizeof(numerodiposti));
	

	if(mysql_stmt_bind_param(insert_model, param) != 0) {
		print_stmt_error(insert_model, "Could not bind parameters for insert_model");
		return;
	}
	if(mysql_stmt_execute(insert_model) != 0) {
		print_stmt_error(insert_model, "Could not execute insert_model");
		return;
		}
	mysql_stmt_free_result(insert_model);
	mysql_stmt_reset(insert_model);
	

}

void do_insert_sparepart(struct ricambio *ricambio)
{		
	MYSQL_BIND param[6]; 
	
	float costounitario; 
	int quantitadiriordino; 
	int scortaminima; 
	int quantitainmagazzino; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, ricambio->codice, strlen(ricambio->codice));
	set_binding_param(&param[1], MYSQL_TYPE_FLOAT, &costounitario, sizeof(costounitario));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &quantitadiriordino, sizeof(quantitadiriordino));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, ricambio->descrizione, strlen(ricambio->descrizione));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &scortaminima, sizeof(scortaminima));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &quantitainmagazzino, sizeof(quantitainmagazzino));
	 
	
	if(mysql_stmt_bind_param(insert_sparepart, param) != 0) {
		print_stmt_error(insert_sparepart, "Could not bind parameters for bind_sparepart");
		return;
	}
	if(mysql_stmt_execute(insert_sparepart) != 0) {
		print_stmt_error(insert_sparepart, "Could not execute insert_sparepart");
		return;
		}
	mysql_stmt_free_result(insert_sparepart);
	mysql_stmt_reset(insert_sparepart);
	
}

void do_insert_bus(struct mezzo *mezzo)
{		
	MYSQL_BIND param[8]; 
	MYSQL_TIME dataultimarevisioneinmotorizzazione; 
	MYSQL_TIME dataimmatricolazione; 

	int modellomezzo; 
	int autonomia; 
	int valorecontakm;
	
	date_to_mysql_time(mezzo->dataultimarevisioneinmotorizzazione, &dataultimarevisioneinmotorizzazione); 
	date_to_mysql_time(mezzo->dataimmatricolazione, &dataimmatricolazione); 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzo->targa, strlen(mezzo->targa));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &modellomezzo, sizeof(modellomezzo));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, mezzo->ingombri, strlen(mezzo->ingombri));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, mezzo->modellomezzo, strlen(mezzo->modellomezzo));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &autonomia, sizeof(autonomia));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &valorecontakm, sizeof(valorecontakm));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &dataultimarevisioneinmotorizzazione, sizeof(dataultimarevisioneinmotorizzazione));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &dataimmatricolazione, sizeof(dataimmatricolazione));
	

	if(mysql_stmt_bind_param(insert_bus, param) != 0) {
		print_stmt_error(insert_bus, "Could not bind parameters for bind_bus");
		return;
	}
	if(mysql_stmt_execute(insert_bus) != 0) {
		print_stmt_error(insert_bus, "Could not execute insert_bus");
		return;
		}
	mysql_stmt_free_result(insert_bus);
	mysql_stmt_reset(insert_bus);
	
}

void do_insert_certify(struct tagliando *tagliando)
{		
	MYSQL_BIND param[3];

	int idtagliando;  
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, tagliando->idtagliando, sizeof(idtagliando));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tagliando->tipologiatagliando, strlen(tagliando->tipologiatagliando));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, tagliando->validitasuperate, strlen(tagliando->validitasuperate));
	
	
	if(mysql_stmt_bind_param(insert_certify, param) != 0) {
		print_stmt_error(insert_certify, "Could not bind parameters for insert_certify");
		return;
	}
	if(mysql_stmt_execute(insert_certify) != 0) {
		print_stmt_error(insert_certify, "Could not execute insert_certify");
		return;
		}
	mysql_stmt_free_result(insert_certify);
	mysql_stmt_reset(insert_certify);
	
}


					//*** Esecuzione update statement ***//
	
	
	
void do_validate_reservation(struct prenotazione *prenotazione)
{		
	MYSQL_BIND param[5]; 
	MYSQL_TIME datadiprenotazione; 
	MYSQL_TIME datadiconferma; 
	MYSQL_TIME datasaldo; 

	int numerodiprenotazione; 

	datetime_to_mysql_time(prenotazione->datadiprenotazione, &datadiprenotazione);
	datetime_to_mysql_time(prenotazione->datadiconferma, &datadiconferma);
	datetime_to_mysql_time(prenotazione->datasaldo, &datasaldo);
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiprenotazione, sizeof(numerodiprenotazione));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prenotazione->clienteprenotante, strlen(prenotazione->clienteprenotante));
	set_binding_param(&param[2], MYSQL_TYPE_DATETIME, &datadiprenotazione,sizeof(datadiprenotazione));
	set_binding_param(&param[3], MYSQL_TYPE_DATETIME, &datadiconferma, sizeof(datadiconferma));
	set_binding_param(&param[4], MYSQL_TYPE_DATETIME, &datasaldo, sizeof(datasaldo));
	
	
	if(mysql_stmt_bind_param(validate_reservation, param) != 0) {
		print_stmt_error(validate_reservation, "Could not bind parameters for bind_reservation");
		return;
	}
	if(mysql_stmt_execute(validate_reservation) != 0) {
		print_stmt_error(validate_reservation, "Could not execute validate_reservation");
		return;
		}
	mysql_stmt_free_result(validate_reservation);
	mysql_stmt_reset(validate_reservation);
	
}

								// Esecuzione statment update speciali




void do_update_trip_seat(struct viaggio *viaggio)
{	
	MYSQL_BIND param[11]; 
	MYSQL_TIME datadipartenzaviaggio; 
	MYSQL_TIME datadiritornoviaggio;
	MYSQL_TIME datadiannullamento; 

	int idviaggio; 
	int conducente; 
	int accompagnatrice; 
	float costodelviaggio; 
	int numerodikm; 
	int numerodipostidisponibili; 
	int dataannullamento; 
	
	datetime_to_mysql_time(viaggio->datadipartenzaviaggio, &datadipartenzaviaggio);
	datetime_to_mysql_time(viaggio->datadiritornoviaggio, &datadiritornoviaggio); 
	datatime_to_mysql_time(viaggio->datadiannullamento, &datadiannullamento); 

	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idviaggio, sizeof(idviaggio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, viaggio->tourassociato, strlen(viaggio->tourassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &conducente, sizeof(conducente);
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &accompagnatrice, sizeof(accompagnatrice));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, viaggio->mezzoimpiegato, strlen(viaggio->mezzoimpiegato));
	set_binding_param(&param[5], MYSQL_TYPE_DATETIME, &datadipartenzaviaggio, sizeof(datadipartenzaviaggio));
	set_binding_param(&param[6], MYSQL_TYPE_DATETIME, &datadiritornoviaggio, sizeof(datadiritornoviaggio));
	set_binding_param(&param[7], MYSQL_TYPE_FLOAT, &costodelviaggio, sizeof(costodelviaggio));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &numerodikm, sizeof(numerodikm));
	set_binding_param(&param[9], MYSQL_TYPE_LONG, &numerodipostidisponibili, sizeof(numerodipostidisponibili));
	set_binding_param(&param[10], MYSQL_TYPE_DATETIME, &dataannullamento, sizeof(dataannullamento));
	
	if(mysql_stmt_bind_param(update_trip_seat, param) != 0) {
		print_stmt_error(update_trip_seat, "Could not bind parameters for update_trip_seat");
		return;
	}
	if(mysql_stmt_execute(update_trip_seat) != 0) {
		print_stmt_error(update_trip_seat, "Could not execute update_trip_seat");
		return;
		}
	mysql_stmt_free_result(update_trip_seat);
	mysql_stmt_reset(update_trip_seat);
}
void do_update_pullman_km(struct mezzo *mezzo)
{ 		
	MYSQL_BIND param[8]; 
	MYSQL_TIME dataultimarevisioneinmotorizzazione; 
	MYSQL_TIME dataimmatricolazione; 

	int modellomezzo; 
	int autonomia; 
	int valorecontakm; 
	
	date_to_mysql_time(mezzo->dataultimarevisioneinmotorizzazione, &dataultimarevisioneinmotorizzazione); 
	date_to_mysql_time(mezzo->dataimmatricolazione, &dataimmatricolazione); 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzo->targa, strlen(mezzo->targa));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &modellomezzo, sizeof(modellomezzo));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, mezzo->ingombri, strlen(mezzo->ingombri));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, mezzo->modellomezzo, strlen(mezzo->modellomezzo));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &autonomia, sizeof(autonomia));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &valorecontakm, sizeof(valorecontakm));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &dataultimarevisioneinmotorizzazione, sizeof(dataultimarevisioneinmotorizzazione));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &dataimmatricolazione, sizeof(dataimmatricolazione));
	

	if(mysql_stmt_bind_param(update_pullman_km, param) != 0) {
		print_stmt_error(update_pullman_km, "Could not bind parameters for update_pullman_km");
		return;
	}
	if(mysql_stmt_execute(update_pullman_km) != 0) {
		print_stmt_error(update_pullman_km, "Could not execute update_pullman_km");
		return;
		}
	mysql_stmt_free_result(update_pullman_km);
	mysql_stmt_reset(update_pullman_km);
}


void do_update_sparepart_number(struct ricambio *ricambio)
{ 		
	MYSQL_BIND param[6]; 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, ricambi->codice, strlen(ricambi->codice));
	set_binding_param(&param[1], MYSQL_TYPE_FLOAT, &costounitario, sizeof(costounitario));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &quantitadiriordino, sizeof(quantitadiriordino));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, ricambi->descrzione, strlen(ricambi->descrizione));
	set_binding_param(&param[4], MYSQL_TYPE_LOGN, &scortaminima, sizeof(scortaminima));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &quantitainmagazzino, sizeof(quantitainmagazzino));
	

	if(mysql_stmt_bind_param(update_sparepart_number, param) != 0) {
		print_stmt_error(update_sparepart_number, "Could not bind parameters for update_sparepart_number");
		return;
	}
	if(mysql_stmt_execute(update_sparepart_number) != 0) {
		print_stmt_error(Update_sparepart_number, "Could not execute update_sparepart_number");
		return;
		}
	mysql_stmt_free_result(update_sparepart_number);
	mysql_stmt_reset(update_sparepart_number);
}
							// Esecuzione select statement


void do_select_tour( struct tour *tour)
{	MYSQL_BIND param[6]; 
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tour->denominazionetour, strlen(tour->denominazionetour));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tour->descrizionetour, strlen(tour->descrizionetour));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &minimopartecipanti, sizeof(minimopartecipanti));
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &assicurazionemedica, sizeof(assicurazionemedica));
	set_binding_param(&param[4], MYSQL_TYPE_FLOAT, &bagaglio, sizeof(bagaglio));
	set_binding_param(&param[5], MYSQL_TYPE_BOOL, &accompagnatrice, sizeof(accompagnatrice));
	

	if(mysql_stmt_bind_param(select_tour, param) != 0) {
		print_stmt_error(select_tour, "Could not bind parameters for select_tour");
		return;
	}
	if(mysql_stmt_execute(select_tour) != 0) {
		print_stmt_error(select_tour, "Could not execute select_tour");
		return;
		}

	mysql_stmt_free_result(select_tour);
	mysql_stmt_reset(select_tour);
	
}


void do_select_destination(struct meta *meta)
{ 	MYSQL_BIND param[10]; 
	MYSQL_TIME orariodiapertura; 
	
	time_to_mysql_time(meta->orariodiapertura, &orariodiapertura);
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idmeta, sizeof(idmeta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, meta->nomemeta, strlen(meta->nomemeta));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, meta->emailmeta, strlen(meta->emailmeta));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &telefonometa, sizeof(telefonometa));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &faxmeta, sizeof(faxmeta));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, meta->indirizzometa, strlen(meta->indirizzometa));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, meta->tipologiameta, strlen(meta->tipologiameta));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, meta->categoriaalbergo, strlen(meta->categoriaalbergo));
	set_binding_param(&param[8], MYSQL_TYPE_TIME, &orariodiapertura, sizeof(orariodiapertura));
	set_binding_param(&param[9], MYSQL_TYPE_VAR_STRING, meta->localitadiappartenenza, strlen(meta->localitadiappartenenza));
	
	
	if(mysql_stmt_bind_param(select_destination, param) != 0) {
		print_stmt_error(select_destination, "Could not bind parameters for select_destination");
		return;
	}
	// Run procedure
	if(mysql_stmt_execute(select_destination) != 0) {
		print_stmt_error(select_destination, "Could not execute select_destination");
		return;
		}
	mysql_stmt_free_result(select_destination);
	mysql_stmt_reset(select_destination);
	
}


void do_select_trip(struct viaggio *viaggio)
{		
	MYSQL_BIND param[11]; 
	MYSQL_TIME datadipartenzaviaggio; 
	MYSQL_TIME datadiritornoviaggio;
	MYSQL_TIME datadiannullamento; 
	
	datetime_to_mysql_time(viaggio->datadipartenzaviaggio, &datadipartenzaviaggio);
	datetime_to_mysql_time(viaggio->datadiritornoviaggio, &datadiritornoviaggio); 
	datatime_to_mysql_time(viaggio->datadiannullamento, &datadiannullamento); 

	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idviaggio, sizeof(idviaggio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, viaggio->tourassociato, strlen(viaggio->tourassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &conducente, sizeof(conducente);
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &accompagnatrice, sizeof(accompagnatrice));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, viaggio->mezzoimpiegato, strlen(viaggio->mezzoimpiegato));
	set_binding_param(&param[5], MYSQL_TYPE_DATETIME, &datadipartenzaviaggio, sizeof(datadipartenzaviaggio));
	set_binding_param(&param[6], MYSQL_TYPE_DATETIME, &datadiritornoviaggio, sizeof(datadiritornoviaggio));
	set_binding_param(&param[7], MYSQL_TYPE_FLOAT, &costodelviaggio, sizeof(costodelviaggio));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &numerodikm, sizeof(numerodikm));
	set_binding_param(&param[9], MYSQL_TYPE_LONG, &numerodipostidisponibili, sizeof(numerodipostidisponibili));
	set_binding_param(&param[10], MYSQL_TYPE_DATETIME, &dataannullamento, sizeof(dataannullamento));
	
	if(mysql_stmt_bind_param(select_trip, param) != 0) {
		print_stmt_error(select_trip, "Could not bind parameters for select_trip");
		return;
	}
	if(mysql_stmt_execute(select_trip) != 0) {
		print_stmt_error(select_trip, "Could not execute select_trip");
		return;
		}
	mysql_stmt_free_result(select_trip);
	mysql_stmt_reset(select_trip);
	
}

void do_select_visit(struct visita *visita)
{   
	MYSQL_BIND param[10]; 
	MYSQL_TIME datadiarrivo; 
	MYSQL_TIME datadipartenza; 
	MYSQL_TIME oradiarrivo; 
	MYSQL_TIME oradipartenza; 

	date_to_mysql_time (visita->datadiarrivo, &datadiarrivo); 
	date_to_mysql_time (visita->datadipartenza; &datadipartenza); 
	time_to_mysql_time (visita->oradiarrivo, &oradiarrivo); 
	time_to_mysql_time (visita->oradipartenza, &oradipartenza); 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idvisita, sizeof(idvisita));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &viaggiorelativo, sizeof(viaggiorelativo));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &metavisitata, sizeof(metavisitata);
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, visita->datadiarrivo, strlen(visita->datadiarrivo));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, visita->datadipartenza, strlen(visita-> datadipartenza));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, visita->oradiarrivo, strlen(visita->oradiarrivo));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, visita->oradipartenza, strlen(visita->oradipartenza));
	set_binding_param(&param[7], MYSQL_TYPE_BIT, visita->guida, strlen(visita->guida));
	set_binding_param(&param[8], MYSQL_TYPE_FLOAT, &supplemento, sizeof(supplemento));
	set_binding_param(&param[9], MYSQL_TYPE_VAR_STRING, visita->trattamentoalberghiero, strlen(visita->trattamentoalberghiero));
	
	

	if(mysql_stmt_bind_param(select_visit, param) != 0) {
		print_stmt_error(select_visit, "Could not bind parameters for select_visit");
		return;
	}
	if(mysql_stmt_execute(select_visit) != 0) {
		print_stmt_error(select_visit, "Could not execute select_visit");
		return;
		}
	mysql_stmt_free_result(select_visit);
	mysql_stmt_reset(select_visit);
	
}

void do_select_picture(struct documentazionefotografica *documentazionefotografica)
{	
	MYSQL_BIND param[2]; 
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idfoto sizeof(idfoto));
	set_binding_param(&param[1], MYSQL_TYPE_BLOB, documentazionefotografica->foto, strlen(documentazionefotografica->foto));
	
	
	if(mysql_stmt_bind_param(select_picture, param) != 0) {
		print_stmt_error(select_picture, "Could not bind parameters for select_picture");
		return;
	}
	if(mysql_stmt_execute(select_picture) != 0) {
		print_stmt_error(select_picture, "Could not execute select_picture");
		return;
		}
	mysql_stmt_free_result(select_picture);
	mysql_stmt_reset(select_picture);
	
}

void do_select_employee(struct dipendente *dipendente)
{		
	MYSQL_BIND param[5]; 
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &iddipendente, sizeof(iddipendente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, dipendente->nomedipendente, strlen(dipendente->nomedipendente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, dipendente->cognomedipendente, strlen(dipendente->cognomedipendente);
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, dipendente->tipologiadipendente, strlen(dipendente->tipologiadipendente));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &telefonoaziendale, sizeof(telefonoaziendale));
	
	
	if(mysql_stmt_bind_param(select_employee, param) != 0) {
		print_stmt_error(select_employee, "Could not bind parameters for select_employee");
		return;
	}
	if(mysql_stmt_execute(select_employee) != 0) {
		print_stmt_error(select_employee, "Could not execute select_employee");
		return;
		}
	mysql_stmt_free_result(select_employee);
	mysql_stmt_reset(select_employee);
	
}

void do_select_room(struct camera *camera)
{		
	MYSQL_BIND param[4]; 
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerocamera, sizeof(numerocamera));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &albergo, sizeof(albergo);
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, camera->tipologia, strlen(camera->tipologia);
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &costo , sizeof(costo));
	
	
	if(mysql_stmt_bind_param(select_room, param) != 0) {
		print_stmt_error(select_room, "Could not bind parameters for select_room");
		return;
	}
	if(mysql_stmt_execute(select_room) != 0) {
		print_stmt_error(select_room, "Could not execute select_room");
		return;
		}
	mysql_stmt_free_result(select_room);
	mysql_stmt_reset(select_room);
}

void do_select_location(struct localita *localita)
{		
	MYSQL_BIND param[3]; 
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, localita->nomelocalita, strlen(localita->nomelocalita));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, localita->regione, strlen(localita->regione));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, localita->stato, strlen(localita->stato);
	
	if(mysql_stmt_bind_param(select_location, param) != 0) {
		print_stmt_error(select_location, "Could not bind parameters for select_location");
		return;
	}
	if(mysql_stmt_execute(select_location) != 0) {
		print_stmt_error(select_location, "Could not execute select_location");
		return;
		}
	mysql_stmt_free_result(select_location);
	mysql_stmt_reset(select_location);
}

void do_select_map(struct mappa *mappa)
{		
	MYSQL_BIND param[5]; 
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idmappa, sizeof(idmappa));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, mappa->citta, strlen(mappa->citta));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, mappa->livellodidettaglio, strlen(mappa->livellodidettaglio));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, mappa->zona, strlen(mappa->zona));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, mappa->localitarappresentata, strlen(mappa->localitarappresentata));
	
	
	if(mysql_stmt_bind_param(select_map, param) != 0) {
		print_stmt_error(select_map, "Could not bind parameters for select_map");
		return;
	}
	if(mysql_stmt_execute(select_map) != 0) {
		print_stmt_error(select_map, "Could not execute select_location");
		return;
		}
	mysql_stmt_free_result(select_map);
	mysql_stmt_reset(select_map);
	
}

void do_select_costumer(struct cliente *cliente)
{	
	MYSQL_BIND param[8]; 
	MYSQL_TIME datadocumentazione; 
	
	datetime_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, strlen(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, strlen(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, strlen(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, strlen(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATETIME, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_LONG, &recapitotelefonico, sizeof(recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_LONG, &fax, sizeof(fax));
	
	if(mysql_stmt_bind_param(select_costumer, param) != 0) {
		print_stmt_error(select_costumer, "Could not bind parameters for select_costumer");
		return;
	}
	if(mysql_stmt_execute(select_costumer) != 0) {
		print_stmt_error(select_costumer, "Could not execute select_costumer");
		return;
		}
	mysql_stmt_free_result(select_costumer);
	mysql_stmt_reset(select_costumer);
	
}

void do_select_reservation(struct prenotazione *prenotazione)
{		
	MYSQL_BIND param[5]; 
	MYSQL_TIME datadiprenotazione; 
	MYSQL_TIME datadiconferma; 
	MYSQL_TIME datasaldo; 

	datetime_to_mysql_time(prenotazione->datadiprenotazione, &datadiprenotazione);
	datetime_to_mysql_time(prenotazione->datadiconferma, &datadiconferma);
	datetime_to_mysql_time(prenotazione->datasaldo, &datasaldo);
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiprenotazione, sizeof(numerodiprenotazione);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prenotazione->clienteprenotante, strlen(prenotazione->clienteprenotante));
	set_binding_param(&param[2], MYSQL_TYPE_DATETIME, &datadiprenotazione,sizeof(datadiprenotazione));
	set_binding_param(&param[3], MYSQL_TYPE_DATETIME, &datadiconferma, sizeof(datadiconferma));
	set_binding_param(&param[4], MYSQL_TYPE_DATETIME, &datasaldo, sizeof(datasaldo));
	
	
	if(mysql_stmt_bind_param(select_reservation, param) != 0) {
		print_stmt_error(select_reservation, "Could not bind parameters for select_reservation");
		return;
	if(mysql_stmt_execute(select_reservation) != 0) {
		print_stmt_error(select_reservation, "Could not execute select_reservation");
		return;
		}
	}
	mysql_stmt_free_result(select_reservation);
	mysql_stmt_reset(select_reservation);
	
}

void do_select_seat(struct postoprenotato *postoprenotato)
{		
	MYSQL_BIND param[6]; 
	
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiposto, sizeof(numerodiposto);
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &viaggioassociato, sizeof(viaggioassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &prenotazioneassociata,sizeof(prenotazioneassociata));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &etapasseggero, sizeof(etapasseggero));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, postoprenotato->nomepasseggero, strlen(postoprenotato->nomepasseggero));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, postoprenotato->cognomepasseggero, strlen(postoprenotato->cognomepasseggero));
	
	
	if(mysql_stmt_bind_param(select_seat, param) != 0) {
		print_stmt_error(select_seat, "Could not bind parameters for select_seat");
		return;
	}
	if(mysql_stmt_execute(select_seat) != 0) {
		print_stmt_error(select_seat, "Could not execute select_seat");
		return;
		}
	mysql_stmt_free_result(select_seat);
	mysql_stmt_reset(select_seat);
	
}

void do_select_review(struct revisione *revisione)
{		
	MYSQL_BIND param[9]; 
	MYSQL_TIME datainizio;
	MYSQL_TIME datafine; 

	date_to_mysql_time(revisione->datainizio, &datainizio);
	date_to_mysql_time(revisione->datafine, &datafine); 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idrevisione, sizeof(idrevisione);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, revisione->mezzorevisionato, strlen(revisione->mezzorevisionato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &addettoallarevisione,sizeof(addettoallarevisione));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datainizio, sizeof(datainizio));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &chilometraggio, sizeof(chilometraggio));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, revisione->operazionieseguite, strlen(revisione->operazionieseguite));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, revisione->tipologiarevisione, strlen(revisione->tipologiarevisione));
	set_binding_param(&param[8], MYSQL_TYPE_VAR_STRING, revisione->motivazione, strlen(revisione->motivazione));
	
	
	if(mysql_stmt_bind_param(select_review, param) != 0) {
		print_stmt_error(select_review, "Could not bind parameters for select_review");
		return;
	}
	if(mysql_stmt_execute(select_review) != 0) {
		print_stmt_error(select_review, "Could not execute select_review");
		return;
		}
	mysql_stmt_free_result(select_review);
	mysql_stmt_reset(select_review);
	
}

void do_select_model(struct modello *modello)
{		
	MYSQL_BIND param[6]; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idmodello, sizeof(idmodello);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, modello->nomemodello, strlen(modello->nomemodello));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, modello->tipologia, strlen(modello->tipologia));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, modello->datitecnici, strlen(modello->datitecnici));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, modello->casacostruttrice, strlen(modello->casacostruttrice));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &numerodiposti, sizeof(numerodiposti));
	

	if(mysql_stmt_bind_param(delete_model, param) != 0) {
		print_stmt_error(delete_model, "Could not bind parameters for select_model");
		return;
	}
	if(mysql_stmt_execute(select_model) != 0) {
		print_stmt_error(select_model, "Could not execute select_model");
		return;
		}
	mysql_stmt_free_result(delete_model);
	mysql_stmt_reset(delete_model);
}

void do_select_sparepart(struct ricambio *ricambio)
{		
	MYSQL_BIND param[6]; 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, ricambi->codice, strlen(ricambi->codice));
	set_binding_param(&param[1], MYSQL_TYPE_FLOAT, &costounitario, sizeof(costounitario));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &quantitadiriordino, sizeof(quantitadiriordino));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, ricambi->descrzione, strlen(ricambi->descrizione));
	set_binding_param(&param[4], MYSQL_TYPE_LOGN, &scortaminima, sizeof(scortaminima));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &quantitainmagazzino, sizeof(quantitainmagazzino));
	 
	
	if(mysql_stmt_bind_param(select_sparepart, param) != 0) {
		print_stmt_error(select_sparepart, "Could not bind parameters for select_sparepart");
		return;
	}
	if(mysql_stmt_execute(select_sparepart) != 0) {
		print_stmt_error(select_sparepart, "Could not execute select_sparepart");
		return;
		}
	mysql_stmt_free_result(select_sparepart);
	mysql_stmt_reset(select_sparepart);
	
}

void do_select_bus(struct mezzo *mezzo)
{		
	MYSQL_BIND param[8]; 
	MYSQL_TIME dataultimarevisioneinmotorizzazione; 
	MYSQL_TIME dataimmatricolazione; 
	
	date_to_mysql_time(mezzo->dataultimarevisioneinmotorizzazione, &dataultimarevisioneinmotorizzazione); 
	date_to_mysql_time(mezzo->dataimmatricolazione, &dataimmatricolazione); 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzo->targa, strlen(mezzo->targa));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &modellomezzo, sizeof(modellomezzo));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, mezzo->ingombri, strlen(mezzo->ingombri));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, mezzo->modellomezzo, strlen(mezzo->modellomezzo));
	set_binding_param(&param[4], MYSQL_TYPE_LOGN, &autonomia, sizeof(autonomia));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &valorecontakm, sizeof(valorecontkm));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &dataultimarevisioneinmotorizzazione, sizeof(dataultimarevisioneinmotorizzazione));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &dataimmatricolazione, sizeof(dataimmatricolazione));
	

	if(mysql_stmt_bind_param(select_bus, param) != 0) {
		print_stmt_error(select_bus, "Could not bind parameters for select_bus");
		return;
	}
	if(mysql_stmt_execute(select_bus) != 0) {
		print_stmt_error(select_bus, "Could not execute select_bus");
		return;
		}
	mysql_stmt_free_result(select_bus);
	mysql_stmt_reset(select_bus);
	
}

void do_select_certify(struct tagliando *tagliando)
{		
	MYSQL_BIND param[3]; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, tagliando->idtagliando, sizeof(idtagliando));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tagliando->tipologiatagliando, strlen(tagliando->tipologiatagliando));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, tagliando->validitasuperate, strlen(tagliando->validitasuperate));
	
	
	if(mysql_stmt_bind_param(select_certify, param) != 0) {
		print_stmt_error(select_certify, "Could not bind parameters for select_certify");
		return;
	}
	if(mysql_stmt_execute(select_certify) != 0) {
		print_stmt_error(select_certify, "Could not execute select_certify");
		return;
		}
	mysql_stmt_free_result(select_certify);
	mysql_stmt_reset(select_certify);
	
}

void do_select_service(struct servizio *servizio)
{		
	MYSQL_BIND param[3]; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, servizio->idservizio, sizeof(idservizio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, servizio->nomeservizio, strlen(servizio->nomeservizio));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, servizio->descrizioneservizio, strlen(servizio->descrizioneservizio));
	
	
	if(mysql_stmt_bind_param(select_service, param) != 0) {
		print_stmt_error(select_service, "Could not bind parameters for select_service");
		return;
	}
	if(mysql_stmt_execute(select_service) != 0) {
		print_stmt_error(select_service, "Could not execute select_service");
		return;
		}
	mysql_stmt_free_result(select_service);
	mysql_stmt_reset(select_service);
	
}

void do_select_comfort(struct comfort *comfort)
{		
	MYSQL_BIND param[3]; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, comfort->idcomfort, sizeof(idcomfort));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, comfort->nomecomfort, strlen(comfort->nomecomfort));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, comfort->descrizionecomfort, strlen(comfort->descrizionecomfort));
	
	
	if(mysql_stmt_bind_param(select_comfort, param) != 0) {
		print_stmt_error(select_comfort, "Could not bind parameters for select_comfort");
		return;
	}
	if(mysql_stmt_execute(select_comfort) != 0) {
		print_stmt_error(select_comfort, "Could not execute select_comfort");
		return;
		}
	mysql_stmt_free_result(select_comfort);
	mysql_stmt_reset(select_comfort);
	
}


								// Esecuzione statment select speciali


void do_select_assigned_trip(struct viaggio *viaggio)
{		
	MYSQL_BIND param[11]; 
	MYSQL_TIME datadipartenzaviaggio; 
	MYSQL_TIME datadiritornoviaggio;
	MYSQL_TIME datadiannullamento; 
	
	datetime_to_mysql_time(viaggio->datadipartenzaviaggio, &datadipartenzaviaggio);
	datetime_to_mysql_time(viaggio->datadiritornoviaggio, &datadiritornoviaggio); 
	datatime_to_mysql_time(viaggio->datadiannullamento, &datadiannullamento); 

	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idviaggio, sizeof(idviaggio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, viaggio->tourassociato, strlen(viaggio->tourassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &conducente, sizeof(conducente);
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &accompagnatrice, sizeof(accompagnatrice));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, viaggio->mezzoimpiegato, strlen(viaggio->mezzoimpiegato));
	set_binding_param(&param[5], MYSQL_TYPE_DATETIME, &datadipartenzaviaggio, sizeof(datadipartenzaviaggio));
	set_binding_param(&param[6], MYSQL_TYPE_DATETIME, &datadiritornoviaggio, sizeof(datadiritornoviaggio));
	set_binding_param(&param[7], MYSQL_TYPE_FLOAT, &costodelviaggio, sizeof(costodelviaggio));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &numerodikm, sizeof(numerodikm));
	set_binding_param(&param[9], MYSQL_TYPE_LONG, &numerodipostidisponibili, sizeof(numerodipostidisponibili));
	set_binding_param(&param[10], MYSQL_TYPE_DATETIME, &dataannullamento, sizeof(dataannullamento));

	if(mysql_stmt_bind_param(select_assigned_trip, param) != 0) {
		print_stmt_error(select_assigned_trip, "Could not bind parameters for select_assigned_trip");
		return;
	}
	if(mysql_stmt_execute(select_assigned_trip) != 0) {
		print_stmt_error(select_assigned_trip, "Could not execute select_assigned_trip");
		return;
		}
	mysql_stmt_free_result(select_assigned_trip);
	mysql_stmt_reset(select_assigned_trip);
	
}
 
 void do_select_visit_details(struct visita *visita, struct documentazionefotografica *documentazionefotografica)
{	
	MYSQL_BIND param[12]; 

	MYSQL_TIME datadiarrivo; 
	MYSQL_TIME datadipartenza; 
	MYSQL_TIME oradiarrivo; 
	MYSQL_TIME oradipartenza; 

	date_to_mysql_time (visita->datadiarrivo, &datadiarrivo); 
	date_to_mysql_time (visita->datadipartenza; &datadipartenza); 
	time_to_mysql_time (visita->oradiarrivo, &oradiarrivo); 
	time_to_mysql_time (visita->oradipartenza, &oradipartenza); 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idvisita, sizeof(idvisita));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &viaggiorelativo, sizeof(viaggiorelativo));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &metavisitata, sizeof(metavisitata);
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, visita->datadiarrivo, strlen(visita->datadiarrivo));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, visita->datadipartenza, strlen(visita-> datadipartenza));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, visita->oradiarrivo, strlen(visita->oradiarrivo));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, visita->oradipartenza, strlen(visita->oradipartenza));
	set_binding_param(&param[7], MYSQL_TYPE_BIT, visita->guida, strlen(visita->guida));
	set_binding_param(&param[8], MYSQL_TYPE_FLOAT, &supplemento, sizeof(supplemento));
	set_binding_param(&param[9], MYSQL_TYPE_VAR_STRING, visita->trattamentoalberghiero, strlen(visita->trattamentoalberghiero)); 
	set_binding_param(&param[10], MYSQL_TYPE_LONG, &idfoto sizeof(idfoto));
	set_binding_param(&param[11], MYSQL_TYPE_BLOB, documentazionefotografica->foto, strlen(documentazionefotografica->foto));
	

	if(mysql_stmt_bind_param(select_visit_details, param) != 0) {
		print_stmt_error(select_visit_details, "Could not bind parameters for select_visit_details");
		return;
	}
	if(mysql_stmt_execute(select_visit_details) != 0) {
		print_stmt_error(select_visit_details, "Could not execute select_visit_details");
		return;
		}
	mysql_stmt_free_result(select_visit_details);
	mysql_stmt_reset(select_visit_details);
	
}
 
void do_select_tour_destination(struct tour *tour, struct meta *meta, struct documentazionefotografica *documentazionefotografica)
{	
	MYSQL_BIND param[18]; 

	time_to_mysql_time(meta->orariodiapertura, &orariodiapertura);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tour->denominazionetour, strlen(tour->denominazionetour));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tour->descrizionetour, strlen(tour->descrizionetour));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &minimopartecipanti, sizeof(minimopartecipanti));
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &assicurazionemedica, sizeof(assicurazionemedica));
	set_binding_param(&param[4], MYSQL_TYPE_FLOAT, &bagaglio, sizeof(bagaglio));
	set_binding_param(&param[5], MYSQL_TYPE_BOOL, &accompagnatrice, sizeof(accompagnatrice));
	set_binding_param(&param[6], MYSQL_TYPE_LONG, &idfoto sizeof(idfoto));
	set_binding_param(&param[7], MYSQL_TYPE_BLOB, documentazionefotografica->foto, strlen(documentazionefotografica->foto));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &idmeta, sizeof(idmeta));
	set_binding_param(&param[9], MYSQL_TYPE_VAR_STRING, meta->nomemeta, strlen(meta->nomemeta));
	set_binding_param(&param[10], MYSQL_TYPE_VAR_STRING, meta->emailmeta, strlen(meta->emailmeta));
	set_binding_param(&param[11], MYSQL_TYPE_LONG, &telefonometa, sizeof(telefonometa));
	set_binding_param(&param[12], MYSQL_TYPE_LONG, &faxmeta, sizeof(faxmeta));
	set_binding_param(&param[13], MYSQL_TYPE_VAR_STRING, meta->indirizzometa, strlen(meta->indirizzometa));
	set_binding_param(&param[14], MYSQL_TYPE_VAR_STRING, meta->tipologiameta, strlen(meta->tipologiameta));
	set_binding_param(&param[15], MYSQL_TYPE_VAR_STRING, meta->categoriaalbergo, strlen(meta->categoriaalbergo));
	set_binding_param(&param[16], MYSQL_TYPE_TIME, &orariodiapertura, sizeof(orariodiapertura));
	set_binding_param(&param[17], MYSQL_TYPE_VAR_STRING, meta->localitadiappartenenza, strlen(meta->localitadiappartenenza));
	

	if(mysql_stmt_bind_param(select_tour_destination, param) != 0) {
		print_stmt_error(select_tour_destination, "Could not bind parameters for select_tour_destination");
		return;
		}
	if(mysql_stmt_execute(select_tour_destination) != 0) {
		print_stmt_error(select_tour_destination, "Could not execute select_tour_destination");
		return;
		}

	mysql_stmt_free_result(select_tour_destination);
	mysql_stmt_reset(select_tour_destination);
	
}


void do_select_model_comfort(struct modello *modello, struct comfort *comfort)
{		
	MYSQL_BIND param[9]; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idmodello, sizeof(idmodello);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, modello->nomemodello, strlen(modello->nomemodello));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, modello->tipologia, strlen(modello->tipologia));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, modello->datitecnici, strlen(modello->datitecnici));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, modello->casacostruttrice, strlen(modello->casacostruttrice));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &numerodiposti, sizeof(numerodiposti));
	set_binding_param(&param[6], MYSQL_TYPE_LONG, comfort->idcomfort, sizeof(idcomfort));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, comfort->nomecomfort, strlen(comfort->nomecomfort));
	set_binding_param(&param[8], MYSQL_TYPE_VAR_STRING, comfort->descrizionecomfort, strlen(comfort->descrizionecomfort));

	if(mysql_stmt_bind_param(select_model_comfort, param) != 0) {
		print_stmt_error(select_model_comfort, "Could not bind parameters for select_model_comfort");
		return;
	}
	if(mysql_stmt_execute(select_model_comfort) != 0) {
		print_stmt_error(select_model_comfort, "Could not execute select_model_comfort");
		return;
		}
	mysql_stmt_free_result(select_model_comfort);
	mysql_stmt_reset(select_model_comfort);
} 

void do_select_hotel_service(struct meta *meta, struct servizio *servizio)
{	MYSQL_BIND param[13]; 
	
	MYSQL_TIME orariodiapertura; 
	time_to_mysql_time(meta->orariodiapertura, &orariodiapertura);


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idmeta, sizeof(idmeta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, meta->nomemeta, strlen(meta->nomemeta));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, meta->emailmeta, strlen(meta->emailmeta));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &telefonometa, sizeof(telefonometa));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &faxmeta, sizeof(faxmeta));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, meta->indirizzometa, strlen(meta->indirizzometa));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, meta->tipologiameta, strlen(meta->tipologiameta));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, meta->categoriaalbergo, strlen(meta->categoriaalbergo));
	set_binding_param(&param[8], MYSQL_TYPE_TIME, &orariodiapertura, sizeof(orariodiapertura));
	set_binding_param(&param[9], MYSQL_TYPE_VAR_STRING, meta->localitadiappartenenza, strlen(meta->localitadiappartenenza));
	set_binding_param(&param[10], MYSQL_TYPE_LONG, servizio->idservizio, sizeof(idservizio));
	set_binding_param(&param[11], MYSQL_TYPE_VAR_STRING, servizio->nomeservizio, strlen(servizio->nomeservizio));
	set_binding_param(&param[12], MYSQL_TYPE_VAR_STRING, servizio->descrizioneservizio, strlen(servizio->descrizioneservizio));
	

	if(mysql_stmt_bind_param(select_hotel_service, param) != 0) {
		print_stmt_error(select_hotel_service, "Could not bind parameters for select_hotel_service");
		return;
	}
	if(mysql_stmt_execute(select_hotel_service) != 0) {
		print_stmt_error(select_hotel_service, "Could not execute select_hotel_service");
		return;
		}
	mysql_stmt_free_result(select_hotel_service);
	mysql_stmt_reset(select_hotel_service);
}

void do_select_expired_review(struct revisione *revisione)
{		
	MYSQL_BIND param[9]; 
	MYSQL_TIME datainizio;
	MYSQL_TIME datafine; 

	date_to_mysql_time(revisione->datainizio, &datainizio);
	date_to_mysql_time(revisione->datafine, &datafine); 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idrevisione, sizeof(idrevisione);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, revisione->mezzorevisionato, strlen(revisione->mezzorevisionato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &addettoallarevisione,sizeof(addettoallarevisione));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datainizio, sizeof(datainizio));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[5], MYSQL_TYPE_LONG, &chilometraggio, sizeof(chilometraggio));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, revisione->operazionieseguite, strlen(revisione->operazionieseguite));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, revisione->tipologiarevisione, strlen(revisione->tipologiarevisione));
	set_binding_param(&param[8], MYSQL_TYPE_VAR_STRING, revisione->motivazione, strlen(revisione->motivazione));
	

	if(mysql_stmt_bind_param(select_expired_review, param) != 0) {
		print_stmt_error(select_expired_review, "Could not bind parameters for select_expired_review");
		return;
	}
	if(mysql_stmt_execute(select_expired_review) != 0) {
		print_stmt_error(select_expired_review, "Could not execute select_expired_review");
		return;
		}
	mysql_stmt_free_result(select_expired_review);
	mysql_stmt_reset(select_expired_review);
}

void do_select_sparepart_warehouse(struct ricambio *ricambio)
{	bind_sparepart(ricambio);

	if(mysql_stmt_bind_param(select_sparepart_warehouse, param) != 0) {
		print_stmt_error(select_sparepart_warehouse, "Could not bind parameters for select_sparepart_warehouse");
		return;
	}
	if(mysql_stmt_execute(select_sparepart_warehouse) != 0) {
		print_stmt_error(select_sparepart_warehouse, "Could not execute select_sparepart_warehouse");
		return;
		}

	mysql_stmt_free_result(select_sparepart_warehouse);
	mysql_stmt_reset(select_sparepart_warehouse);
}


int main(int argv, char* argc){
    init_db();
    return 0;
}


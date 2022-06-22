#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <assert.h>
#include <err.h>

#include "trpdb.h"
#include "../utils/db.h"


static char *opt_host_name = "localhost"; /* host (default=localhost) */
static char *opt_user_name = "giordano"; /* username (default=login name)*/
static char *opt_password = "root1989"; /* password (default=none) */
static unsigned int opt_port_num =  3306; /* port number (use built-in) */
static char *opt_socket_name = NULL; /* socket name (use built-in) */
static char *opt_db_name = "tripdb"; /* database name (default=none) */
static unsigned int opt_flags = 0; /* connection flags (none) */

static MYSQL *conn;

static MYSQL_STMT *login_procedure;

static MYSQL_STMT *insert_costumer; //OK HOSTESS
static MYSQL_STMT *insert_reservation; // OK HOSTESS
static MYSQL_STMT *insert_seat; //OK HOSTESS
static MYSQL_STMT *insert_assoc; //OK HOSTESS

static MYSQL_STMT *select_trip; //ok HOSTESS, CLIENTE
static MYSQL_STMT *select_costumer; //Ok HOSTESS
static MYSQL_STMT *select_reservation; //ok HOSTESS

static MYSQL_STMT *select_tour; //Cliente
static MYSQL_STMT *select_destination;// Cliente
static MYSQL_STMT *select_picture; // Cliente
static MYSQL_STMT *select_room; // Cliente
static MYSQL_STMT *select_model; //Cliente
static MYSQL_STMT *select_comfort;// Cliente
static MYSQL_STMT *select_service; // Cliente 

static MYSQL_STMT *select_all_tour; // Cliente
static MYSQL_STMT *select_tour_trip; // Cliente

static MYSQL_STMT *update_trip_seat; //ok HOSTESS
static MYSQL_STMT *validate_reservation; //ok  HOSTESS
static MYSQL_STMT *update_data_doc; //Ok  HOSTESS

static void close_prepared_stmts(void)
{
	if(login_procedure) {
		mysql_stmt_close(login_procedure);
		login_procedure = NULL;
	}
	if(select_tour) {						// Procedura di select tour
		mysql_stmt_close(select_tour);
		select_tour = NULL;
	}	
	if(select_all_tour) {					// Procedura di select della denominazione di tutti i tour
		mysql_stmt_close(select_all_tour);
		select_all_tour = NULL;
	}	
	if(select_destination) {				// Procedura di select meta
		mysql_stmt_close(select_destination);
		select_destination = NULL;
	}	
	if(select_service) {					// Procedura di select servizio
		mysql_stmt_close(select_service);
		select_service = NULL;
	}	
	if(select_comfort) {					// Procedura di select comfort
		mysql_stmt_close(select_comfort);
		select_comfort = NULL;
	}	
	if(select_model) {						// Procedura di select model
		mysql_stmt_close(select_model);
		select_model = NULL;
	}	
	if(select_picture) {					// Procedura di select documentazione fotografica
		mysql_stmt_close(select_picture);
		select_picture = NULL;
	}
	if(select_room) {						// Procedura di select camera
		mysql_stmt_close(select_room);
		select_room = NULL;
	}	
	if(select_tour_trip) {				// Procedura di select viaggi realtivi ai tour
		mysql_stmt_close(select_tour_trip);
		select_tour_trip = NULL;
	}				
	if(select_trip) {				// Procedura di select viaggi
		mysql_stmt_close(select_trip);
		select_trip = NULL;
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
	if(update_trip_seat) {				// Procedura  update tagliando(MECCANICO) 
		mysql_stmt_close(update_trip_seat);
		update_trip_seat= NULL;
	}
	if(update_data_doc){				// Procedura update data documentazione
		mysql_stmt_close(update_data_doc); 
		update_data_doc= NULL; 
	}
	if(insert_assoc){
		mysql_stmt_close(insert_assoc);
		insert_assoc = NULL; 
	}
}

static bool initialize_prepared_stmts(role_t for_role)
{ 
	printf("For role %d\n\n", for_role); 

	switch(for_role) {

		case LOGIN_ROLE:
			if(!setup_prepared_stmt(&login_procedure, "call login(?, ?, ?)", conn)) {
				print_stmt_error(login_procedure, "Unable to initialize login statement\n");
				return false;
			}
			break;

		case HOSTESS:
			if(!setup_prepared_stmt(&insert_costumer, "call insert_costumer(?, ?, ?, ?, ?, ?, ?, ?)", conn)) {		//Insert
				print_stmt_error(insert_costumer, "Unable to initialize insert costumer statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_reservation, "call insert_reservation(?, ?)", conn)) {
				print_stmt_error(insert_reservation, "Unable to initialize insert reservation statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_seat, "call insert_seat (?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(insert_seat, "Unable to initialize insert seat statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&validate_reservation, "call validate_reservation(?, ?, ?)", conn)) {
				print_stmt_error(validate_reservation, "Unable to initialize validate reservation statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_costumer, "call select_costumer(?, ?, ?, ?, ?, ?, ?, ? )", conn)) {
				print_stmt_error(select_costumer, "Unable to initialize select costumer statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_reservation, "call select_reservation(?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_reservation, "Unable to initialize select reservation statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_trip, "call select_trip(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_trip, "Unable to initialize select trip statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&update_trip_seat, "call update_trip_seat(?, ?)", conn)) {
				print_stmt_error(update_trip_seat, "Unable to initialize update trip statement statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&update_data_doc, "call update_data_doc(?, ?)", conn)) {
				print_stmt_error(update_data_doc, "Unable to initialize update trip statement statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&insert_assoc, "call insert_assoc(?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(insert_assoc, "Unable to initialize update trip statement statement\n");
				return false;
			}
			break;

		case CLIENTE:
			if(!setup_prepared_stmt(&select_tour, "call select_tour(?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_tour, "Unable to initialize select_tour statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_all_tour, "call select_all_tour()", conn)) {
				print_stmt_error(select_all_tour, "Unable to initialize select_all_tour statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_tour_trip, "call select_tour_trip(?)", conn)) {
				print_stmt_error(select_tour_trip, "Unable to initialize select tour trip statement\n");
				return false;
			}
			/*
			if(!setup_prepared_stmt(&select_destination, "call select_destination()", conn)) {
				print_stmt_error(select_destination, "Unable to initialize select_destination statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_comfort, "call select_comfort()", conn)) {
				print_stmt_error(select_comfort, "Unable to initialize select_model_comfort statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_service, "call select_service()", conn)) {
				print_stmt_error(select_service, "Unable to initialize select_service statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_model, "call select_model()", conn)) {
				print_stmt_error(select_model, "Unable to initialize select_model statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_room, "call select_room()", conn)) {
				print_stmt_error(select_room, "Unable to initialize select_room statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_picture, "call select_picture()", conn)) {
				print_stmt_error(select_picture, "Unable to initialize select_picture statement\n");
				return false;
			}*/
			if(!setup_prepared_stmt(&select_trip, "call select_trip(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_trip, "Unable to initialize select_trip statement\n");
				return false;
			}
			break;

		default:
			fprintf(stderr, "[FATAL] Unexpected role to prepare statements.\n");
			exit(EXIT_FAILURE);
	}

	return true;

}

bool init_db(void) //testato
{
printf("Inizializzazione database..."); 
	unsigned int timeout = 300;
	bool reconnect = true;
	
	conn = mysql_init(NULL);
	
	if(conn == NULL) {
		finish_with_error(conn, "mysql_init() failed (probably out of memory)\n");
	}
	if(mysql_real_connect(conn, opt_host_name, opt_user_name,opt_password, opt_db_name, opt_port_num, opt_socket_name,opt_flags) == NULL) {
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
printf("completata \n"); 
	return initialize_prepared_stmts(LOGIN_ROLE);
}


void fini_db(void)
{
	close_prepared_stmts();

	mysql_close(conn);
}


role_t attempt_login(struct credentials *cred)
{
	MYSQL_BIND param[3]; // Used both for input and output
	int role = 0;

	// Prepare parameters
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cred->username, strlen(cred->username));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cred->password, strlen(cred->password));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &role, sizeof(role));

	if(mysql_stmt_bind_param(login_procedure, param) != 0) { // Note _param
		print_stmt_error(login_procedure, "Binding dei parametri non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}

	// Run procedure
	if(mysql_stmt_execute(login_procedure) != 0) {
		print_stmt_error(login_procedure, "Login non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}

	// Prepare output parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &role, sizeof(role));

	if(mysql_stmt_bind_result(login_procedure, param)) {
		print_stmt_error(login_procedure, "Bind_result non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}

	// Retrieve output parameter
	if(mysql_stmt_fetch(login_procedure)) {
		print_stmt_error(login_procedure, "Fetch non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}
	printf("ROLE %d \n", role);
    out:
	// Consume the possibly-returned table for the output parameter
	while(mysql_stmt_next_result(login_procedure) != -1) {}

	mysql_stmt_free_result(login_procedure);
	mysql_stmt_reset(login_procedure);
	 
	initialize_prepared_stmts(role); 
	printf("ROLE %d \n", role);
	return role;
}


void db_switch_to_login(void)
{
	close_prepared_stmts();
	if(mysql_change_user(conn, getenv("LOGIN_USER"), getenv("LOGIN_PASS"), getenv("DB"))) {
		fprintf(stderr,"mysql_change_user() failed: %s\n", mysql_error(conn));
		exit(EXIT_FAILURE);
	}

	if(!initialize_prepared_stmts(LOGIN_ROLE)) {
		fprintf(stderr,"[FATAL] Cannot initialize prepared statements.\n");
		exit(EXIT_FAILURE);
	}

}

/*
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
}*/


										// Esecuzione insert statement


void do_insert_costumer(struct cliente *cliente ) // funziona
{	
	MYSQL_BIND param[8]; 
	MYSQL_TIME datadocumentazione; 
	int recapitotelefonico;
	int fax; 
	
	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, sizeof(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, sizeof(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, sizeof(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, sizeof(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, sizeof(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, sizeof(cliente->recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, cliente->fax, sizeof(cliente->fax));
	
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

void do_insert_reservation(struct prenotazione *prenotazione)// funziona
{		
	MYSQL_BIND param[2]; 
	MYSQL_TIME datadiprenotazione; 

	date_to_mysql_time(prenotazione->datadiprenotazione, &datadiprenotazione);
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prenotazione->clienteprenotante, sizeof(prenotazione->clienteprenotante));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &datadiprenotazione,sizeof(datadiprenotazione));
	
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

void do_insert_seat(struct postoprenotato *postoprenotato) //Funziona
{		
	MYSQL_BIND param[6]; 
	
	int numerodiposto; 
	int viaggioassociato; 
	int prenotazioneassociata; 
	int etapasseggero; 

	numerodiposto = postoprenotato->numerodiposto; 
	viaggioassociato = postoprenotato->viaggioassociato; 
	prenotazioneassociata = postoprenotato->prenotazioneassociata; 
	etapasseggero = postoprenotato->etapasseggero; 

	printf("Numero di prenotazione tripdb %d \n\n", postoprenotato->prenotazioneassociata); 

	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiposto, sizeof(numerodiposto));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &viaggioassociato, sizeof(viaggioassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &prenotazioneassociata,sizeof(prenotazioneassociata));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &etapasseggero, sizeof(etapasseggero));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, postoprenotato->nomepasseggero, sizeof(postoprenotato->nomepasseggero));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, postoprenotato->cognomepasseggero, sizeof(postoprenotato->cognomepasseggero));
	
    bind_exe(insert_seat,param, "insert_seat"); 

	mysql_stmt_free_result(insert_seat);
	mysql_stmt_reset(insert_seat);
	
}

void do_insert_assoc(struct associata *associata) // Funziona
{		
	MYSQL_BIND param[5];
	MYSQL_TIME datafinesoggiorno;
	MYSQL_TIME datainiziosoggiorno; 

	int cameraprenotata; 
	int ospite; 
	int albergoinquestione; 

	date_to_mysql_time(associata->datainiziosoggiorno, &datainiziosoggiorno); 
	date_to_mysql_time(associata->datafinesoggiorno, &datafinesoggiorno); 
	
	cameraprenotata = associata->cameraprenotata; 
	albergoinquestione = associata->albergoinquestione;
	ospite = associata->ospite; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &cameraprenotata, sizeof(cameraprenotata));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &ospite, sizeof(ospite));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &albergoinquestione, sizeof(albergoinquestione));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datainiziosoggiorno, sizeof(datainiziosoggiorno)); 
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datafinesoggiorno, sizeof(datafinesoggiorno));
	
	bind_exe(insert_assoc, param, "insert_assoc"); 

	mysql_stmt_free_result(insert_assoc);
	mysql_stmt_reset(insert_assoc);
	
}

void do_validate_reservation(struct prenotazione *prenotazione) //Funziona
{		
	MYSQL_BIND param[3]; 

	MYSQL_TIME datadiconferma; 
	MYSQL_TIME datasaldo; 

	int numerodiprenotazione; 

	numerodiprenotazione = prenotazione->numerodiprenotazione; 
	
	date_to_mysql_time(prenotazione->datadiconferma, &datadiconferma);
	date_to_mysql_time(prenotazione->datasaldo, &datasaldo);
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiprenotazione, sizeof(numerodiprenotazione));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &datadiconferma, sizeof(datadiconferma));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datasaldo, sizeof(datasaldo));
	
	bind_exe(validate_reservation,param,"validate_reservation"); 

	mysql_stmt_free_result(validate_reservation);
	mysql_stmt_reset(validate_reservation);
	
}

								// Esecuzione statment update speciali




void do_update_trip_seat(struct viaggio *viaggio) //Funziona
{	
	MYSQL_BIND param[2]; 

	int idviaggio; 
	int postidisponibili; 

	idviaggio = viaggio->idviaggio; 
	postidisponibili = viaggio->postidisponibili; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idviaggio, sizeof(idviaggio));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &postidisponibili, sizeof(postidisponibili));

	bind_exe(update_trip_seat, param, "update_trip_seat"); 

	mysql_stmt_free_result(update_trip_seat);
	mysql_stmt_reset(update_trip_seat);
}



void do_select_trip(struct viaggio *viaggio) //Funziona
{		
	MYSQL_BIND param[11]; 
	MYSQL_TIME datadipartenzaviaggio; 
	MYSQL_TIME datadiritornoviaggio;
	MYSQL_TIME datadiannullamento;
	MYSQL_TIME ddp; 
	MYSQL_TIME ddr; 
	MYSQL_TIME dda; 

	int idviaggio; 
	int conducente; 				
	int accompagnatrice; 
	float costodelviaggio;  
	int numerodikm; 
	int postidisponibili; 

	int idv; 
	char tou[VARCHAR_LEN]; 
	int con; 				
	int acc; 					
	char mez[VARCHAR_LEN]; 			
	float cos;
	int nkm;
	int pds;

	date_to_mysql_time(viaggio->datadipartenzaviaggio, &datadipartenzaviaggio);
	date_to_mysql_time(viaggio->datadiritornoviaggio, &datadiritornoviaggio); 
	date_to_mysql_time(viaggio->datadiannullamento, &datadiannullamento);

	init_mysql_timestamp(&ddp); 
	init_mysql_timestamp(&ddr); 
	init_mysql_timestamp(&dda);
    
	idviaggio = viaggio->idviaggio; 
	/*conducente = viaggio->conducente; 				
	accompagnatrice = viaggio->accompagnatrice ; 
	costodelviaggio = viaggio->costodelviaggio;  
	numerodikm = viaggio->numerodikm; 
	postidisponibili = viaggio -> postidisponibili; */

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idviaggio, sizeof(idviaggio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, viaggio->tourassociato, sizeof(viaggio->tourassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &conducente, sizeof(conducente));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &accompagnatrice, sizeof(accompagnatrice));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, viaggio->mezzoimpiegato, sizeof(viaggio->mezzoimpiegato));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadipartenzaviaggio, sizeof(datadipartenzaviaggio));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &datadiritornoviaggio, sizeof(datadiritornoviaggio));
	set_binding_param(&param[7], MYSQL_TYPE_FLOAT, &costodelviaggio, sizeof(costodelviaggio));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &numerodikm, sizeof(numerodikm));
	set_binding_param(&param[9], MYSQL_TYPE_LONG, &postidisponibili, sizeof(postidisponibili));
	set_binding_param(&param[10], MYSQL_TYPE_DATE, &datadiannullamento, sizeof(datadiannullamento));
	
	if(bind_exe(select_trip,param,"select_trip") == -1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tou, sizeof(tou));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &con, sizeof(con));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &acc, sizeof(acc));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, mez, sizeof(mez));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &ddp, DATE_LEN);
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &ddr, DATE_LEN);
	set_binding_param(&param[6], MYSQL_TYPE_FLOAT, &cos, sizeof(cos));
	set_binding_param(&param[7], MYSQL_TYPE_LONG, &nkm, sizeof(nkm));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &pds, sizeof(pds));
	set_binding_param(&param[9], MYSQL_TYPE_DATE, &dda, DATE_LEN);

	if(take_result(select_trip,param, "select_trip") == -1)
		goto stop; 

		strcpy(viaggio->tourassociato, tou);
		strcpy(viaggio->mezzoimpiegato, mez);

		viaggio->conducente = con; 
		viaggio->accompagnatrice = acc; 
		viaggio->numerodikm = nkm; 
		viaggio->postidisponibili = pds; 
		viaggio->costodelviaggio = cos; 

		mysql_date_to_string(&ddp, viaggio->datadipartenzaviaggio);
		mysql_date_to_string(&ddr, viaggio->datadiritornoviaggio); 
        mysql_date_to_string(&dda, viaggio->datadiannullamento);

	stop: 

	mysql_stmt_free_result(select_trip);
	mysql_stmt_reset(select_trip);	
}
	
void do_select_costumer(struct cliente *cliente) // funziona
{	 
	MYSQL_BIND param[8];  
	MYSQL_TIME datadocumentazione;
    MYSQL_TIME ddc; 

    char eml[VARCHAR_LEN];
	char nmc[VARCHAR_LEN];
	char cgm[VARCHAR_LEN];
	char ind[VARCHAR_LEN];
	char cdf[VARCHAR_LEN];
	char tel[VARCHAR_LEN];
	char fax[VARCHAR_LEN];


	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);
    init_mysql_timestamp(&ddc);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, sizeof(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, sizeof(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, sizeof(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, sizeof(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, sizeof(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, sizeof(cliente->recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, cliente->fax, sizeof(cliente->fax));

	if(bind_exe(select_costumer,param,"select_costumer") == -1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, eml, VARCHAR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, nmc, VARCHAR_LEN);
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cgm, VARCHAR_LEN);
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, ind, VARCHAR_LEN);
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cdf, VARCHAR_LEN);
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &ddc, DATE_LEN);
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, tel, VARCHAR_LEN);
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, fax, VARCHAR_LEN);

	if(take_result(select_costumer,param,"select_costumer")== -1)
		goto stop;

	strcpy(cliente->emailcliente, eml);
	strcpy(cliente->nomecliente, nmc);
	strcpy(cliente->cognomecliente, cgm);
    strcpy(cliente->codicefiscale, cdf);
    strcpy(cliente->indirizzocliente, ind);
    strcpy(cliente->recapitotelefonico,tel); 
    strcpy(cliente->fax, fax); 
    mysql_date_to_string(&ddc, cliente->datadocumentazione);
		
    stop:
	mysql_stmt_free_result(select_costumer);
	mysql_stmt_reset(select_costumer); 
	
}


void do_select_reservation(struct prenotazione *prenotazione)//Funziona
{		
	MYSQL_BIND param[5]; 
	MYSQL_TIME datadiprenotazione; 
	MYSQL_TIME datadiconferma; 
	MYSQL_TIME datasaldo; 
	MYSQL_TIME ddp; 
	MYSQL_TIME ddc; 
	MYSQL_TIME dds; 
	
	int numerodiprenotazione;
	char cli[VARCHAR_LEN];

	numerodiprenotazione = prenotazione->numerodiprenotazione; 

	date_to_mysql_time(prenotazione->datadiprenotazione, &datadiprenotazione); 
	date_to_mysql_time(prenotazione->datadiconferma, &datadiconferma);
	date_to_mysql_time(prenotazione->datasaldo, &datasaldo);

	init_mysql_date(&ddp); 
	init_mysql_date(&ddc); 
	init_mysql_date(&dds); 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiprenotazione, sizeof(numerodiprenotazione));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, prenotazione->clienteprenotante, sizeof(prenotazione->clienteprenotante));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datadiprenotazione,sizeof(datadiprenotazione));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datadiconferma, sizeof(datadiconferma));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datasaldo, sizeof(datasaldo));

	if(bind_exe(select_reservation,param,"select_reservation") == -1)
		goto stop;  

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cli, VARCHAR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &ddp, sizeof(ddp));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &ddc, sizeof(ddc));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &dds, sizeof(dds));

	if(take_result(select_reservation,param,"select_reservation")== -1) 
		goto stop; 

	
	strcpy(prenotazione->clienteprenotante, cli);
	mysql_date_to_string(&ddp, prenotazione->datadiprenotazione); 
	mysql_date_to_string(&ddc, prenotazione->datadiconferma); 
	mysql_date_to_string(&dds, prenotazione->datasaldo); 

	stop: 
	mysql_stmt_free_result(select_reservation);
	mysql_stmt_reset(select_reservation);
}
	


void do_update_data_doc(struct cliente *cliente) //funziona
{	
	MYSQL_BIND param[2]; 
	MYSQL_TIME datadocumentazione; 

	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, sizeof(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_DATETIME, &datadocumentazione, sizeof(datadocumentazione));
	
	if(mysql_stmt_bind_param(update_data_doc, param) != 0) {
		print_stmt_error(update_data_doc, "Could not bind parameters for update_data_doc");
		return;
	}
	if(mysql_stmt_execute(update_data_doc) != 0) {
		print_stmt_error(update_data_doc, "Could not execute update_data_doc");
		return;
		}
	mysql_stmt_free_result(update_data_doc);
	mysql_stmt_reset(update_data_doc);
	
}
void do_select_tour( struct tour *tour)
{	
	MYSQL_BIND param[7];

	int minimopartecipanti; 
	float assicurazionemedica; 
	float bagaglio; 
	float garanziaannullamento; 
	signed char accompagnatrice; 
	
	char den [VARCHAR_LEN]; 
	char des [DES_LEN]; 
	int mip; 
	float amd; 
	float bgl; 
	float gan; 
	signed char acc; 
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tour->denominazionetour, sizeof(tour->denominazionetour));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tour->descrizionetour, sizeof(tour->descrizionetour));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &minimopartecipanti, sizeof(minimopartecipanti));
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &assicurazionemedica, sizeof(assicurazionemedica));
	set_binding_param(&param[4], MYSQL_TYPE_FLOAT, &bagaglio, sizeof(bagaglio));
	set_binding_param(&param[5], MYSQL_TYPE_FLOAT, &garanziaannullamento, sizeof(garanziaannullamento));
	set_binding_param(&param[6], MYSQL_TYPE_TINY, &accompagnatrice, sizeof(accompagnatrice));
	
	if(bind_exe(select_tour,param, "select_tour")== -1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, den, sizeof(den));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, des, sizeof(des));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &mip, sizeof(mip));
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &amd, sizeof(amd));
	set_binding_param(&param[4], MYSQL_TYPE_FLOAT, &bgl, sizeof(bgl));
	set_binding_param(&param[5], MYSQL_TYPE_FLOAT, &gan, sizeof(gan));
	set_binding_param(&param[6], MYSQL_TYPE_TINY, &acc, sizeof(acc));
	
	if(take_result(select_tour, param, "select_tour")==-1)
		goto stop; 
	
	printf("Des %s", des); 
	

	strcpy(tour->denominazionetour, den);  
	strcpy(tour->descrizionetour, des); 
	tour->minimopartecipanti = mip; 
	tour->assicurazionemedica = amd; 
	tour->bagaglio = bgl; 
	tour->garanziaannullamento = gan; 
	tour->accompagnatrice = acc; 

	stop: 
	mysql_stmt_free_result(select_tour);
	mysql_stmt_reset(select_tour);
	
}

struct viaggi_info *get_viaggi_info(struct viaggio *viaggio)
{		
	MYSQL_BIND param[4]; 
	MYSQL_TIME datadipartenzaviaggio; 
	MYSQL_TIME datadiritornoviaggio;
	MYSQL_TIME ddp; 
	MYSQL_TIME ddr; 

	struct viaggi_info *viaggi_info = NULL; 
	int status; 
	size_t rows, count; 
	count = 0; 

	float cos;
	int pds;
	
	init_mysql_timestamp(&ddp); 
	init_mysql_timestamp(&ddr); 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, viaggio->tourassociato, sizeof(viaggio->tourassociato));
	bind_exe(select_tour_trip, param, "select_toir_trip"); 
	rows = take_rows(select_tour_trip, "select_tour_trip"); 
	if (rows == -1)
		goto stop; 

	viaggi_info =malloc((sizeof(struct viaggio)+sizeof(viaggi_info))*rows);
	memset(viaggi_info, 0, sizeof(*viaggi_info) + sizeof(struct viaggio)*rows);

	if(viaggi_info == NULL){
		printf("Impossibile eseguire la malloc su viaggi info"); 
		goto stop; 
	}

	set_binding_param(&param[0], MYSQL_TYPE_DATE, &ddp, sizeof(ddp));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &ddr, sizeof(ddr));
	set_binding_param(&param[2], MYSQL_TYPE_FLOAT, &cos, sizeof(cos));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &pds, sizeof(pds));

	if(mysql_stmt_bind_result(select_tour_trip, param)) {
		print_stmt_error(select_tour_trip, "\n\n Impossibile eseguire il bind risult\n\n");
		goto stop; 
	}

	viaggi_info->num_viaggi = rows;

	while (true) {
		status = mysql_stmt_fetch(select_tour_trip);
		if (status == MYSQL_NO_DATA)
			break; 
		if (status == 1 ){
			print_stmt_error(select_tour_trip, "\nImpossibile eseguire fetch");
			}
			
			mysql_date_to_string(&ddp,viaggi_info->viaggi_info[count].datadipartenzaviaggio);
			mysql_date_to_string(&ddr,viaggi_info->viaggi_info[count].datadiritornoviaggio);

			viaggi_info->viaggi_info[count].costodelviaggio = cos; 
			viaggi_info->viaggi_info[count].postidisponibili = pds; 

			printf("Data di partenza:	%s 	\n",viaggi_info->viaggi_info[count].datadipartenzaviaggio);
			printf("Data di riotrno:	%s 	\n",viaggi_info->viaggi_info[count].datadiritornoviaggio);
			printf("Prezzo:	%f 	\n",viaggi_info->viaggi_info[count].costodelviaggio);
			printf("Posti disponibili: %d 	\n",viaggi_info->viaggi_info[count].postidisponibili);	 
			printf("\n\n"); 
			count++; 
	}
	stop: 

	mysql_stmt_free_result(select_tour_trip);
	mysql_stmt_reset(select_tour_trip);	
}

struct tour_info *get_tour_info (struct viaggio *viaggio)
{	
	MYSQL_BIND param[7];
	struct tour_info *tour_info = NULL; 
	char *buff = "get_tour_info";
	char dnm[VARCHAR_LEN]; 
	char dsc[DES_LEN]; 
	int mnp; 
	float mdc; 
	float bgl;
	float gnl; 
	signed char acm;
	size_t rows, count;   
	int status;
	count = 0; 

	rows  = take_rows(select_all_tour, "select_all_tour");
		
	tour_info =malloc((sizeof(struct tour)+sizeof(tour_info))*rows);
	memset(tour_info, 0, sizeof(*tour_info) + sizeof(struct tour)*rows);

	if(tour_info == NULL){
		printf("Impossibile eseguire la malloc su tour info"); 
		goto stop; 
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, dnm, sizeof(dnm));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, dsc, sizeof(dsc)); 
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &mnp, sizeof(mnp)); 
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &mdc, sizeof(mdc)); 
	set_binding_param(&param[4], MYSQL_TYPE_FLOAT, &bgl, sizeof(bgl)); 
	set_binding_param(&param[5], MYSQL_TYPE_FLOAT, &gnl, sizeof(gnl)); 
	set_binding_param(&param[6], MYSQL_TYPE_TINY, &acm, sizeof(acm)); 

	if(mysql_stmt_bind_result(select_all_tour, param)) {
		print_stmt_error(select_all_tour, "\n\n Impossibile eseguire il bind risult\n\n");
		goto stop; 
	}
	tour_info->num_tour = rows; 
	while (true) {
		status = mysql_stmt_fetch(select_all_tour);
		if (status == MYSQL_NO_DATA)
			break; 
		if (status == 1 ){
			print_stmt_error(select_all_tour, "\nImpossibile eseguire fetch");
			}
			strcpy(tour_info->tour_info[count].denominazionetour, dnm);
			strcpy(tour_info->tour_info[count].descrizionetour, dsc);
			strcpy(viaggio->tourassociato,dnm); 

			tour_info->tour_info[count].minimopartecipanti = mnp; 
			tour_info->tour_info[count].assicurazionemedica = mdc; 
			tour_info->tour_info[count].bagaglio = bgl; 
			tour_info->tour_info[count].garanziaannullamento = gnl; 
			tour_info->tour_info[count].accompagnatrice = acm;

			printf("* %s *\n",tour_info->tour_info[count].denominazionetour);
			printf("Descrizione tour:	%s 	\n",tour_info->tour_info[count].descrizionetour);
			printf("Minimo partecipanti:	 %d 	\n",tour_info->tour_info[count].minimopartecipanti);
			printf("Diritti iscrizione: \n");
			printf("Assicurazione medica:	 %f euro\n",tour_info->tour_info[count].assicurazionemedica);	
			printf("Bagaglio:		 %f euro\n",tour_info->tour_info[count].bagaglio);
			printf("Garanzia di annullamento:%f euro\n",tour_info->tour_info[count].garanziaannullamento);
			printf("\n-Accompagnatrice prevista:%d 	\n",tour_info->tour_info[count].accompagnatrice); 
			printf("\n\n");
			get_viaggi_info(viaggio);  
			count++; 
	}
	stop: 
	mysql_stmt_free_result(select_all_tour);
	mysql_stmt_reset(select_all_tour);
	
}
	
void do_select_destination(struct meta *meta)
{ 	
	MYSQL_BIND param[10]; 
	MYSQL_TIME orariodiapertura; 

	int idmeta; 
	int telefonometa; 
	int faxmeta; 
	
	time_to_mysql_time(meta->orariodiapertura, &orariodiapertura);
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idmeta, sizeof(idmeta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, meta->nomemeta, sizeof(meta->nomemeta));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, meta->emailmeta, sizeof(meta->emailmeta));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &telefonometa, sizeof(telefonometa));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &faxmeta, sizeof(faxmeta));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, meta->indirizzo, sizeof(meta->indirizzo));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, meta->tipologiameta, sizeof(meta->tipologiameta));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, meta->categoriaalbergo, sizeof(meta->categoriaalbergo));
	set_binding_param(&param[8], MYSQL_TYPE_TIME, &orariodiapertura, sizeof(orariodiapertura));
	set_binding_param(&param[9], MYSQL_TYPE_VAR_STRING, meta->localitadiappartenenza, sizeof(meta->localitadiappartenenza));
	
	
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
void do_select_service(struct servizio *servizio)
{		
	MYSQL_BIND param[3]; 

	int idservizio; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, servizio->idservizio, sizeof(idservizio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, servizio->nomeservizio, sizeof(servizio->nomeservizio));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, servizio->descrizioneservizio, sizeof(servizio->descrizioneservizio));
	
	
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

	int idcomfort; 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, comfort->idcomfort, sizeof(idcomfort));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, comfort->nomecomfort, sizeof(comfort->nomecomfort));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, comfort->descrizionecomfort, sizeof(comfort->descrizionecomfort));
	
	
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

void do_select_model(struct modello *modello)
{		
	MYSQL_BIND param[6]; 
	
	int idmodello;
	int numerodiposti;  

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idmodello, sizeof(idmodello));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, modello->nomemodello, sizeof(modello->nomemodello));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, modello->datitecnici, sizeof(modello->datitecnici));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, modello->casacostruttrice, sizeof(modello->casacostruttrice));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &numerodiposti, sizeof(numerodiposti));
	

	if(mysql_stmt_bind_param(select_model, param) != 0) {
		print_stmt_error(select_model, "Could not bind parameters for select_model");
		return;
	}
	if(mysql_stmt_execute(select_model) != 0) {
		print_stmt_error(select_model, "Could not execute select_model");
		return;
		}
	mysql_stmt_free_result(select_model);
	mysql_stmt_reset(select_model);
}

void do_select_picture(struct documentazionefotografica *documentazionefotografica)
{	
	MYSQL_BIND param[2]; 

	int idfoto; 


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idfoto, sizeof(idfoto));
	set_binding_param(&param[1], MYSQL_TYPE_BLOB, documentazionefotografica->foto, sizeof(documentazionefotografica->foto));
	
	
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

void do_select_room(struct camera *camera)
{		
	MYSQL_BIND param[4]; 

	int numerocamera; 
	int albergoinquestione;
	int costo;  

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerocamera, sizeof(numerocamera));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &albergoinquestione, sizeof(albergoinquestione));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, camera->tipologia, sizeof(camera->tipologia));
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
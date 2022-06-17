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

static MYSQL_STMT *select_trip; //ok HOSTESS
static MYSQL_STMT *select_costumer; //Ok HOSTESS
static MYSQL_STMT *select_reservation; //ok HOSTESS

static MYSQL_STMT *update_trip_seat; //ok HOSTESS
static MYSQL_STMT *validate_reservation; //ok  HOSTESS
static MYSQL_STMT *update_data_doc; //Ok  HOSTESS

static void close_prepared_stmts(void)
{
	if(login_procedure) {
		mysql_stmt_close(login_procedure);
		login_procedure = NULL;
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
			if(!setup_prepared_stmt(&select_reservation, "call select_reservation(?)", conn)) {
				print_stmt_error(select_reservation, "Unable to initialize select reservation statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_trip, "call select_trip(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
				print_stmt_error(select_trip, "Unable to initialize select reservation statement\n");
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
			if(!setup_prepared_stmt(&insert_assoc, "call insert_assoc(?, ?, ?)", conn)) {
				print_stmt_error(insert_assoc, "Unable to initialize update trip statement statement\n");
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
	 
	initialize_prepared_stmts(role); 
	
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

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, strlen(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, strlen(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, strlen(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, strlen(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, strlen(cliente->recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, cliente->fax, strlen(cliente->fax));
	
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
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prenotazione->clienteprenotante, strlen(prenotazione->clienteprenotante));
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
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiposto, sizeof(numerodiposto));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &viaggioassociato, sizeof(viaggioassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &prenotazioneassociata,sizeof(prenotazioneassociata));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &etapasseggero, sizeof(etapasseggero));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, postoprenotato->nomepasseggero, strlen(postoprenotato->nomepasseggero));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, postoprenotato->cognomepasseggero, strlen(postoprenotato->cognomepasseggero));
	
    bind_exe(insert_seat,param, "insert_seat"); 

	mysql_stmt_free_result(insert_seat);
	mysql_stmt_reset(insert_seat);
	
}

void do_insert_assoc(struct associata *associata) 
{		
	MYSQL_BIND param[3];

	int cameraprenotata; 
	int ospite; 
	int albergoinquestione; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &cameraprenotata, sizeof(cameraprenotata));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &ospite, sizeof(ospite));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &albergoinquestione, sizeof(albergoinquestione));
	
	
	if(mysql_stmt_bind_param(insert_assoc, param) != 0) {
		print_stmt_error(insert_assoc, "Could not bind parameters for insert_assoc");
		return;
	}
	if(mysql_stmt_execute(insert_assoc) != 0) {
		print_stmt_error(insert_assoc, "Could not execute insert_assoc");
		return;
		}
	mysql_stmt_free_result(insert_assoc);
	mysql_stmt_reset(insert_assoc);
	
}



					//*** Esecuzione update statement ***//
	
	
	
void do_validate_reservation(struct prenotazione *prenotazione)
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
	conducente = viaggio->conducente; 				
	accompagnatrice = viaggio->accompagnatrice ; 
	costodelviaggio = viaggio->costodelviaggio;  
	numerodikm = viaggio->numerodikm; 
	postidisponibili = viaggio -> postidisponibili; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idviaggio, sizeof(idviaggio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, viaggio->tourassociato, strlen(viaggio->tourassociato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &conducente, sizeof(conducente));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &accompagnatrice, sizeof(accompagnatrice));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, viaggio->mezzoimpiegato, strlen(viaggio->mezzoimpiegato));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadipartenzaviaggio, sizeof(datadipartenzaviaggio));
	set_binding_param(&param[6], MYSQL_TYPE_DATE, &datadiritornoviaggio, sizeof(datadiritornoviaggio));
	set_binding_param(&param[7], MYSQL_TYPE_FLOAT, &costodelviaggio, sizeof(costodelviaggio));
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &numerodikm, sizeof(numerodikm));
	set_binding_param(&param[9], MYSQL_TYPE_LONG, &postidisponibili, sizeof(postidisponibili));
	set_binding_param(&param[10], MYSQL_TYPE_DATE, &datadiannullamento, sizeof(datadiannullamento));
	
	if(bind_exe(select_trip,param,"select_trip") == -1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tou, VARCHAR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &con, NUM_LEN);
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &acc, VARCHAR_LEN);
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, mez, VARCHAR_LEN);
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &ddp, DATE_LEN);
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &ddr, DATE_LEN);
	set_binding_param(&param[6], MYSQL_TYPE_FLOAT, &cos, NUM_LEN);
	set_binding_param(&param[7], MYSQL_TYPE_LONG, &nkm, NUM_LEN);
	set_binding_param(&param[8], MYSQL_TYPE_LONG, &pds, NUM_LEN);
	set_binding_param(&param[9], MYSQL_TYPE_DATE, &dda, DATE_LEN);

	if(take_result(select_trip,param, "select_trip") == -1)
		goto stop; 

		strcpy(viaggio->tourassociato, tou);
		strcpy(viaggio->mezzoimpiegato, mez);
		viaggio->conducente = con; 
		viaggio->accompagnatrice = acc; 
		viaggio->numerodikm = nkm; 
		viaggio->postidisponibili = pds; 

		mysql_timestamp_to_string(&ddp, viaggio->datadipartenzaviaggio);
		mysql_timestamp_to_string(&ddr, viaggio->datadiritornoviaggio); 
        mysql_timestamp_to_string(&dda, viaggio->datadiannullamento);

	stop: 

	mysql_stmt_free_result(select_trip);
	mysql_stmt_reset(select_trip);	
}
	
void do_select_costumer(struct cliente *cliente) // funziona ma rivedere il campo recapito telefonico
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

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, strlen(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, strlen(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, strlen(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, strlen(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, strlen(cliente->recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, cliente->fax, strlen(cliente->fax));

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
    mysql_timestamp_to_string(&ddc, cliente->datadocumentazione);
		
    stop:
	mysql_stmt_free_result(select_costumer);
	mysql_stmt_reset(select_costumer); 
	
}


void do_select_reservation(struct prenotazione *prenotazione)
{		
	MYSQL_BIND param[5]; 
	MYSQL_TIME datadiprenotazione; 
	MYSQL_TIME datadiconferma; 
	MYSQL_TIME datasaldo; 
	MYSQL_TIME ddp; 
	MYSQL_TIME ddc; 
	MYSQL_TIME dds; 
	
	int numerodiprenotazione;
	int ndp; 
	char cli[VARCHAR_LEN];

	numerodiprenotazione = prenotazione->numerodiprenotazione; 

	date_to_mysql_time(prenotazione->datadiprenotazione, &datadiprenotazione); 
	date_to_mysql_time(prenotazione->datadiconferma, &datadiconferma);
	date_to_mysql_time(prenotazione->datasaldo, &datasaldo);

	init_mysql_timestamp(&ddp); 
	init_mysql_timestamp(&ddc); 
	init_mysql_timestamp(&dds); 
	
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &numerodiprenotazione, sizeof(numerodiprenotazione));
	
	if(bind_exe(select_reservation,param,"select_reservation") == -1)
		goto stop;  

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &ndp, NUM_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, &cli, VARCHAR_LEN);
	set_binding_param(&param[2], MYSQL_TYPE_DATETIME, &ddp, DATE_LEN);
	set_binding_param(&param[3], MYSQL_TYPE_DATETIME, &ddc, DATE_LEN);
	set_binding_param(&param[4], MYSQL_TYPE_DATETIME, &dds, DATE_LEN);

	if(take_result(select_reservation,param,"select_reservation")== -1) 
		goto stop; 

	strcpy(prenotazione->clienteprenotante, cli); 
	prenotazione->numerodiprenotazione = ndp; 
	mysql_timestamp_to_string(&ddp, prenotazione->datadiprenotazione); 
	mysql_timestamp_to_string(&ddc, prenotazione->datadiconferma); 
	mysql_timestamp_to_string(&dds, prenotazione->datasaldo); 

	stop: 
	mysql_stmt_free_result(select_reservation);
	mysql_stmt_reset(select_reservation);
}
	


void do_update_data_doc(struct cliente *cliente) //funziona
{	MYSQL_BIND param[2]; 
	MYSQL_TIME datadocumentazione; 

	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
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
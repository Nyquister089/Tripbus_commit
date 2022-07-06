#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <assert.h>
#include <err.h>

#include "trpdb.h"
#include "../utils/db.h"

static char *opt_host_name = "localhost"; /* host (default=localhost) */
static char *opt_user_name = "giordano";  /* username (default=login name)*/
static char *opt_password = "root1989";	  /* password (default=none) */
static unsigned int opt_port_num = 3306;  /* port number (use built-in) */
static char *opt_socket_name = NULL;	  /* socket name (use built-in) */
static char *opt_db_name = "tripdb";	  /* database name (default=none) */
static unsigned int opt_flags = 0;		  /* connection flags (none) */

static MYSQL *conn;

static MYSQL_STMT *login_procedure;

static MYSQL_STMT *insert_costumer;	   // OK HOSTESS
static MYSQL_STMT *insert_reservation; // OK HOSTESS
static MYSQL_STMT *insert_seat;		   // OK HOSTESS
static MYSQL_STMT *insert_assoc;	   // OK HOSTESS
static MYSQL_STMT *insert_review;	   // Meccanico
static MYSQL_STMT *insert_sostitution; // Meccanico

static MYSQL_STMT *select_trip;		   // ok HOSTESS
static MYSQL_STMT *select_costumer;	   // Ok HOSTESS
static MYSQL_STMT *select_reservation; // ok HOSTESS
static MYSQL_STMT *select_review;	   // ok Meccanico, Manager
static MYSQL_STMT *select_sparepart;   // ok Meccanico, ok Manager
static MYSQL_STMT *select_assoc;   		// ok Manager
static MYSQL_STMT *select_skills; 		// ok Manager
static MYSQL_STMT *select_employee;		// ok Manager 
static MYSQL_STMT *select_fmo;			// ok Manager
static MYSQL_STMT *select_fme;			// ok Manager
static MYSQL_STMT *select_ofr;			// ok Manager
static MYSQL_STMT *select_tome; 		// non funziona Manager
static MYSQL_STMT *select_user; 		// ok Manager
static MYSQL_STMT *select_seat; 		// ok Manager
static MYSQL_STMT *select_model; 		// ok Manager
static MYSQL_STMT *select_bus;		   // ok Manager

static MYSQL_STMT *select_tour;		   //
static MYSQL_STMT *select_destination; //
static MYSQL_STMT *select_picture;	   //
static MYSQL_STMT *select_room;		   //
static MYSQL_STMT *select_comfort;	   //			
static MYSQL_STMT *select_service;	   //


static MYSQL_STMT *select_all_tour;		  	// ok Cliente
static MYSQL_STMT *select_dest_tour;	  	// ok Cliente
static MYSQL_STMT *select_hotel_service;  	// ok Cliente
static MYSQL_STMT *select_model_comfort;  	// ok Cliente
static MYSQL_STMT *select_expired_review; 	// ok Meccanico
static MYSQL_STMT *select_max_idreview;   	// ok Meccanico
static MYSQL_STMT *select_assigned_trip; 	// ok AUTISTA 
static MYSQL_STMT *select_dest_time;		// ok AUTISTA
static MYSQL_STMT *select_dvr_map; 			// ok AUTISTA

static MYSQL_STMT *update_trip_seat;		 // ok HOSTESS
static MYSQL_STMT *validate_reservation;	 // ok HOSTESS
static MYSQL_STMT *update_data_doc;			 // Ok HOSTESS
static MYSQL_STMT *update_spareparts_number; // ok Meccanico
static MYSQL_STMT *update_km;				// Autista


static void close_prepared_stmts(void)
{
	if (login_procedure)
	{
		mysql_stmt_close(login_procedure);
		login_procedure = NULL;
	}
	if (select_assoc)
	{
		mysql_stmt_close(select_assoc);
		select_assoc = NULL;
	}
	if (select_tour)
	{ // Procedura di select tour
		mysql_stmt_close(select_tour);
		select_tour = NULL;
	}
	if (select_hotel_service)
	{ // Procedura di select dei servizi relativi ad un albergo
		mysql_stmt_close(select_hotel_service);
		select_hotel_service = NULL;
	}
	if (select_all_tour)
	{ // Procedura di select di tutti i tour
		mysql_stmt_close(select_all_tour);
		select_all_tour = NULL;
	}
	if (select_destination)
	{ // Procedura di select meta
		mysql_stmt_close(select_destination);
		select_destination = NULL;
	}
	if (select_service)
	{ // Procedura di select servizio
		mysql_stmt_close(select_service);
		select_service = NULL;
	}
	if (select_comfort)
	{ // Procedura di select comfort
		mysql_stmt_close(select_comfort);
		select_comfort = NULL;
	}
	if (select_model)
	{ // Procedura di select model
		mysql_stmt_close(select_model);
		select_model = NULL;
	}
	if (select_bus)
	{ // Procedura di select model
		mysql_stmt_close(select_bus);
		select_bus = NULL;
	}
	if (select_picture)
	{ // Procedura di select documentazione fotografica
		mysql_stmt_close(select_picture);
		select_picture = NULL;
	}
	if (select_review)
	{ // Procedura di select revisione
		mysql_stmt_close(select_review);
		select_review = NULL;
	}
	if (select_sparepart)
	{ // Procedura di select ricambio
		mysql_stmt_close(select_sparepart);
		select_sparepart = NULL;
	}
	if (select_room)
	{ // Procedura di select camera
		mysql_stmt_close(select_room);
		select_room = NULL;
	}
	if (select_model_comfort)
	{ // Procedura di select di un  modello e di foto e comfort ad esso associate
		mysql_stmt_close(select_model_comfort);
		select_model_comfort = NULL;
	}
	if (select_expired_review)
	{ // Procedura di select delle mete relative ad un viaggio
		mysql_stmt_close(select_expired_review);
		select_expired_review = NULL;
	}
	if (select_dest_tour)
	{ // Procedura di select delle targhe dei mezzi aventi revsioni scadute
		mysql_stmt_close(select_dest_tour);
		select_dest_tour = NULL;
	}
	if (select_max_idreview)
	{ // Procedura di select viaggi
		mysql_stmt_close(select_max_idreview);
		select_max_idreview = NULL;
	}
	if(select_dest_time) {			// Procedura di visualizzazione dati temporali mete visitate da viaggio (AUTISTA)
		mysql_stmt_close(select_dest_time);
		select_dest_time = NULL;
	}
	if(select_assigned_trip) {			// Procedura di visualizzazione viaggi assegnati (AUTISTA)
		mysql_stmt_close(select_assigned_trip);
		select_assigned_trip = NULL;
	}
	if (select_dvr_map)			// Procedura di visualizzazione mappe relative ad una località (AUTISTA)
	{ 
		mysql_stmt_close(select_dvr_map);
		select_dvr_map = NULL;
	}
	if (select_bus)
	{ 									// Procedura di select mezzo
		mysql_stmt_close(select_bus);
		select_bus = NULL;
	}
	if (select_employee)
	{
		mysql_stmt_close(select_employee);
		select_employee = NULL;
	}
	if (select_model)
	{
		mysql_stmt_close(select_model);
		select_model = NULL;
	}
	if (select_seat)
	{
		mysql_stmt_close(select_seat);
		select_seat = NULL;
	}
	if (select_user)
	{
		mysql_stmt_close(select_user);
		select_user = NULL;
	}
	if (select_tome)
	{
		mysql_stmt_close(select_tome);
		select_tome = NULL;
	}
	if (select_ofr)
	{
		mysql_stmt_close(select_ofr);
		select_ofr = NULL;
	}
	if (select_fme)
	{
		mysql_stmt_close(select_fme);
		select_fme = NULL;
	}
	if (select_fmo)
	{
		mysql_stmt_close(select_fmo);
		select_fmo = NULL;
	}
	if (select_skills)
	{
		mysql_stmt_close(select_skills);
		select_skills = NULL;
	}
	if (select_trip)
	{ // Procedura di select viaggi
		mysql_stmt_close(select_trip);
		select_trip = NULL;
	}
	if (insert_costumer)
	{ // Procedura di insert cliente (HOSTESS)
		mysql_stmt_close(insert_costumer);
		insert_costumer = NULL;
	}
	if (insert_reservation)
	{ // Procedura di insert prenotazione (HOSTESS)
		mysql_stmt_close(insert_reservation);
		insert_reservation = NULL;
	}
	if (insert_review)
	{ // Procedura di insert revisioni(MECCANICO)
		mysql_stmt_close(insert_review);
		insert_review = NULL;
	}
	if (update_spareparts_number)
	{ // Procedura di modifica del numero di ricambi a seguito di una sostituzione (MECCANICO)
		mysql_stmt_close(update_spareparts_number);
		update_spareparts_number = NULL;
	}
	if (insert_sostitution)
	{ // Procedura di insert sostituzione (MECCANICO)
		mysql_stmt_close(insert_sostitution);
		insert_sostitution = NULL;
	}
	if (insert_seat)
	{ // Procedura di insert posto prenotato (HOSTESS)
		mysql_stmt_close(insert_seat);
		insert_seat = NULL;
	}
	if (select_costumer)
	{ // Procedura select cliente (HOSTESS)
		mysql_stmt_close(select_costumer);
		select_costumer = NULL;
	}
	if (validate_reservation)
	{ // Procedura update  prenotazione (HOSTESS)
		mysql_stmt_close(validate_reservation);
		validate_reservation = NULL;
	}
	if (select_reservation)
	{ // Procedura select  prenotazione (HOSTESS)
		mysql_stmt_close(select_reservation);
		select_reservation = NULL;
	}
	if (update_trip_seat)
	{ // Procedura  update tagliando(MECCANICO)
		mysql_stmt_close(update_trip_seat);
		update_trip_seat = NULL;
	}
	if (update_data_doc)
	{ // Procedura update data documentazione
		mysql_stmt_close(update_data_doc);
		update_data_doc = NULL;
	}
	if(update_km)
	{ 										// Procedura update valore conta km 
		mysql_stmt_close(update_km);
		update_km = NULL;
	}
	if (insert_assoc)
	{
		mysql_stmt_close(insert_assoc);
		insert_assoc = NULL;
	}
}

static bool initialize_prepared_stmts(role_t for_role)
{
	printf("For role %d\n\n", for_role);

	switch (for_role)
	{

	case LOGIN_ROLE:
		if (!setup_prepared_stmt(&login_procedure, "call login(?, ?, ?)", conn))
		{
			print_stmt_error(login_procedure, "Unable to initialize login statement\n");
			return false;
		}
		break;

	case AUTISTA:
			if(!setup_prepared_stmt(&select_assigned_trip, "call select_assigned_trip(?)", conn)) {
				print_stmt_error(select_assigned_trip, "Unable to initialize select_assigned_trip statement\n");
				return false;
			}
			if(!setup_prepared_stmt(&select_dest_time, "call select_dest_time(?)", conn)) {
				print_stmt_error(select_dest_time, "Unable to initialize select_dest_time statement\n");
				return false;
			}
			if (!setup_prepared_stmt(&select_dvr_map, "call select_dvr_map(?)", conn))
			{
			print_stmt_error(select_dvr_map, "Unable to select_dvr_map statement\n");
			return false;
			}
			if (!setup_prepared_stmt(&select_bus, "call select_bus(?)", conn))
			{
			print_stmt_error(select_bus, "Unable to initialize select_bus statement\n");
			return false;
			}
			if (!setup_prepared_stmt(& update_km, "call  update_km(?,?)", conn))
			{
			print_stmt_error( update_km, "Unable to initialize update_km statement\n");
			return false;
			}
		break; 

	case HOSTESS:
		if (!setup_prepared_stmt(&insert_costumer, "call insert_costumer(?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ // Insert
			print_stmt_error(insert_costumer, "Unable to initialize insert costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_reservation, "call insert_reservation(?, ?)", conn))
		{
			print_stmt_error(insert_reservation, "Unable to initialize insert reservation statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_seat, "call insert_seat (?, ?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(insert_seat, "Unable to initialize insert seat statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&validate_reservation, "call validate_reservation(?, ?, ?)", conn))
		{
			print_stmt_error(validate_reservation, "Unable to initialize validate reservation statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_costumer, "call select_costumer(?, ?, ?, ?, ?, ?, ?, ? )", conn))
		{
			print_stmt_error(select_costumer, "Unable to initialize select costumer statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_reservation, "call select_reservation(?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(select_reservation, "Unable to initialize select reservation statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_trip, "call select_trip(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(select_trip, "Unable to initialize select trip statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&update_trip_seat, "call update_trip_seat(?, ?)", conn))
		{
			print_stmt_error(update_trip_seat, "Unable to initialize update trip statement statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&update_data_doc, "call update_data_doc(?, ?)", conn))
		{
			print_stmt_error(update_data_doc, "Unable to initialize update trip statement statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_assoc, "call insert_assoc(?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(insert_assoc, "Unable to initialize update trip statement statement\n");
			return false;
		}
		break;

	case CLIENTE:
		if (!setup_prepared_stmt(&select_tour, "call select_tour(?, ?, ?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(select_tour, "Unable to initialize select_tour statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_hotel_service, "call select_hotel_service(?)", conn))
		{
			print_stmt_error(select_hotel_service, "Unable to initialize select_hotel_service statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_all_tour, "call select_all_tour()", conn))
		{
			print_stmt_error(select_all_tour, "Unable to initialize select_all_tour statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_model_comfort, "call select_model_comfort(?)", conn))
		{
			print_stmt_error(select_model_comfort, "Unable to initialize select dest tour statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_dest_tour, "call select_dest_tour(?)", conn))
		{
			print_stmt_error(select_dest_tour, "Unable to initialize select dest tour statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_trip, "call select_trip(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{
			print_stmt_error(select_trip, "Unable to initialize select_trip statement\n");
			return false;
		}
		break;
	case MECCANICO:
		if (!setup_prepared_stmt(&update_spareparts_number, "call  update_spareparts_number(?,?)", conn))
		{ // Insert
			print_stmt_error(update_spareparts_number, "Unable to initialize insert review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_review, "call insert_review(?, ?, ?, ?, ?, ?, ?, ?)", conn))
		{ // Insert
			print_stmt_error(insert_review, "Unable to initialize insert review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&insert_sostitution, "call insert_sostitution(?,?,?)", conn))
		{
			print_stmt_error(insert_sostitution, "Unable to initialize insert_sostitution statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_sparepart, "call select_sparepart(?)", conn))
		{
			print_stmt_error(select_sparepart, "Unable to initialize select_sparepart statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_review, "call select_review(?)", conn))
		{
			print_stmt_error(select_review, "Unable to initialize select_review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_max_idreview, "call select_max_idreview()", conn))
		{
			print_stmt_error(select_max_idreview, "Unable to initialize select_max_idreview statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_expired_review, "call select_expired_review()", conn))
		{
			print_stmt_error(select_expired_review, "Unable to initialize select_expired_review statement\n");
			return false;
		} 
		break;
		case MANAGER:
		if (!setup_prepared_stmt(&select_sparepart, "call select_sparepart(?)", conn))
		{
			print_stmt_error(select_sparepart, "Unable to initialize select_sparepart statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_review, "call select_review(?)", conn))
		{
			print_stmt_error(select_review, "Unable to initialize select_review statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_assoc, "call  select_assoc(?,?,?)", conn))
		{ 
			print_stmt_error(select_assoc, "Unable to initialize select_assoc statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_employee, "call  select_employee(?)", conn))
		{ 
			print_stmt_error(select_employee, "Unable to initialize select_employee statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_bus, "call  select_bus(?)", conn))
		{ 
			print_stmt_error(select_bus, "Unable to initialize select_bus statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_model, "call  select_model(?)", conn))
		{ 
			print_stmt_error(select_model, "Unable to initialize select_model statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_seat, "call  select_seat(?, ?)", conn))
		{ 
			print_stmt_error(select_seat, "Unable to initialize select_seat statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_user, "call  select_user(?)", conn))
		{ 
			print_stmt_error(select_user, "Unable to initialize select_user statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_tome, "call  select_tome(?,?)", conn))
		{ 
			print_stmt_error(select_tome, "Unable to initialize select_tome statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_ofr, "call  select_ofr(?,?)", conn))
		{ 
			print_stmt_error(select_ofr, "Unable to initialize select_ofr statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_fme, "call  select_fme(?,?)", conn))
		{ 
			print_stmt_error(select_fme, "Unable to initialize select_fme statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_fmo, "call  select_fmo(?,?)", conn))
		{ 
			print_stmt_error(select_fmo, "Unable to initialize select_fmo statement\n");
			return false;
		}
		if (!setup_prepared_stmt(&select_skills, "call  select_skills(?,?)", conn))
		{ 
			print_stmt_error(select_skills, "Unable to initialize select_skills statement\n");
			return false;
		}
		break;

	default:
		fprintf(stderr, "[FATAL] Unexpected role to prepare statements.\n");
		exit(EXIT_FAILURE);
	}

	return true;
}

bool init_db(void) // testato
{
	printf("Inizializzazione database...");
	unsigned int timeout = 300;
	bool reconnect = true;

	conn = mysql_init(NULL);

	if (conn == NULL)
	{
		finish_with_error(conn, "mysql_init() failed (probably out of memory)\n");
	}
	if (mysql_real_connect(conn, opt_host_name, opt_user_name, opt_password, opt_db_name, opt_port_num, opt_socket_name, opt_flags) == NULL)
	{
		finish_with_error(conn, "mysql_real_connect() failed\n");
	}
	if (mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout))
	{
		print_error(conn, "[mysql_options] failed.");
	}
	if (mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect))
	{
		print_error(conn, "[mysql_options] failed.");
	}
#ifndef NDEBUG
	mysql_debug("d:t:O,/tmp/client.trace");
	if (mysql_dump_debug_info(conn))
	{
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

	if (mysql_stmt_bind_param(login_procedure, param) != 0)
	{ // Note _param
		print_stmt_error(login_procedure, "Binding dei parametri non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}

	// Run procedure
	if (mysql_stmt_execute(login_procedure) != 0)
	{
		print_stmt_error(login_procedure, "Login non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}

	// Prepare output parameters
	set_binding_param(&param[0], MYSQL_TYPE_LONG, &role, sizeof(role));

	if (mysql_stmt_bind_result(login_procedure, param))
	{
		print_stmt_error(login_procedure, "Bind_result non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}

	// Retrieve output parameter
	if (mysql_stmt_fetch(login_procedure))
	{
		print_stmt_error(login_procedure, "Fetch non riuscito");
		role = FAILED_LOGIN;
		goto out;
	}
	printf("ROLE %d \n", role);
out:
	// Consume the possibly-returned table for the output parameter
	while (mysql_stmt_next_result(login_procedure) != -1)
	{
	}

	mysql_stmt_free_result(login_procedure);
	mysql_stmt_reset(login_procedure);

	initialize_prepared_stmts(role);
	printf("ROLE %d \n", role);
	return role;
}

void db_switch_to_login(void)
{
	close_prepared_stmts();
	if (mysql_change_user(conn, getenv("LOGIN_USER"), getenv("LOGIN_PASS"), getenv("DB")))
	{
		fprintf(stderr, "mysql_change_user() failed: %s\n", mysql_error(conn));
		exit(EXIT_FAILURE);
	}

	if (!initialize_prepared_stmts(LOGIN_ROLE))
	{
		fprintf(stderr, "[FATAL] Cannot initialize prepared statements.\n");
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

void do_insert_costumer(struct cliente *cliente) // funziona
{
	MYSQL_BIND param[8];
	MYSQL_TIME datadocumentazione;

	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, sizeof(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, sizeof(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, sizeof(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, sizeof(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, sizeof(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, sizeof(cliente->recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, cliente->fax, sizeof(cliente->fax));

	if (mysql_stmt_bind_param(insert_costumer, param) != 0)
	{
		print_stmt_error(insert_costumer, "Could not bind parameters for insert_costumer");
		return;
	}

	if (mysql_stmt_execute(insert_costumer) != 0)
	{
		print_stmt_error(insert_costumer, "Could not execute insert_costumer");
		return;
	}

	mysql_stmt_free_result(insert_costumer);

	mysql_stmt_reset(insert_costumer);
}

void do_insert_reservation(struct prenotazione *prenotazione) // funziona
{
	MYSQL_BIND param[2];
	MYSQL_TIME datadiprenotazione;

	date_to_mysql_time(prenotazione->datadiprenotazione, &datadiprenotazione);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, prenotazione->clienteprenotante, sizeof(prenotazione->clienteprenotante));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &datadiprenotazione, sizeof(datadiprenotazione));

	if (mysql_stmt_bind_param(insert_reservation, param) != 0)
	{
		print_stmt_error(insert_reservation, "Could not bind parameters for insert_reservation");
		return;
	}
	if (mysql_stmt_execute(insert_reservation) != 0)
	{
		print_stmt_error(insert_reservation, "Could not execute insert_reservation");
		return;
	}

	mysql_stmt_free_result(insert_reservation);
	mysql_stmt_reset(insert_reservation);
}

void do_insert_seat(struct postoprenotato *postoprenotato) // Funziona
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
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &prenotazioneassociata, sizeof(prenotazioneassociata));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &etapasseggero, sizeof(etapasseggero));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, postoprenotato->nomepasseggero, sizeof(postoprenotato->nomepasseggero));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, postoprenotato->cognomepasseggero, sizeof(postoprenotato->cognomepasseggero));

	bind_exe(insert_seat, param, "insert_seat");

	mysql_stmt_free_result(insert_seat);
	mysql_stmt_reset(insert_seat);
}

void do_insert_assoc(struct associata *associata) // Funziona
{
	MYSQL_BIND param[5];
	MYSQL_TIME datafinesoggiorno;
	MYSQL_TIME datainiziosoggiorno;

	char *buff = "insert_assoc";
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

	bind_exe(insert_assoc, param, buff);

	mysql_stmt_free_result(insert_assoc);
	mysql_stmt_reset(insert_assoc);
}

void do_insert_review(struct revisione *revisione)
{
	MYSQL_BIND param[8];
	MYSQL_TIME datainizio;
	MYSQL_TIME datafine;

	char *buff = "insert_review";
	int addettoallarevisione;
	int chilometraggio;

	date_to_mysql_time(revisione->datainizio, &datainizio);
	date_to_mysql_time(revisione->datafine, &datafine);

	addettoallarevisione = revisione->addettoallarevisione;
	chilometraggio = revisione->chilometraggio;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, revisione->mezzorevisionato, strlen(revisione->mezzorevisionato));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &addettoallarevisione, sizeof(addettoallarevisione));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datainizio, sizeof(datainizio));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &chilometraggio, sizeof(chilometraggio));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, revisione->operazionieseguite, strlen(revisione->operazionieseguite));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, revisione->tipologiarevisione, strlen(revisione->tipologiarevisione));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, revisione->motivazione, strlen(revisione->motivazione));

	bind_exe(insert_review, param, buff);

	mysql_stmt_free_result(insert_review);
	mysql_stmt_reset(insert_review);
}

void do_validate_reservation(struct prenotazione *prenotazione) // Funziona
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

	bind_exe(validate_reservation, param, "validate_reservation");

	mysql_stmt_free_result(validate_reservation);
	mysql_stmt_reset(validate_reservation);
}

void do_insert_sostitution(struct sostituito *sostituito) // FUNZIONA
{
	MYSQL_BIND param[3];

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &sostituito->revisioneassociata, sizeof(sostituito->revisioneassociata));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, sostituito->ricambioutilizzato, strlen(sostituito->ricambioutilizzato));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &sostituito->quantitasostituita, sizeof(sostituito->quantitasostituita));

	bind_exe(insert_sostitution, param, "insert_sostitution");

	mysql_stmt_free_result(insert_sostitution);
	mysql_stmt_reset(insert_sostitution);
}


void do_update_trip_seat(struct viaggio *viaggio) // Funziona
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

void do_update_km(struct mezzo *mezzo) 
{
	MYSQL_BIND param[2];
	char *buff = "update_km"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING ,mezzo->targa, strlen(mezzo->targa));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &mezzo->valorecontakm, sizeof(mezzo->valorecontakm));

	bind_exe(update_km, param, buff);

	mysql_stmt_free_result(update_km);
	mysql_stmt_reset(update_km);
}

void do_select_model(struct modello *modello)
{
	MYSQL_BIND param[3];
	
	char *buff = "select_model";

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, modello->nomemodello, strlen(modello->nomemodello));
	
	if (bind_exe(select_model, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, modello->casacostruttrice, sizeof(modello->casacostruttrice));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, modello->datitecnici, sizeof(modello->datitecnici));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &modello->numeroposti, sizeof(modello->numeroposti));
	
	take_result(select_model, param, buff);
 
	stop:
	mysql_stmt_free_result(select_model);
	mysql_stmt_reset(select_model);
 
}

void do_select_seat(struct postoprenotato *postoprenotato)
{
	MYSQL_BIND param[4];
	
	char *buff = "select_seat";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &postoprenotato->numerodiposto, sizeof(postoprenotato->numerodiposto));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &postoprenotato->viaggioassociato, sizeof(postoprenotato->viaggioassociato));
	
	if (bind_exe(select_seat, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, postoprenotato->nomepasseggero, sizeof(postoprenotato->nomepasseggero));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, postoprenotato->cognomepasseggero, sizeof(postoprenotato->cognomepasseggero));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &postoprenotato->etapasseggero, sizeof(postoprenotato->etapasseggero));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &postoprenotato->prenotazioneassociata, sizeof(postoprenotato->prenotazioneassociata));
	
	take_result(select_seat, param, buff);
 
	stop:
	mysql_stmt_free_result(select_seat);
	mysql_stmt_reset(select_seat);
 
}

void do_select_user(struct utente *utente)
{
	MYSQL_BIND param[3];
	
	char *buff = "select_user";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &utente->id, sizeof(utente->id));
	
	if (bind_exe(select_user, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, utente->email, sizeof(utente->email));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, utente->pswrd, sizeof(utente->pswrd));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &utente->tipo, sizeof(utente->tipo));
	
	take_result(select_user, param, buff);
 
	stop:
	mysql_stmt_free_result(select_user);
	mysql_stmt_reset(select_user);
 
}

void do_select_tome(struct tome *tome)
{
	MYSQL_BIND param[2];
	
	char *buff = "select_tome";

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tome->tourinquestione, sizeof(tome->tourinquestione));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &tome->metainquestione, sizeof(tome->metainquestione));
	
	if (bind_exe(select_tome, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tome->descrizione, sizeof(tome->descrizione));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tome->meta, sizeof(tome->meta));
	
	take_result(select_tome, param, buff);
 
	stop:
	mysql_stmt_free_result(select_tome);
	mysql_stmt_reset(select_tome);
 
}

void do_select_ofr(struct offre *offre)
{
	MYSQL_BIND param[3];
	
	char *buff = "select_ofr";


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &offre->albergoofferente, sizeof(offre->albergoofferente));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &offre->idservizio, sizeof(offre->servizio));
	
	
	if (bind_exe(select_ofr, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, offre->meta, sizeof(offre->meta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, offre->servizio, sizeof(offre->servizio));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, offre->descrizione, sizeof(offre->descrizione));
	
	if(take_result(select_ofr, param, buff)== -1)
		goto stop; 
	
	stop:
	mysql_stmt_free_result(select_ofr);
	mysql_stmt_reset(select_ofr);
 
}

void do_select_fme(struct fme *fme)
{
	MYSQL_BIND param[3];
	
	char *buff = "select_fme";


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &fme->foto, sizeof(fme->foto));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &fme->meta, sizeof(fme->meta));
	
	
	if (bind_exe(select_fme, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, fme->nome, sizeof(fme->nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, fme->descrizione, sizeof(fme->descrizione));
	set_binding_param(&param[2], MYSQL_TYPE_BLOB, fme->immagine, sizeof(fme->immagine));
	
	if(take_result(select_fme, param, buff)== -1)
		goto stop; 
	
	stop:
	mysql_stmt_free_result(select_fme);
	mysql_stmt_reset(select_fme);
 
}

void do_select_fmo(struct fmo *fmo)
{
	MYSQL_BIND param[2];
	
	char *buff = "select_fmo";


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &fmo->foto, sizeof(fmo->foto));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, fmo->modello, strlen(fmo->modello));
	
	
	if (bind_exe(select_fmo, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, fmo->descrizione, sizeof(fmo->descrizione));
	set_binding_param(&param[1], MYSQL_TYPE_BLOB, fmo->immagine, sizeof(fmo->immagine));
	
	if(take_result(select_fmo, param, buff)== -1)
		goto stop; 
	
	stop:
	mysql_stmt_free_result(select_fmo);
	mysql_stmt_reset(select_fmo);
 
}
 

void do_select_employee(struct dipendente*dipendente)
{
	MYSQL_BIND param[4];
	
	char *buff = "select_employee";

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &dipendente->iddipendente, sizeof(dipendente->iddipendente));
	
	if (bind_exe(select_employee, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, dipendente->nomedipendente, sizeof(dipendente->nomedipendente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, dipendente->cognomedipendente, sizeof(dipendente->cognomedipendente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, dipendente->tipologiadipendente, sizeof(dipendente->cognomedipendente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, dipendente->telefonoaziendale, sizeof(dipendente->telefonoaziendale));
	
	
	if(take_result(select_employee, param, buff)== -1)
		goto stop; 
	
	stop:
	mysql_stmt_free_result(select_employee);
	mysql_stmt_reset(select_employee);
 
}

void do_select_skills(struct competenze *competenze)
{
	MYSQL_BIND param[2];

	
	char *buff = "select_skills";

	char telefono[VARCHAR_LEN];
	char meccanico[VARCHAR_LEN];  


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &competenze->meccanicocompetente, sizeof(competenze->meccanicocompetente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, competenze->modelloassociato, strlen(competenze->modelloassociato));
	
	if (bind_exe(select_skills, param, buff) == -1)
		goto stop;


	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, meccanico, sizeof(meccanico));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, telefono, sizeof(telefono));
	
	
	if(take_result(select_skills, param, buff)== -1)
		goto stop; 
	
	strcpy(competenze->modelloassociato, meccanico); 
	strcpy(competenze->telefono, telefono);
	
	stop:
	mysql_stmt_free_result(select_skills);
	mysql_stmt_reset(select_skills);
}


void do_select_assoc(struct associata *associata)
{
	MYSQL_BIND param[3];
	MYSQL_TIME datainiziosoggiorno; 
	MYSQL_TIME datafinesoggiorno;

	char *buff = "select_assoc";

	date_to_mysql_time(associata->datainiziosoggiorno, &datainiziosoggiorno);
	date_to_mysql_time(associata->datafinesoggiorno,&datafinesoggiorno);

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &associata->albergoinquestione, sizeof(associata->albergoinquestione));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &associata->cameraprenotata, sizeof(associata->cameraprenotata));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &associata->ospite, sizeof(associata->ospite));

	if (bind_exe(select_assoc, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_DATE, &datainiziosoggiorno, sizeof(datainiziosoggiorno));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &datafinesoggiorno, sizeof(datafinesoggiorno));
	 
	
	if (take_result(select_assoc, param, buff)== -1)
		goto stop; 

	mysql_date_to_string(&datainiziosoggiorno, associata->datainiziosoggiorno); 
	mysql_date_to_string(&datafinesoggiorno, associata->datafinesoggiorno); 

	stop:

	mysql_stmt_free_result(select_assoc);
	mysql_stmt_reset(select_assoc);
}

void do_select_sparepart(struct ricambio *ricambio) //FUNZIONA
{
	MYSQL_BIND param[5];

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, ricambio->codice, strlen(ricambio->codice));

	if (bind_exe(select_sparepart, param, "select_sparepart") == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_FLOAT, &ricambio->costounitario, sizeof(ricambio->costounitario));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &ricambio->quantitadiriordino, sizeof(ricambio->quantitadiriordino));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, ricambio->descrizione, sizeof(ricambio->descrizione));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &ricambio->scortaminima, sizeof(ricambio->scortaminima));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &ricambio->quantitainmagazzino, sizeof(ricambio->quantitainmagazzino));

	take_result(select_sparepart, param, "select_sparepart");

stop:

	mysql_stmt_free_result(select_sparepart);
	mysql_stmt_reset(select_sparepart);
}

void do_select_bus(struct mezzo *mezzo)
{
	MYSQL_BIND param[6];
	MYSQL_TIME dataultimarevisioneinmotorizzazione;
	MYSQL_TIME dataimmatricolazione;

	char *buff = "select_bus";  

	date_to_mysql_time(mezzo->dataultimarevisioneinmotorizzazione, &dataultimarevisioneinmotorizzazione);
	date_to_mysql_time(mezzo->dataimmatricolazione, &dataimmatricolazione);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzo->targa, strlen(mezzo->targa));

	if (bind_exe(select_bus, param, buff) == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzo->modellomezzo, sizeof(mezzo->modellomezzo));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &dataultimarevisioneinmotorizzazione, sizeof(dataultimarevisioneinmotorizzazione));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, mezzo->ingombri, sizeof(mezzo->ingombri));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &mezzo->autonomia, sizeof(mezzo->autonomia));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &mezzo->valorecontakm, sizeof(mezzo->valorecontakm));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &dataimmatricolazione, sizeof(dataimmatricolazione));

	if( take_result(select_bus, param, buff) == -1)
		goto stop; 

   	stop:

	mysql_date_to_string(&dataultimarevisioneinmotorizzazione, mezzo->dataultimarevisioneinmotorizzazione);
	mysql_date_to_string(&dataimmatricolazione, mezzo->dataimmatricolazione);

	mysql_stmt_free_result(select_bus);
	mysql_stmt_reset(select_bus);
}

void do_select_review(struct revisione *revisione) // FUNZIONA
{
	MYSQL_BIND param[8];
	MYSQL_TIME datainizio;
	MYSQL_TIME datafine;

	char *buff = "select_review";

	init_mysql_timestamp(&datainizio);
	init_mysql_timestamp(&datafine);
 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &revisione->idrevisione, sizeof(revisione->idrevisione));
	
	if (bind_exe(select_review, param, buff) == -1)
		goto stop;
	
	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, revisione->mezzorevisionato, sizeof(revisione->mezzorevisionato));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &revisione->addettoallarevisione, sizeof(revisione->addettoallarevisione));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datainizio, sizeof(datainizio));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &revisione->chilometraggio, sizeof(revisione->chilometraggio));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, revisione->operazionieseguite, sizeof(revisione->operazionieseguite));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, revisione->tipologiarevisione, sizeof(revisione->tipologiarevisione));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, revisione->motivazione, sizeof(revisione->motivazione));
	
	if (take_result(select_review, param, buff) == -1)
		goto stop;
	
	mysql_date_to_string(&datainizio, revisione->datainizio);
	mysql_date_to_string(&datafine, revisione->datafine);
	
	stop:
	mysql_stmt_free_result(select_review);
	mysql_stmt_reset(select_review);
}

void do_select_trip(struct viaggio *viaggio) // Funziona
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

	if (bind_exe(select_trip, param, "select_trip") == -1)
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

	if (take_result(select_trip, param, "select_trip") == -1)
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

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, strlen(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, cliente->nomecliente, sizeof(cliente->nomecliente));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cliente->cognomecliente, sizeof(cliente->cognomecliente));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, cliente->indirizzocliente, sizeof(cliente->indirizzocliente));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cliente->codicefiscale, sizeof(cliente->codicefiscale));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &datadocumentazione, sizeof(datadocumentazione));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, cliente->recapitotelefonico, sizeof(cliente->recapitotelefonico));
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, cliente->fax, sizeof(cliente->fax));

	if (bind_exe(select_costumer, param, "select_costumer") == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, eml, VARCHAR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, nmc, VARCHAR_LEN);
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, cgm, VARCHAR_LEN);
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, ind, VARCHAR_LEN);
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, cdf, VARCHAR_LEN);
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &ddc, DATE_LEN);
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, tel, VARCHAR_LEN);
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, fax, VARCHAR_LEN);

	if (take_result(select_costumer, param, "select_costumer") == -1)
		goto stop;

	strcpy(cliente->emailcliente, eml);
	strcpy(cliente->nomecliente, nmc);
	strcpy(cliente->cognomecliente, cgm);
	strcpy(cliente->codicefiscale, cdf);
	strcpy(cliente->indirizzocliente, ind);
	strcpy(cliente->recapitotelefonico, tel);
	strcpy(cliente->fax, fax);
	mysql_date_to_string(&ddc, cliente->datadocumentazione);

stop:
	mysql_stmt_free_result(select_costumer);
	mysql_stmt_reset(select_costumer);
}

void do_select_reservation(struct prenotazione *prenotazione) // Funziona
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
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &datadiprenotazione, sizeof(datadiprenotazione));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &datadiconferma, sizeof(datadiconferma));
	set_binding_param(&param[4], MYSQL_TYPE_DATE, &datasaldo, sizeof(datasaldo));

	if (bind_exe(select_reservation, param, "select_reservation") == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cli, VARCHAR_LEN);
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &ddp, sizeof(ddp));
	set_binding_param(&param[2], MYSQL_TYPE_DATE, &ddc, sizeof(ddc));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &dds, sizeof(dds));

	if (take_result(select_reservation, param, "select_reservation") == -1)
		goto stop;

	strcpy(prenotazione->clienteprenotante, cli);
	mysql_date_to_string(&ddp, prenotazione->datadiprenotazione);
	mysql_date_to_string(&ddc, prenotazione->datadiconferma);
	mysql_date_to_string(&dds, prenotazione->datasaldo);

stop:
	mysql_stmt_free_result(select_reservation);
	mysql_stmt_reset(select_reservation);
}

void do_update_data_doc(struct cliente *cliente) // funziona
{
	MYSQL_BIND param[2];
	MYSQL_TIME datadocumentazione;

	date_to_mysql_time(cliente->datadocumentazione, &datadocumentazione);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, cliente->emailcliente, sizeof(cliente->emailcliente));
	set_binding_param(&param[1], MYSQL_TYPE_DATETIME, &datadocumentazione, sizeof(datadocumentazione));

	if (mysql_stmt_bind_param(update_data_doc, param) != 0)
	{
		print_stmt_error(update_data_doc, "Could not bind parameters for update_data_doc");
		return;
	}
	if (mysql_stmt_execute(update_data_doc) != 0)
	{
		print_stmt_error(update_data_doc, "Could not execute update_data_doc");
		return;
	}
	mysql_stmt_free_result(update_data_doc);
	mysql_stmt_reset(update_data_doc);
}
void do_select_tour(struct tour *tour)
{
	MYSQL_BIND param[7];

	int minimopartecipanti;
	float assicurazionemedica;
	float bagaglio;
	float garanziaannullamento;
	signed char accompagnatrice;

	char den[VARCHAR_LEN];
	char des[DES_LEN];
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

	if (bind_exe(select_tour, param, "select_tour") == -1)
		goto stop;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, den, sizeof(den));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, des, sizeof(des));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &mip, sizeof(mip));
	set_binding_param(&param[3], MYSQL_TYPE_FLOAT, &amd, sizeof(amd));
	set_binding_param(&param[4], MYSQL_TYPE_FLOAT, &bgl, sizeof(bgl));
	set_binding_param(&param[5], MYSQL_TYPE_FLOAT, &gan, sizeof(gan));
	set_binding_param(&param[6], MYSQL_TYPE_TINY, &acc, sizeof(acc));

	if (take_result(select_tour, param, "select_tour") == -1)
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

	if (mysql_stmt_bind_param(select_destination, param) != 0)
	{
		print_stmt_error(select_destination, "Could not bind parameters for select_destination");
		return;
	}
	// Run procedure
	if (mysql_stmt_execute(select_destination) != 0)
	{
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

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idservizio, sizeof(idservizio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, servizio->nomeservizio, sizeof(servizio->nomeservizio));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, servizio->descrizioneservizio, sizeof(servizio->descrizioneservizio));

	if (mysql_stmt_bind_param(select_service, param) != 0)
	{
		print_stmt_error(select_service, "Could not bind parameters for select_service");
		return;
	}
	if (mysql_stmt_execute(select_service) != 0)
	{
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

	if (mysql_stmt_bind_param(select_comfort, param) != 0)
	{
		print_stmt_error(select_comfort, "Could not bind parameters for select_comfort");
		return;
	}
	if (mysql_stmt_execute(select_comfort) != 0)
	{
		print_stmt_error(select_comfort, "Could not execute select_comfort");
		return;
	}
	mysql_stmt_free_result(select_comfort);
	mysql_stmt_reset(select_comfort);
}

void do_select_picture(struct documentazionefotografica *documentazionefotografica)
{
	MYSQL_BIND param[2];

	int idfoto;

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idfoto, sizeof(idfoto));
	set_binding_param(&param[1], MYSQL_TYPE_BLOB, documentazionefotografica->foto, sizeof(documentazionefotografica->foto));

	if (mysql_stmt_bind_param(select_picture, param) != 0)
	{
		print_stmt_error(select_picture, "Could not bind parameters for select_picture");
		return;
	}
	if (mysql_stmt_execute(select_picture) != 0)
	{
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
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &costo, sizeof(costo));

	if (mysql_stmt_bind_param(select_room, param) != 0)
	{
		print_stmt_error(select_room, "Could not bind parameters for select_room");
		return;
	}
	if (mysql_stmt_execute(select_room) != 0)
	{
		print_stmt_error(select_room, "Could not execute select_room");
		return;
	}
	mysql_stmt_free_result(select_room);
	mysql_stmt_reset(select_room);
}

void do_select_max_idreview(struct revisione *revisione )
{
	MYSQL_BIND param[1]; 
	char *buff = "select_max_idreview"; 

	if(exe_proc(select_max_idreview, buff)==-1)
		goto stop; 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &revisione->idrevisione, sizeof(revisione->idrevisione));

	take_result(select_max_idreview,param,buff); 

	stop: 
	mysql_stmt_free_result(select_max_idreview);
	mysql_stmt_reset(select_max_idreview);
}

void do_update_spareparts_number(struct ricambio *ricambio) //FUNZIONA
{
	MYSQL_BIND param[2];
	char *buff = "update_spareparts_number"; 

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, ricambio->codice, strlen(ricambio->codice));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &ricambio->quantitainmagazzino, sizeof(ricambio->quantitainmagazzino));
	
	bind_exe(update_spareparts_number, param, buff);

	mysql_stmt_free_result(update_spareparts_number);
	mysql_stmt_reset(update_spareparts_number);
}

struct info_modelli *get_info_modello(char *nmd)
{
	MYSQL_BIND param[7];

	struct info_modelli *info_modello = NULL;
	char *buff = "select_model_comfort";

	char casacostruttrice[VARCHAR_LEN];
	int numeroposti;
	char nomecomfort[VARCHAR_LEN];
	char descrizionecomfort[DES_LEN];
	char foto[PIC];
	char descrizionefoto[DES_LEN];
	int idfoto;

	size_t rows, count;
	count = 0;
	int cmpr, status;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nmd, strlen(nmd));

	bind_exe(select_model_comfort, param, buff);
	rows = take_rows(select_model_comfort,buff); 
	if(rows == -1)
		goto stop;

	info_modello = malloc((sizeof(struct info_modelli) + sizeof(info_modello)) * rows);
	memset(info_modello, 0, sizeof(*info_modello) + sizeof(struct info_modelli) * rows);

	if (info_modello == NULL)
	{
		printf("Impossibile eseguire la malloc su tour info");
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, casacostruttrice, sizeof(casacostruttrice));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &numeroposti, sizeof(numeroposti));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, nomecomfort, sizeof(nomecomfort));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, descrizionecomfort, sizeof(descrizionecomfort));
	set_binding_param(&param[4], MYSQL_TYPE_BLOB, foto, sizeof(foto));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, descrizionefoto, sizeof(descrizionefoto));
	set_binding_param(&param[6], MYSQL_TYPE_LONG, &idfoto, sizeof(idfoto));

	if (mysql_stmt_bind_result(select_model_comfort, param))
	{
		print_stmt_error(select_model_comfort, "\n\n Impossibile eseguire il bind risult\n\n");
		free(info_modello);
		info_modello = NULL;
		goto stop;
	}

	info_modello->num_modelli = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_model_comfort);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			print_stmt_error(select_model_comfort, "\nImpossibile eseguire fetch");
		}

		strcpy(info_modello->info_modelli[count].casacostruttrice, casacostruttrice);
		info_modello->info_modelli[count].numeroposti = numeroposti;
		strcpy(info_modello->info_modelli[count].nomecomfort, nomecomfort);
		strcpy(info_modello->info_modelli[count].descrizionecomfort, descrizionecomfort);
		strcpy(info_modello->info_modelli[count].foto, foto);
		strcpy(info_modello->info_modelli[count].descrizionefoto, descrizionefoto);
		info_modello->info_modelli[count].idfoto = idfoto;

		cmpr = strcmp(info_modello->info_modelli[count].casacostruttrice, info_modello->info_modelli[count - 1].casacostruttrice);

		if (cmpr != 0)
		{
			printf("Casa costruttrice:	%s \n", info_modello->info_modelli[count].casacostruttrice);
			printf("Numero di posti:	%d	\n\n", info_modello->info_modelli[count].numeroposti);
		}
		printf("Comfort:	 	%s \n", info_modello->info_modelli[count].nomecomfort);
		printf("%s \n", info_modello->info_modelli[count].descrizionecomfort);

		if (info_modello->info_modelli[count].idfoto != info_modello->info_modelli[count - 1].idfoto)
		{
			printf("%s\n", info_modello->info_modelli[count].foto);
			printf("Descrizione foto:%s\n\n", info_modello->info_modelli[count].descrizionefoto);
		}
		count++;
	}
stop:
	mysql_stmt_free_result(select_model_comfort);
	mysql_stmt_reset(select_model_comfort);
	free(info_modello);
};

struct revisioni_scadute *get_info_revisioni(void)
{
	MYSQL_BIND param[4];
	MYSQL_TIME datafine;

	struct revisioni_scadute *info_revisioni = NULL;
	char *buff = "select_expired_review";
	char mezzorevisionato[VARCHAR_LEN];
	int chilometraggio;
	int valorekm;

	size_t rows;
	int count, status, cmpr;
	count = 0;

	init_mysql_timestamp(&datafine);

	rows = take_rows(select_expired_review, buff);
	if(rows == -1)
		goto stop;

	info_revisioni = malloc((sizeof(struct revisioni_scadute) + sizeof(info_revisioni)) * rows);
	memset(info_revisioni, 0, sizeof(*info_revisioni) + sizeof(struct revisioni_scadute) * rows);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, mezzorevisionato, sizeof(mezzorevisionato));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &datafine, sizeof(datafine));
	set_binding_param(&param[2], MYSQL_TYPE_LONG, &chilometraggio, sizeof(chilometraggio));
	set_binding_param(&param[3], MYSQL_TYPE_LONG, &valorekm, sizeof(valorekm));

	if (mysql_stmt_bind_result(select_expired_review, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_expired_review, "\n\n Impossibile eseguire il bind risult\n\n");
		free(info_revisioni);
		info_revisioni = NULL;
		goto stop;
	}

	info_revisioni->num_revisione = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_expired_review);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			printf("Procedura: %s", buff);
			print_stmt_error(select_expired_review, "\nImpossibile eseguire fetch");
		}
		strcpy(info_revisioni->revisioni_scadute[count].mezzorevisionato, mezzorevisionato);
		mysql_date_to_string(&datafine, info_revisioni->revisioni_scadute[count].datafine);
		info_revisioni->revisioni_scadute[count].chilometraggio = chilometraggio;
		info_revisioni->revisioni_scadute[count].idrevisione = valorekm;
		cmpr = strcmp(info_revisioni->revisioni_scadute[count].mezzorevisionato, info_revisioni->revisioni_scadute[count - 1].mezzorevisionato);
		if (cmpr != 0)
		{
			printf("*Targa mezzo:		%s \n", info_revisioni->revisioni_scadute[count].mezzorevisionato);
			printf("Data ultima revisione:	%s	\n", info_revisioni->revisioni_scadute[count].datafine);
			printf("Chilometri revisone:	%d \n", info_revisioni->revisioni_scadute[count].chilometraggio);
			printf("Chilometri attuali:	%d	\n\n", info_revisioni->revisioni_scadute[count].idrevisione);
		}

		count++;
	}
stop:
	mysql_stmt_free_result(select_expired_review);
	mysql_stmt_reset(select_expired_review);
	free(info_revisioni);
};

struct servizi_albergo *get_servizi_albergo(int idh)
{
	MYSQL_BIND param[2];

	struct servizi_albergo *info_servizi = NULL;
	char *buff = "select_hotel_service";
	char nomeservizio[VARCHAR_LEN];
	char descrizioneservizio[DES_LEN];
	size_t rows;
	int count, status;
	count = 0;

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idh, sizeof(idh));

	bind_exe(select_hotel_service, param, buff);
	rows = take_rows(select_hotel_service, buff);
	if(rows == -1)
		goto stop;

	info_servizi = malloc((sizeof(struct servizi_albergo) + sizeof(info_servizi)) * rows);
	memset(info_servizi, 0, sizeof(*info_servizi) + sizeof(struct servizi_albergo) * rows);

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nomeservizio, sizeof(nomeservizio));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, descrizioneservizio, sizeof(descrizioneservizio));

	if (mysql_stmt_bind_result(select_hotel_service, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_hotel_service, "\n\n Impossibile eseguire il bind risult\n\n");
		free(info_servizi);
		info_servizi = NULL;
		goto stop;
	}

	info_servizi->num_servizi = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_hotel_service);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			printf("Procedura: %s", buff);
			print_stmt_error(select_hotel_service, "\nImpossibile eseguire fetch");
		}
		strcpy(info_servizi->servizi_albergo[count].nomeservizio, nomeservizio);
		strcpy(info_servizi->servizi_albergo[count].descrizioneservizio, descrizioneservizio);

		printf("* %s *\n", info_servizi->servizi_albergo[count].nomeservizio);
		printf("Descrizione:		%s	\n\n", info_servizi->servizi_albergo[count].descrizioneservizio);

		count++;
	}
stop:
	mysql_stmt_free_result(select_hotel_service);
	mysql_stmt_reset(select_hotel_service);
};

struct info_mete *get_mete_info(int idv)
{
	MYSQL_BIND param[14];
	MYSQL_TIME darrivo;
	MYSQL_TIME dpartenza;
	MYSQL_TIME oarrivo;
	MYSQL_TIME opartenza;
	MYSQL_TIME oapertura;
	
	printf("Malloc");
	struct info_mete *info_mete = NULL;
	int status;
	int cmpr;
	char *buff = "select_dest_tour";
	char nome[VARCHAR_LEN];
	float supplemento;
	int codicealbergo;
	char tipologiameta[VARCHAR_LEN];
	char desfoto[VARCHAR_LEN];
	char foto[BLOB_LEN];
	signed char guida;
	char trattamento[VARCHAR_LEN];
	char categoriaalbergo[VARCHAR_LEN];
	size_t rows, count;
	count = 0;

	init_mysql_timestamp(&darrivo);
	init_mysql_timestamp(&dpartenza);
	init_mysql_timestamp(&oarrivo);
	init_mysql_timestamp(&opartenza);
	init_mysql_timestamp(&oapertura); 

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idv, sizeof(idv));

	bind_exe(select_dest_tour, param, buff);

	rows = take_rows(select_dest_tour, buff);
	if(rows == -1)
		goto stop;

	info_mete = malloc((sizeof(struct mete_tour) + sizeof(info_mete)) * rows);
	memset(info_mete, 0, sizeof(*info_mete) + sizeof(struct mete_tour) * rows);

	if (info_mete == NULL)
	{
		printf("Impossibile eseguire la malloc su %s", buff);
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nome, sizeof(nome));
	set_binding_param(&param[1], MYSQL_TYPE_DATE, &darrivo, sizeof(darrivo));
	set_binding_param(&param[2], MYSQL_TYPE_TIME, &oarrivo, sizeof(oarrivo));
	set_binding_param(&param[3], MYSQL_TYPE_DATE, &dpartenza, sizeof(dpartenza));
	set_binding_param(&param[4], MYSQL_TYPE_TIME, &opartenza, sizeof(opartenza));
	set_binding_param(&param[5], MYSQL_TYPE_FLOAT, &supplemento, sizeof(supplemento));
	set_binding_param(&param[6], MYSQL_TYPE_VAR_STRING, tipologiameta, sizeof(tipologiameta));
	set_binding_param(&param[7], MYSQL_TYPE_TINY, &guida, sizeof(guida));
	set_binding_param(&param[8], MYSQL_TYPE_TIME, &oapertura, sizeof(oapertura));
	set_binding_param(&param[9], MYSQL_TYPE_VAR_STRING, trattamento, sizeof(trattamento));
	set_binding_param(&param[10], MYSQL_TYPE_VAR_STRING, categoriaalbergo, sizeof(categoriaalbergo));
	set_binding_param(&param[11], MYSQL_TYPE_VAR_STRING, desfoto, sizeof(desfoto));
	set_binding_param(&param[12], MYSQL_TYPE_BLOB, foto, sizeof(foto));
	set_binding_param(&param[13], MYSQL_TYPE_LONG, &codicealbergo, sizeof(codicealbergo));

	if (mysql_stmt_bind_result(select_dest_tour, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_dest_tour, "\n\n Impossibile eseguire il bind risult\n\n");
		free(info_mete);
		info_mete = NULL;
		goto stop;
	}

	info_mete->num_mete = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_dest_tour);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			print_stmt_error(select_dest_tour, "\nImpossibile eseguire fetch");
		}
		strcpy(info_mete->info_mete[count].nome, nome);
		strcpy(info_mete->info_mete[count].tipologiameta, tipologiameta);
		mysql_date_to_string(&darrivo, info_mete->info_mete[count].darrivo);
		mysql_date_to_string(&dpartenza, info_mete->info_mete[count].dpartenza);
		mysql_time_to_string(&oarrivo, info_mete->info_mete[count].oarrivo);
		mysql_time_to_string(&opartenza, info_mete->info_mete[count].opartenza);
		mysql_time_to_string(&oapertura, info_mete->info_mete[count].oapertura);

		info_mete->info_mete[count].supplemento = supplemento;
		info_mete->info_mete[count].codicealbergo = codicealbergo;

		strcpy(info_mete->info_mete[count].trattamento, trattamento);
		strcpy(info_mete->info_mete[count].categoriaalbergo, categoriaalbergo);
		strcpy(info_mete->info_mete[count].desfoto, desfoto);
		strcpy(info_mete->info_mete[count].foto, foto);

		cmpr = strcmp(info_mete->info_mete[count].nome, info_mete->info_mete[count - 1].nome);
		if (cmpr != 0)
		{
			printf("* %s *\n", info_mete->info_mete[count].nome);
			printf("Data di arrivo:		%s	", info_mete->info_mete[count].darrivo);
			printf("Ora di arrivo:	  	%s \n", info_mete->info_mete[count].oarrivo);
			printf("Data di partenza:	%s	", info_mete->info_mete[count].dpartenza);
			printf("Ora di partenza: 	%s \n", info_mete->info_mete[count].opartenza);
			printf("Supplemento:		%f euro\n", info_mete->info_mete[count].supplemento);
			printf("Tipologia meta:		%s 	\n", info_mete->info_mete[count].tipologiameta);

			if (strcmp(info_mete->info_mete[count].tipologiameta, "Bene") == 0)
			{
				printf("Orario di apertura:	%s 	\n", info_mete->info_mete[count].oapertura);
				printf("Guida prevista:		%d 	\n", info_mete->info_mete[count].guida);
			}
			else
			{
				printf("Trattamento:		%s \n", info_mete->info_mete[count].trattamento);
				printf("Categoria:		%s 	\n", info_mete->info_mete[count].categoriaalbergo);
				printf("Codice albergo:		%d \n", info_mete->info_mete[count].codicealbergo);
			}
		}
		printf("\n");
		printf("Foto:  %s	\n", info_mete->info_mete[count].foto);
		printf("Descrizione foto:	%s \n\n", info_mete->info_mete[count].desfoto);

		count++;
	}
stop:
	mysql_stmt_free_result(select_dest_tour);
	mysql_stmt_reset(select_dest_tour);
	free(info_mete);
};

struct tour_info *get_tour_info(void)
{
	MYSQL_BIND param[13];
	MYSQL_TIME dpv;
	MYSQL_TIME drv;

	struct tour_info *tour_info = NULL;
	char *buff = "select_all_tour";
	char dnm[VARCHAR_LEN];
	char dsc[DES_LEN];
	char nmd[VARCHAR_LEN];
	int mnp;
	int pds;
	int cmpr;
	int cdv;
	int status;
	float mdc;
	float bgl;
	float gnl;
	float csv;
	signed char acm;
	size_t rows, count;
	count = 0;

	init_mysql_timestamp(&dpv);
	init_mysql_timestamp(&drv);

	rows = take_rows(select_all_tour, buff);
	if(rows == -1)
		goto stop;

	tour_info = malloc((sizeof(struct tour_viaggi) + sizeof(tour_info)) * rows);
	memset(tour_info, 0, sizeof(*tour_info) + sizeof(struct tour_viaggi) * rows);

	if (tour_info == NULL)
	{
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
	set_binding_param(&param[7], MYSQL_TYPE_VAR_STRING, nmd, sizeof(nmd));
	set_binding_param(&param[8], MYSQL_TYPE_DATE, &dpv, sizeof(dpv));
	set_binding_param(&param[9], MYSQL_TYPE_DATE, &drv, sizeof(drv));
	set_binding_param(&param[10], MYSQL_TYPE_FLOAT, &csv, sizeof(csv));
	set_binding_param(&param[11], MYSQL_TYPE_LONG, &pds, sizeof(pds));
	set_binding_param(&param[12], MYSQL_TYPE_LONG, &cdv, sizeof(cdv));

	if (mysql_stmt_bind_result(select_all_tour, param))
	{
		print_stmt_error(select_all_tour, "\n\n Impossibile eseguire il bind risult\n\n");
		free(tour_info);
		tour_info = NULL;
		goto stop;
	}

	tour_info->num_tour = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_all_tour);
		if (status == MYSQL_NO_DATA)
			break;
		if (status == 1)
		{
			print_stmt_error(select_all_tour, "\nImpossibile eseguire fetch");
		}
		strcpy(tour_info->tour_info[count].denominazionetour, dnm);
		strcpy(tour_info->tour_info[count].descrizionetour, dsc);

		tour_info->tour_info[count].minimopartecipanti = mnp;
		tour_info->tour_info[count].assicurazionemedica = mdc;
		tour_info->tour_info[count].bagaglio = bgl;
		tour_info->tour_info[count].garanziaannullamento = gnl;
		tour_info->tour_info[count].accompagnatrice = acm;
		tour_info->tour_info[count].codiceviaggio = cdv;

		cmpr = strcmp(tour_info->tour_info[count].denominazionetour, tour_info->tour_info[count - 1].denominazionetour);

		if (cmpr != 0)
		{
			printf("* %s *\n", tour_info->tour_info[count].denominazionetour);
			printf("Descrizione tour:	%s 	\n", tour_info->tour_info[count].descrizionetour);
			printf("Minimo partecipanti:	 %d 	\n", tour_info->tour_info[count].minimopartecipanti);
			printf("Diritti iscrizione: \n");
			printf("Assicurazione medica:	 %f euro\n", tour_info->tour_info[count].assicurazionemedica);
			printf("Bagaglio:		 %f euro\n", tour_info->tour_info[count].bagaglio);
			printf("Garanzia di annullamento:%f euro\n", tour_info->tour_info[count].garanziaannullamento);
			printf("\n-Accompagnatrice prevista:%d 	\n", tour_info->tour_info[count].accompagnatrice);
			printf("\n\nViaggi previsti :\n");
		}
		strcpy(tour_info->tour_info[count].nomemodello, nmd);
		mysql_date_to_string(&dpv, tour_info->tour_info[count].datadipartenzaviaggio);
		mysql_date_to_string(&drv, tour_info->tour_info[count].datadiritornoviaggio);
		tour_info->tour_info[count].costodelviaggio = csv;
		tour_info->tour_info[count].postidisponibili = pds;
		tour_info->tour_info[count].codiceviaggio = cdv;

		printf("Modello pullman:	%s \n", tour_info->tour_info[count].nomemodello);
		printf("Codice viaggio: 	%d \n", tour_info->tour_info[count].codiceviaggio);
		printf("Data di partenza:	%s 	\n", tour_info->tour_info[count].datadipartenzaviaggio);
		printf("Data di riotrno:	%s 	\n", tour_info->tour_info[count].datadiritornoviaggio);
		printf("Prezzo:			%f euro	\n", tour_info->tour_info[count].costodelviaggio);
		printf("Posti disponibili:	%d 	\n", tour_info->tour_info[count].postidisponibili);
		printf("\n");
		count++;
	}
stop:
	mysql_stmt_free_result(select_all_tour);
	mysql_stmt_reset(select_all_tour);
	free(tour_info);
}

struct viaggi_assegnati *get_viaggi_assegnati(int dvr) //funziona
{
	MYSQL_BIND param[9];
	MYSQL_TIME ddp;
	MYSQL_TIME ddr;

	struct viaggi_assegnati *viaggi_assegnati = NULL;
	char *buff = "select_assigned_trip";
	int status; 
	size_t rows, count;
	count = 0;

	char tour[VARCHAR_LEN];
	int viaggio; 
	char modello[VARCHAR_LEN];
	char targa[TAR_LEN];
	int autonomia; 
	char ingombri [VARCHAR_LEN]; 
	int contakm; 

	init_mysql_timestamp(&ddp);
	init_mysql_timestamp(&ddr);


	set_binding_param(&param[0], MYSQL_TYPE_LONG, &dvr, sizeof(dvr));


	 
	 bind_exe(select_assigned_trip, param, buff);
	 rows = take_rows(select_assigned_trip, buff);
	if(rows == -1)
		goto stop; 

	viaggi_assegnati = malloc((sizeof(struct viaggi_mezzi) + sizeof(viaggi_assegnati)) * rows);
	memset(viaggi_assegnati, 0, sizeof(*viaggi_assegnati) + sizeof(struct viaggi_mezzi) * rows);

	if (viaggi_assegnati == NULL)
	{
		printf("Impossibile eseguire la malloc su tour info");
		goto stop;
	}


	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, tour,  sizeof(tour));
	set_binding_param(&param[1], MYSQL_TYPE_LONG, &viaggio, sizeof(viaggio));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, modello, sizeof(modello));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, targa, sizeof(targa));
	set_binding_param(&param[4], MYSQL_TYPE_LONG, &autonomia, sizeof(autonomia));
	set_binding_param(&param[5], MYSQL_TYPE_VAR_STRING, ingombri, sizeof(ingombri));
	set_binding_param(&param[6], MYSQL_TYPE_LONG, &contakm, sizeof(contakm));
	set_binding_param(&param[7], MYSQL_TYPE_DATE, &ddp, sizeof(ddp));
	set_binding_param(&param[8], MYSQL_TYPE_DATE, &ddr, sizeof(ddr));
	
	if (mysql_stmt_bind_result(select_assigned_trip, param))
	{
		print_stmt_error(select_assigned_trip, "\n\n Impossibile eseguire il bind risult\n\n");
		free(viaggi_assegnati);
		viaggi_assegnati = NULL;
		goto stop;
	}

	viaggi_assegnati->num_viaggi = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_assigned_trip);
		if (status == MYSQL_NO_DATA)
			break;
		if (status == 1)
		{
			print_stmt_error(select_assigned_trip, "\nImpossibile eseguire fetch");
		}

		strcpy(viaggi_assegnati->viaggi_assegnati[count].tour, tour);
		strcpy(viaggi_assegnati->viaggi_assegnati[count].modello, modello);
		strcpy(viaggi_assegnati->viaggi_assegnati[count].targa, targa);
		strcpy(viaggi_assegnati->viaggi_assegnati[count].ingombri, ingombri);
		mysql_date_to_string(&ddp,viaggi_assegnati->viaggi_assegnati[count].partenza ); 
		mysql_date_to_string(&ddr,viaggi_assegnati->viaggi_assegnati[count].ritorno);


		viaggi_assegnati->viaggi_assegnati[count].viaggio = viaggio;
		viaggi_assegnati->viaggi_assegnati[count].autonomia= autonomia;
		viaggi_assegnati->viaggi_assegnati[count].contakm = contakm;

		printf("* %s *\n", viaggi_assegnati->viaggi_assegnati[count].tour);
		printf("Codice viaggio: 	%d \n", viaggi_assegnati->viaggi_assegnati[count].viaggio);
		printf("Data di partenza:	%s 	\n", viaggi_assegnati->viaggi_assegnati[count].partenza);
		printf("Data di riotrno:	%s 	\n\n", viaggi_assegnati->viaggi_assegnati[count].ritorno);
		printf("Mezzo impiegato\n");
		printf("Modello pullman:	%s \n", viaggi_assegnati->viaggi_assegnati[count].modello);
		printf("Targa:			%s 	\n", viaggi_assegnati->viaggi_assegnati[count].targa);
		printf("Autonomia mezzo:	%d km	\n", viaggi_assegnati->viaggi_assegnati[count].autonomia);
		printf("Ingombri:		%s \n", viaggi_assegnati->viaggi_assegnati[count].ingombri);	
		printf("Valore conta km:	%d 	\n\n", viaggi_assegnati->viaggi_assegnati[count].contakm);
		count++;
	}
stop:
	mysql_stmt_free_result(select_assigned_trip);
	mysql_stmt_reset(select_assigned_trip);
	free(viaggi_assegnati);
}

struct mete_visite *get_mete_visite(int idv)
{
	MYSQL_BIND param[9];
	MYSQL_TIME darrivo;
	MYSQL_TIME dpartenza;
	MYSQL_TIME oarrivo;
	MYSQL_TIME opartenza;
	

	struct mete_visite *mete_visite = NULL;
	int status;
	int cmpr;
	char *buff = "select_dest_time";

	char nome [VARCHAR_LEN]; 
	char tipologia[VARCHAR_LEN]; 
	char localita[VARCHAR_LEN];
	char regione[VARCHAR_LEN]; 
	char indirizzo[VARCHAR_LEN];
	char arrivo[DATE_LEN];
	char ingresso[TIME_LEN]; 
	char partenza[DATE_LEN]; 
	char uscita[TIME_LEN]; 
	
	size_t rows, count;
	count = 0;

	init_mysql_timestamp(&darrivo);
	init_mysql_timestamp(&dpartenza);
	init_mysql_timestamp(&oarrivo);
	init_mysql_timestamp(&opartenza);

	set_binding_param(&param[0], MYSQL_TYPE_LONG, &idv, sizeof(idv));

	bind_exe(select_dest_time, param, buff);
	rows =take_rows(select_dest_time, buff); 
	if(rows ==-1)
		goto stop; 

	mete_visite = malloc((sizeof(struct mete_visite) + sizeof(mete_visite)) * rows);
	memset(mete_visite, 0, sizeof(*mete_visite) + sizeof(struct mete_visite) * rows);

	if (mete_visite == NULL)
	{
		printf("Impossibile eseguire la malloc su %s", buff);
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nome, sizeof(nome));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, tipologia, sizeof(tipologia));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, localita, sizeof(localita));
	set_binding_param(&param[3], MYSQL_TYPE_VAR_STRING, regione, sizeof(regione));
	set_binding_param(&param[4], MYSQL_TYPE_VAR_STRING, indirizzo, sizeof(indirizzo));
	set_binding_param(&param[5], MYSQL_TYPE_DATE, &darrivo, sizeof(darrivo));
	set_binding_param(&param[6], MYSQL_TYPE_TIME, &oarrivo, sizeof(oarrivo));
	set_binding_param(&param[7], MYSQL_TYPE_DATE, &dpartenza, sizeof(dpartenza));
	set_binding_param(&param[8], MYSQL_TYPE_TIME, &opartenza, sizeof(opartenza));
	
	if (mysql_stmt_bind_result(select_dest_time, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_dest_time, "\n\n Impossibile eseguire il bind risult\n\n");
		free(mete_visite);
		mete_visite = NULL;
		goto stop;
	}

	mete_visite->num_visite = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_dest_time);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			print_stmt_error(select_dest_time, "\nImpossibile eseguire fetch");
		}
		strcpy(mete_visite->mete_visite[count].nome, nome);
		strcpy(mete_visite->mete_visite[count].tipologia, tipologia);
		strcpy(mete_visite->mete_visite[count].localita, localita);
		strcpy(mete_visite->mete_visite[count].regione, regione);
		strcpy(mete_visite->mete_visite[count].indirizzo, indirizzo);
		mysql_date_to_string(&darrivo, mete_visite->mete_visite[count].arrivo);
		mysql_date_to_string(&dpartenza, mete_visite->mete_visite[count].partenza);
		mysql_time_to_string(&oarrivo, mete_visite->mete_visite[count].ingresso);
		mysql_time_to_string(&opartenza, mete_visite->mete_visite[count].uscita);
		
		printf("* %s *\n", mete_visite->mete_visite[count].nome);
		printf("Tipologia meta:		%s 	\n", mete_visite->mete_visite[count].tipologia);
		printf("Località:		%s 	\n", mete_visite->mete_visite[count].localita);
		printf("Regione:		%s 	\n", mete_visite->mete_visite[count].regione);
		printf("Indirizzo:		%s 	\n", mete_visite->mete_visite[count].indirizzo);
		printf("Data di arrivo:		%s	", mete_visite->mete_visite[count].arrivo);
		printf("Ora di arrivo:	  	%s \n", mete_visite->mete_visite[count].ingresso);
		printf("Data di partenza:	%s	", mete_visite->mete_visite[count].partenza);
		printf("Ora di partenza: 	%s \n\n", mete_visite->mete_visite[count].uscita);
		
		count++;
	}
stop:
	mysql_stmt_free_result(select_dest_time);
	mysql_stmt_reset(select_dest_time);
	free(mete_visite);
};


extern struct mappe *get_mappe (char* nml)
{
	MYSQL_BIND param[4];

	struct mappe *mappe = NULL;
	int status;
	int cmpr;
	char *buff = "select_dvr_map";

	char citta[VARCHAR_LEN];
	char dettaglio[VARCHAR_LEN];
	char zona[VARCHAR_LEN];
	char immagine[VARCHAR_LEN];	

	size_t rows, count;
	count = 0;

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, nml, strlen(nml));

	bind_exe(select_dvr_map, param, buff);
	rows = take_rows(select_dvr_map, buff);
	if(rows == -1)
		goto stop; 

	mappe = malloc((sizeof(struct mappe) + sizeof(mappe)) * rows);

	memset(mappe, 0, sizeof(*mappe) + sizeof(struct mappe) * rows);

	if (mappe == NULL)
	{
		printf("Impossibile eseguire la malloc su %s", buff);
		goto stop;
	}

	set_binding_param(&param[0], MYSQL_TYPE_VAR_STRING, citta, sizeof(citta));
	set_binding_param(&param[1], MYSQL_TYPE_VAR_STRING, dettaglio, sizeof(dettaglio));
	set_binding_param(&param[2], MYSQL_TYPE_VAR_STRING, zona, sizeof(zona));
	set_binding_param(&param[3], MYSQL_TYPE_BLOB, immagine, sizeof(immagine));
	
	
	if (mysql_stmt_bind_result(select_dvr_map, param))
	{
		printf("Procedura: %s", buff);
		print_stmt_error(select_dvr_map, "\n\n Impossibile eseguire il bind risult\n\n");
		free(mappe);
		mappe = NULL;
		goto stop;
	}

	mappe->num_mappe = rows;

	while (true)
	{
		status = mysql_stmt_fetch(select_dvr_map);
		if (status == MYSQL_NO_DATA)
		{
			printf("...\n");
			break;
		}
		if (status == 1)
		{
			print_stmt_error(select_dvr_map, "\nImpossibile eseguire fetch");
		}

		strcpy(mappe->mappe[count].citta, citta);
		strcpy(mappe->mappe[count].dettaglio, dettaglio);
		strcpy(mappe->mappe[count].zona, zona);
		strcpy(mappe->mappe[count].immagine, immagine);
		
		printf("* %s *\n", mappe->mappe[count].citta);
		printf("Dettaglio:		%s 	\n", mappe->mappe[count].dettaglio);
		printf("Zona:			%s 	\n", mappe->mappe[count].zona);
		printf("Immagine:		%s 	\n\n", mappe->mappe[count].immagine);
		
		count++;
	}
stop:
	mysql_stmt_free_result(select_dvr_map);
	mysql_stmt_reset(select_dvr_map);
	free(mappe);
}
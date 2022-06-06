
#include <stdio.h>
#include "hostess.h"
#include "ins.h"
#include "upd.h"
#include "../utils/io.h"
#include "../utils/validation.h"

int get_hstss_action(void)
{
	char options[7] = {'1','2','3','4','5','6','7'};
	char op;
			
	clear_screen();
	puts("*********************************");
	puts("*   INTERFACCIA HOSTESS    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consultare prenotazioni");
	puts("2) Inserire un nuovo cliente");
	puts("3) Inserire una nuova prenotazione");
	puts("4) Modifica posti disponibili per un viaggio");
	puts("5) Conferma prenotazione ed intestazione posti");
	puts("6) Modificare la data di invio ultimi documenti di un cliente"); 
	puts("7) Esci");
	


	op = multi_choice("Select an option", options, 6);
	return op - '1';
}

bool exe_hstss_act(hstss_act sel)
{	struct cliente *cliente; 
	struct prenotazione *prenotazione;
	switch (sel)
		{case INSERT_CLIENTE:
		{
		ins_costumer(cliente); 
		return true ; 
		}
		
		case INSERT_PRENOTAZIONE:{
		ins_prenotation(prenotazione); 
		return true;
		}
     	
     	case POSTI_VIAGGIO:{
     	struct  viaggio *viaggio; 
     	mod_trip_seat(viaggio);
		return true; 
		 }

	 	case CONFERMA_PRENOTAZIONE:		{
		validate_prenotation (prenotazione); 
		return true;
		 }

		case UPDATE_DATA_DOC:		{
		update_d_doc(cliente);
		return true;
		}
		
		case QUIT:
		// gestire l'uscita dal Db (disconnessione e ritorno a schermata iniziale) 
		return false; 
		
	break;
		default:
			fprintf(stderr, "Il carattere digitato non corrisponde a nessuna azione \n");
			exit(EXIT_FAILURE);
	}

	return true;
}

void show_prenotation_details(struct prenotazione *prenotazione ) // Procedura visualizzazione dettagli prenotazione
{	
	clear_screen(); 
	char buffer[VARCHAR_LEN]; 
	 get_input("Inserisci il numero di prenotazione : ", VARCHAR_LEN, buffer, false);
	 do_select_reservation(prenotazione); 
 	clear_screen(); 
 	printf("** Dettagli prenotazione **");
 	printf("Penotazione numero: %s  E-mail cliente: %s \n Data di prenotazione: %s \n Data di conferma: %s \n Data Saldo: %s \n",
		prenotazione->numerodiprenotazione, 
		prenotazione->clienteprenotante,
		prenotazione->datadiprenotazione, 
		prenotazione->datadiconferma, 
		prenotazione->datasaldo); 
}

void mod_trip_seat(struct  viaggio *viaggio) // Procedura modifica posti dipsonibili per viaggio 
{
	clear_screen(); 
	char buffer[VARCHAR_LEN]; 
 	get_input("Inserisci il codice del viaggio : ", VARCHAR_LEN, buffer, false);
 	//procedura select viaggio
 	clear_screen(); 
 	printf("**  Dettagli Viaggio "); 
 	printf("Tour : %s \n Posti disponibili: %s \n Data annullamento: %s \n ",
 		viaggio->tourassociato, 
		viaggio->postidisponibili, 
 		viaggio->datadiannullamento); 
 	get_input ("Inserisci i nuovi posti disponibili :", NUM_LEN , viaggio->postidisponibili, false); 

}

void validate_prenotation(struct prenotazione *prenotazione)
{
	clear_screen();
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura conferma prenotazione **\n\n");
	get_input("Inserisci numero d'interesse : ", VARCHAR_LEN , buffer, false); 
    // procedura di select
	printf("Numero:  %s \n  E-mail cliente: %s \n Data di prenotazione: %s \n Data di conferma: %s \n Data di saldo: %s \n  ", 
		prenotazione->numerodiprenotazione,
		prenotazione->clienteprenotante,
		prenotazione->datadiprenotazione,
		prenotazione->datadiconferma,
		prenotazione->datasaldo
		);
 	bool answer_update = yes_or_no("\n\n Vuoi confermare questa prenotazione? (s/n) ",'s','n',false,false);
	if(!answer_update) {
		return;
		}
	while(true){
		get_input("Modifica data di conferma [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datadiconferma, false);
		if(validate_date(prenotazione->datadiconferma))
			break;
		fprintf(stderr, "Data errata!\n");
		}
	while(true){
		get_input("Modifica data di saldo [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datasaldo, false);
		if(validate_date(prenotazione->datasaldo))
			break;
		fprintf(stderr, "Data errata!\n");
		}
}

void update_d_doc(struct cliente  *cliente)
{
	clear_screen();
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura di modifica data documenti cliente **\n\n");
	get_input("Inserisci l'ID d'interesse : ", VARCHAR_LEN , buffer, false); 
    // procedura di select
	printf("E-mail:  %s \n Nome: %s \n Cognome: %s \n Indirizzo: %s \n Codice fiscale: %s \n Recapito telefonico: %s \n Fax: %s \n Data documentazione: %s \n", 
		cliente->emailcliente,
		cliente->nomecliente,
		cliente->cognomecliente,
		cliente->indirizzocliente,
		cliente->codicefiscale,
		cliente->recapitotelefonico,
		cliente->fax,
		cliente->datadocumentazione
		);
    bool answer_update = yes_or_no("\n\n Vuoi modificare la data documentazione di questo cliente? (s/n) ",'s','n',false,false);
	if(!answer_update) {
		return;
	}
	while(true){
		get_input("Modifica l'ultima data d'invio dei documuenti [YYYY-DD-MM]: ", DATE_LEN, cliente->datadocumentazione, false);
		if(validate_date(cliente->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}

}

void run_hstss_interface (void)
{ 	hstss_act sel; 
	while (true){
	get_hstss_action(); 
	if (!exe_hstss_act(sel))
		break; 
	
	}
}	



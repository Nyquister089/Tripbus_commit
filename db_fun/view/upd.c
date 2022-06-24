#include<stdio.h>
#include<stdlib.h>

#include "upd.h"
/*
void update_trip(struct viaggio *viaggio)
{	clear_screen();
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura di update viaggio **\n\n");
	get_input("Inserisci l'ID d'interesse : ", VARCHAR_LEN , buffer, false); 
    // procedura di select
    printf("ID  %s \n : Tour associato: %s \n Conducente: %s \n Accompagnatrice: %s \n Mezzo: %s \n Partenza: %s \n Ritorno: %s \n Costo : %s \n Numero Km : %s \n Posti: %s \n  ", 
		viaggio->idviaggio,
		viaggio->tourassociato,
		viaggio->conducente,
		viaggio->accompagnatrice,
		viaggio->mezzoimpiegato,
		viaggio->datadipartenzaviaggio,
		viaggio->datadiritornoviaggio,
		viaggio->costodelviaggio, 
		viaggio->numerodikm,
		viaggio->postidisponibili
		);
    bool answer_update = yes_or_no("\n\n Vuoi modificare questo viaggio? (s/n) ",'s','n',false,false);
	if(! answer_update){
		return; 
	}
		get_input("Modifica l'ID: ", VARCHAR_LEN, viaggio->idviaggio, false); // ID è autoincrement, quindi non va inserito?
		get_input("Modifica il tour a cui è associato: ", VARCHAR_LEN, viaggio->tourassociato, false);
		get_input("Modifica l'ID del conducente assegnato: ", VARCHAR_LEN, viaggio->conducente, false);
		get_input("Modifica l'ID dell'eventuale accompagnatrice: ", VARCHAR_LEN, viaggio->accompagnatrice, false);
		get_input("Modifica la targa del mezzo impiegato: ", VARCHAR_LEN, viaggio->mezzoimpiegato, false);
	while(true) {
		get_input("Modifica la data di partenza [YYYY-MM-DD]: ", DATE_LEN, 	viaggio->datadipartenzaviaggio, false);
		if(validate_date(viaggio->datadipartenzaviaggio))
			break;
		fprintf(stderr, "Data Errata!\n");
		}

	while(true) {
		get_input("Modifica la data di ritorno [YYYY-MM-DD]: ", DATE_LEN, viaggio->datadiritornoviaggio, false);
		if(validate_date(viaggio->datadiritornoviaggio))
			break;
		fprintf(stderr, "Data Errata!\n");
		}

	
	get_input("Modifica il prezzo: ", DEC_LEN, viaggio->costodelviaggio, false);
	get_input("Modifica il numero di Km che verranno percorsi: ", VARCHAR_LEN, viaggio->numerodikm, false);
	get_input("Modifica i posti disponibili totali: ", VARCHAR_LEN, viaggio->postidisponibili, false);
	// esegui gli update gestione campi vuoti
	
	
}



void update_costumer(struct cliente *cliente)
{	clear_screen();
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura di update cliente **\n\n");
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
    bool answer_update = yes_or_no("\n\n Vuoi modificare questo cliente? (s/n) ",'s','n',false,false);
	if(! answer_update){
		return; 
	}

	get_input("Modifica l'indirizzo e-mail: ", VARCHAR_LEN, cliente->emailcliente, false);
	get_input("Modifica il nome: ", VARCHAR_LEN, cliente->nomecliente, false);
	get_input("Modifica il cognome: ", VARCHAR_LEN, cliente->cognomecliente, false);
	get_input("Modifica l'indirizzo: ", VARCHAR_LEN, cliente->indirizzocliente, false);
	get_input("Modifica il codice fiscale: ", VARCHAR_LEN, cliente->codicefiscale, false);
	get_input("Modifica il recapito telefonico: ", VARCHAR_LEN, cliente->recapitotelefonico, false);
	get_input("Modifica il numero di fax: ", VARCHAR_LEN, cliente->fax, false);
	while(true){
		get_input("Modifica l'ultima data d'invio dei documuenti [YYYY-DD-MM]: ", DATE_LEN, cliente->datadocumentazione, false);
		if(validate_date(cliente->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
}

void update_prenotation(struct prenotazione *prenotazione)
{	clear_screen();
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura di update prenotazione **\n\n");
	get_input("Inserisci numero d'interesse : ", VARCHAR_LEN , buffer, false); 
    // procedura di select
	printf("Numero:  %s \n  E-mail cliente: %s \n Data di prenotazione: %s \n Data di conferma: %s \n Data di saldo: %s \n  ", 
		prenotazione->numerodiprenotazione,
		prenotazione->clienteprenotante,
		prenotazione->datadiprenotazione,
		prenotazione->datadiconferma,
		prenotazione->datasaldo
		);
    bool answer_update = yes_or_no("\n\n Vuoi modificare questa prenotazione? (s/n) ",'s','n',false,false);
	if(! answer_update){
		return; 
	}
	get_input("Modifica il numero di prenotazione: ", VARCHAR_LEN, prenotazione->numerodiprenotazione, false);/////Autoincrement
	get_input("Modifica l'indirizzo e-mail del cliente che ha effettuato la prenotazione : ", VARCHAR_LEN, prenotazione->clienteprenotante, false);
	while(true){
		get_input("Modifica data [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datadiprenotazione, false);
		if(validate_date(prenotazione->datadiprenotazione))
			break;
		fprintf(stderr, "Data errata!\n");
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
	
}*/



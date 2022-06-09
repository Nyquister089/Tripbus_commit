#include <string.h>
#include "ins.h"


void ins_prenotation(struct prenotazione *prenotazione)
{	//clear_scren();
	printf("** Dettagli inserimento prenotazione **\n\n");
	get_input("Inserisci l'indirizzo e-mail del cliente che ha effettuato la prenotazione : ", VARCHAR_LEN, prenotazione->clienteprenotante, false);
	while(true){
		get_input("Inserisci data [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datadiprenotazione, false);
		if(validate_date(prenotazione->datadiprenotazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci data di conferma [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datadiconferma, false);
		if(validate_date(prenotazione->datadiconferma))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci data di saldo [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datasaldo, false);
		if(validate_date(prenotazione->datasaldo))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	do_insert_reservation(prenotazione); 
}

void ins_seat(struct postoprenotato *postoprenotato)
{	//clear_scren();
	printf("** Dettagli inserimento passeggero **\n\n");
	get_input("Inserisci il numero di posto  : ", NUM_LEN, postoprenotato->numerodiposto, false);
	get_input("Inserisci l'ID del viaggio a cui partecipera' il passeggero: ", NUM_LEN, postoprenotato->viaggioassociato, false);
	get_input("Inserisci l'eta': ", NUM_LEN, postoprenotato-> etapasseggero, false);
	get_input("Inserisci il nome: ", VARCHAR_LEN, postoprenotato-> nomepasseggero, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, postoprenotato-> cognomepasseggero, false);
	do_insert_seat(postoprenotato); 
}

void ins_review(struct revisione *revisione)
{	//clear_scren();
	printf("** Dettagli inserimento revisione **\n\n");
	get_input("Inserisci l'ID del mezzo revisionato : ", NUM_LEN, revisione->mezzorevisionato, false);
	get_input("Inserisci l'ID del meccanico che ha eseguito la revisione : ", NUM_LEN, revisione-> addettoallarevisione, false);
	get_input("Inserisci la descrizione delle operazioni eseguite (massimo 5000 caratteri): ", DES_LEN, revisione-> operazionieseguite, false);
	get_input("Inserisci il numero di km presenti sul conta chilometri del mezzo revisionato : ", VARCHAR_LEN, revisione-> chilometraggio, false);
	get_input("Inserisci la tipologia(ordinaria o straordinaria) : ", VARCHAR_LEN, revisione-> tipologiarevisione, false);
	if(strcmp(revisione->tipologiarevisione,"straordinaria") == 0)
		get_input("Inserisci la motivazione della revisione straordinaria (massimo 5000 caratteri) : ", DES_LEN, revisione-> motivazione, false);
	while(true){
		get_input("Inserisci la data di inizio[YYYY-DD-MM]: ", DATE_LEN, revisione->datainizio, false);
		if(validate_date(revisione->datainizio))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci la data di conclusione[YYYY-DD-MM]: ", DATE_LEN, revisione->datafine, false);
		if(validate_date(revisione->datafine))
			break;
		fprintf(stderr, "Data errata!\n");
	}


}

void ins_costumer(struct cliente *cliente)
{	//clear_scren();
	printf("** Dettagli inserimento cliente **\n\n");
	get_input("Inserisci l'indirizzo e-mail: ", VARCHAR_LEN, cliente->emailcliente, false);
	get_input("Inserisci il nome: ", VARCHAR_LEN, cliente->nomecliente, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, cliente->cognomecliente, false);
	get_input("Inserisci l'indirizzo: ", VARCHAR_LEN, cliente->indirizzocliente, false);
	get_input("Inserisci il codice fiscale: ", VARCHAR_LEN, cliente->codicefiscale, false);
	get_input("Inserisci il recapito telefonico: ", NUM_LEN, cliente->recapitotelefonico, false);
	get_input("Inserisci il numero di fax: ", NUM_LEN, cliente->fax, false);
	/*
	while(true) {
		get_input("Insert day [YYYY-MM-DD]: ", DATE_LEN, flight-> giorno, false);
		if(validate_date(flight->giorno))
			break;
		fprintf(stderr, "Invalid date!\n");
	}*/
	get_input("Inserisci l'ultima data d'invio dei documuenti [YYYY-DD-MM]: ", DATE_LEN, cliente->datadocumentazione, false);
	/*	
	while(true){
		get_input("Inserisci l'ultima data d'invio dei documuenti [YYYY-DD-MM]: ", DATE_LEN, cliente->datadocumentazione, false);
		if(validate_date(cliente->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}*/
	do_insert_costumer(cliente); 
}

void ins_sparepart(struct ricambio *ricambio)
{	
	//clear_scren();
	printf("** Dettagli inserimento ricambio **\n\n");
	get_input("Inserisci il codice: ", VARCHAR_LEN, ricambio->codice, false);
	get_input("Inserisci il costo unitario: ", DEC_LEN, ricambio->costounitario, false);
	get_input("Inserisci la quantita' minima: ", NUM_LEN, ricambio->quantitadiriordino, false);
	get_input("Inserisci la descrizione (massimo 5000 caratteri) : ", DES_LEN, ricambio-> descrizione, false);
	get_input("Inserisci la scorta minima: ", NUM_LEN, ricambio-> scortaminima, false);
	get_input("Inserisci quantita' di pezzi disponili: ", NUM_LEN, ricambio-> quantitainmagazzino, false);
}

void ins_bus(struct mezzo *mezzo)
{	//clear_scren();
	printf("** Dettagli inserimento mezzo **\n\n");
	get_input("Inserisci la targa : ", VARCHAR_LEN, mezzo->targa, false);
	get_input("Inserisci l'ID del modello : ", NUM_LEN, mezzo->modellomezzo, false);
	get_input("Inserisci gli ingombri : ", VARCHAR_LEN, mezzo->ingombri, false);
	get_input("Inserisci l'autonomia : ", NUM_LEN, mezzo-> autonomia, false);
	get_input("Inserisci il valore attuale del conta chilometri: ", NUM_LEN, mezzo-> valorecontakm, false);
		while(true){
		get_input("Inserisci la data dell'ultima revisione presso la motorizzazione [YYYY-DD-MM]: ", DATE_LEN, mezzo->dataultimarevisioneinmotorizzazione, false);
		if(validate_date(mezzo->dataultimarevisioneinmotorizzazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci la data di immatricolazione  [YYYY-DD-MM]: ", DATE_LEN, mezzo->dataimmatricolazione, false);
		if(validate_date(mezzo->dataimmatricolazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
}

void ins_model(struct modello *modello)
{	//clear_scren();
	printf("** Dettagli inserimento modello **\n\n");
	get_input("Inserisci il nome : ", DEC_LEN, modello->nomemodello, false);
	get_input("Inserisci la casa costruttrice : ", NUM_LEN, modello->casacostruttrice, false);
	get_input("Inserisci i dati tecnici (massimo 5000 caratteri) : ", DES_LEN, modello-> datitecnici, false);
	get_input("Inserisci il numero di posti: ", NUM_LEN, modello-> numeroposti, false);
}

void ins_certify(struct tagliando *tagliando)
{	//clear_scren();
	printf("** Dettagli inserimento tagliando **\n\n");
	get_input("Inserisci la tipologia del tagliando: ", VARCHAR_LEN, tagliando->tipologiatagliando, false);
	get_input("Inserisci le validita' superate (massimo 5000 caratteri) : ", DES_LEN, tagliando->validitasuperate, false);
}

void ins_association(struct associata *associata)
{//clear_scren();
	printf("** Dettagli associazione camera**\n\n");
	get_input("Inserisci il numero della camera : ", NUM_LEN, associata->cameraprenotata, false);
	get_input("Inserisci il nome dell'ospite: ", VARCHAR_LEN, associata->ospite, false);
	get_input("Inserisci l'albergo in cui è ubicata la camera  : ", NUM_LEN, associata->albergoinquestione, false);	
	do_insert_assoc(associata); 
}

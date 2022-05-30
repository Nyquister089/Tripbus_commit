#include<stdio.h>
#include<stdlib.h>

#include "upd.h"

char BUFFER[VARCHAR_LEN]; 
char ID_RSRC[NUM_LEN]; 
bool ANS; 

void update_tour(struct tour *tour)
{	clear_screen();
	printf("** Procedura di update tour **\n\n");
    get_input("Inserisci la denominazione del tour da modificare : ", VARCHAR_LEN, BUFFER, false); 
    // procedura di select
    printf("Denominazione %s \n : Descrizione : %s \n Numero minimo di partecipanti: %s \n Costo dell'assicurazione: %s \n Costo del bagaglio: %s \n Indicazione sulla presenza di un'accompagnatrice: %s \n  ", 
		tour->denominazionetour,
		tour->descrizionetour,
		tour->minimopartecipanti,
		tour->assicurazionemedica,
		tour->bagaglio,
		tour->accompagnatrice
		);
    
	bool answer_update = yes_or_no("\n\n Vuoi modificare questo tour? (s/n) ",'s','n',false,false);
	if(!answer_update) {
		return;
	}
	
	get_input("Modifica la denominazione: ", VARCHAR_LEN, tour->denominazionetour, false);
	get_input("Modifica la descrizione (massimo 5000 caratteri): ", DES_LEN, tour->descrizionetour, false);
	
	do{
		get_input("Modifica il numero minimo di partecipanti: ", NUM_LEN, tour->minimopartecipanti, false);
	}while(!validate_integer(tour->minimopartecipanti));

	do{
		get_input("Modifica il costo dell'assicurazione: ", DEC_LEN, tour->assicurazionemedica, false);
	}while(!validate_integer(tour->assicurazionemedica));

	do{
		get_input("Modifica il costo del bagaglio: ", DEC_LEN, tour->bagaglio, false);
	}while(!validate_integer(tour->bagaglio));

	get_input("Modifica l'indicazione sulla presenza di un'accompagnatrice: ", VARCHAR_LEN, tour->accompagnatrice, false);
	//esegui update gestione campi vuoti
}

void update_destination(struct meta *meta)
{	clear_screen();
	printf("** Procedura di update meta **\n\n");
	get_input("Inserisci l'ID  : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
    printf("ID  %s \n : Nome: %s \n E-mail: %s \n Recapito telefonico: %s \n Fax: %s \n Indirizzo: %s \n Tipologia: %s \n Categoria albergo : %s \n Orario di apertura : %s \n Località di appartenenza : %s \n  ", 
		meta->idmeta,
		meta->nomemeta,
		meta->emailmeta,
		meta->telefonometa,
		meta->faxmeta,
		meta->indirizzo,
		meta->tipologiameta,
		meta->categoriaalbergo, 
		meta->orariodiapertura,
		meta->localitadiappartenenza
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa meta? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{get_input("Modifica l'ID: ", NUM_LEN, meta->idmeta, false);   /// AUTOINCREMENT
		get_input("Modifica il nome: ", VARCHAR_LEN, meta->nomemeta, false);
		get_input("Modifica l'indirizzo e-mail: ", VARCHAR_LEN, meta->emailmeta, false);
		get_input("Modifica il numero di telefono: ", NUM_LEN, meta->telefonometa, false);
		get_input("Modifica il numero di fax: ", NUM_LEN, meta->faxmeta, false);
		get_input("Modifica l'indirizzo: ", VARCHAR_LEN, meta->indirizzo, false);
		get_input("Modifica la tipologia (bene o albergo ):" , VARCHAR_LEN, meta->tipologiameta, false);
		if(strcmp(meta->tipologiameta, "albergo") == 0)
			get_input("Modifica la categoria dell'albergo: ", VARCHAR_LEN, meta->categoriaalbergo, false);
		else
			while(true) {
				get_input("Modifica l'orario di apertura del bene [HH:MM]: ", TIME_LEN, meta->orariodiapertura, false);
		if(validate_time(meta->orariodiapertura))
			break;
		}

		get_input("Modifica la localita di appartenenza: ", VARCHAR_LEN, meta->localitadiappartenenza, false);
		// esegui gli update gestione campi vuoti
	}
	else 
	{
		//ritorna al menù
	}
}

void update_trip(struct viaggio *viaggio)
{	clear_screen();
	printf("** Procedura di update viaggio **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
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
    ANS = yes_or_no("\n\n Vuoi modificare questo viaggio? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{get_input("Modifica l'ID: ", NUM_LEN, viaggio->idviaggio, false); // ID è autoincrement, quindi non va inserito?
		get_input("Modifica il tour a cui è associato: ", VARCHAR_LEN, viaggio->tourassociato, false);
		get_input("Modifica l'ID del conducente assegnato: ", NUM_LEN, viaggio->conducente, false);
		get_input("Modifica l'ID dell'eventuale accompagnatrice: ", NUM_LEN, viaggio->accompagnatrice, false);
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
	get_input("Modifica il numero di Km che verranno percorsi: ", NUM_LEN, viaggio->numerodikm, false);
	get_input("Modifica i posti disponibili totali: ", NUM_LEN, viaggio->postidisponibili, false);
	// esegui gli update gestione campi vuoti
	}
	else
	{
		//ritorna al menù
	}
}

void update_visit(struct visita *visita)
{	clear_screen();
	printf("** Procedura di update  visita **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("ID:  %s \n  Viaggio: %s \n Meta: %s \n Data di arrivo: %s \n Ora di arrivo: %s \n Data di partenza: %s \n Ora di partenza: %s \n Guida: %s \n Suppplemento: %s \n Trattamento alberghiero: %s \n  ", 
		visita->idvisita,
		visita->viaggiorelativo,
		visita->metavisitata,
		visita->datadiarrivo,
		visita->oradiarrivo,
		visita->datadipartenza,
		visita->oradipartenza,
		visita->guida,
		visita->supplemento,
		visita->trattamentoalberghiero
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa visita? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{get_input("Modifica l'ID: ", NUM_LEN, visita->idvisita, false); // ID è autoincrement, quindi non va inserito?
		get_input("Modifica l'ID del viaggio associato: ", NUM_LEN, visita->viaggiorelativo, false);
		get_input("Modifica l'ID della meta visitata: ", NUM_LEN, visita->metavisitata, false);
		while(true) {
			get_input("Modifica la data di arrivo prevista [YYYY-MM-DD]: ", DATE_LEN, visita->datadiarrivo, false);
			if(validate_date(visita->datadiarrivo))
				break;
			fprintf(stderr,"Data errata!"); 
		}
		while(true) {
			get_input("Modifica la data di partenza prevista [YYYY-MM-DD]: ", DATE_LEN, visita->datadipartenza, false);
			if(validate_date(visita->datadipartenza))
				break;
			fprintf(stderr,"Data errata!");	
		}
	while(true) {
			get_input("Modifica l'orario di arrivo previsto [HH:MM]", TIME_LEN, visita->oradiarrivo, false);
		if(validate_time(visita->oradiarrivo))
			break;
		fprintf(stderr,"Orario errato!");	
		}
	while(true) {
			get_input("Modifica l'orario di partenza previsto [HH:MM]", TIME_LEN, visita->oradipartenza, false);
		if(validate_time(visita->oradipartenza))
			break;
		fprintf(stderr,"Orario errato!");
		}

		get_input("Modifica l'indicazione sulla presenza della guida(si/no): ", BIT_LEN, visita->guida, false);
		get_input("Modifica l'importo dell'eventuale supplemento: ", DEC_LEN, visita->supplemento, false);
		get_input("Modifica la descrizione dell'eventuale trattamento alberghiero (massimo 5000 caratteri)", DES_LEN, visita->trattamentoalberghiero, false);
		// esegui gli update gestione campi vuoti
	}
	else
	{
		//ritorna al menù
	}
		 
}

void update_picture(struct documentazionefotografica *documentazionefotografica) 
{	clear_screen();
	printf("** Procedura di update foto **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("ID:  %s \n  Foto: %s \n ", 
		documentazionefotografica->idfoto,
		documentazionefotografica->foto
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa foto? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{get_input("Modifica l'ID : ", NUM_LEN, documentazionefotografica->idfoto, false); // ID è autoincrement, quindi non va inserito?
		get_input("Modifica l'immagine: ", PIC, documentazionefotografica->foto, false);
		}
	else
		{
		//ritorna al menù
		}
}


void update_employee(struct dipendente *dipendente)
{	clear_screen();
	printf("** Procedura di update  dipendente **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("ID:  %s \n  Nome: %s \n Cognome: %s \n Tipologia: %s \n Telefono aziendale : %s \n  ", 
		dipendente->iddipendente,
		dipendente->nomedipendente,
		dipendente->cognomedipendente,
		dipendente->tipologiadipendente,
		dipendente->telefonoaziendale
		);
    ANS = yes_or_no("\n\n Vuoi modificare questo dipendente? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica l'ID: ", NUM_LEN, dipendente->iddipendente, false); // ID è autoincrement, quindi non va inserito?
	get_input("Modifica il nome: ", VARCHAR_LEN, dipendente->nomedipendente, false);
	get_input("Modifica il cognome: ", VARCHAR_LEN, dipendente->cognomedipendente, false);
	get_input("Modifica la tipolgia (Autista, Hostess o Meccanico): ", BIT_LEN, dipendente->tipologiadipendente, false);
	get_input("Modifica il numero di telefono aziendale: ", NUM_LEN,  dipendente->telefonoaziendale, false); 
		}
	else
		{
		//ritorna al menù
		}
}

void update_room(struct camera *camera)
{	clear_screen();
	printf("** Procedura di update  camera di albergo **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("Numero:  %s \n  Albergo: %s \n  Tipologia: %s \n Costo: %s \n", 
		camera->numerocamera,
		camera->albergo,
		camera->tipologia,
		camera->costo
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa camera? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica il numero della camera : ", NUM_LEN, camera->numerocamera, false);
	get_input("Modifica l'ID dell'albergo in cui la camera è ubicata : ", NUM_LEN, camera->albergo, false);
	get_input("Modifica la tipologia: ", VARCHAR_LEN, camera->tipologia, false);
	get_input("Modifica il prezzo giornaliero del soggiorno: ", DEC_LEN, camera->costo, false);
		}
	else
		{
		//ritorna al menù
		}
}

void update_location(struct localita *localita)
{	clear_screen();
	printf("** Procedura di update  localita **\n\n");
	get_input("Inserisci il nome d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("Nome %s \n  Regione: %s \n Stato: %s \n", 
		localita->nomelocalita,
		localita->regione,
		localita->stato
		
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa localita? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica il nome: ", VARCHAR_LEN, localita->nomelocalita, false);
	get_input("Modifica ll nome della regione: ", VARCHAR_LEN, localita->regione, false);
	get_input("Modifica il nome dello stato: ", VARCHAR_LEN, localita->stato, false);
		}
	else
		{
		//ritorna al menù
		}
}

void update_map(struct mappa *mappa)
{	clear_screen();
	printf("** Procedura di update  mappa **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("ID:  %s \n  Città: %s \n Livello di dettaglio: %s \n Zona: %s \n Localita' rappresentata: %s \n ", 
		mappa->idmappa,
		mappa->citta,
		mappa->livellodidettaglio,
		mappa->zona,
		mappa->localitarappresentata
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa mappa? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
		get_input("Modifica l'ID: ", NUM_LEN, mappa->idmappa, false); //Autoincrement ???
		get_input("Modifica il nome della città rappresentata nella mappa: ", VARCHAR_LEN, mappa->citta, false);
		get_input("Modifica il livello di dettaglio: ", VARCHAR_LEN, mappa->livellodidettaglio, false);
		get_input("Modifica il nome della zona rappresentata dalla mappa: ", VARCHAR_LEN, mappa->zona, false);
		get_input("Modifica il nome della localita' in cui è ubicata la citta' rappresentata: ", VARCHAR_LEN, mappa->localitarappresentata, false);
		}
	else
		{
		//ritorna al menù
		}
}

void update_costumer(struct cliente *cliente)
{	clear_screen();
	printf("** Procedura di update cliente **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
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
    ANS = yes_or_no("\n\n Vuoi modificare questo cliente? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica l'indirizzo e-mail: ", VARCHAR_LEN, cliente->emailcliente, false);
	get_input("Modifica il nome: ", VARCHAR_LEN, cliente->nomecliente, false);
	get_input("Modifica il cognome: ", VARCHAR_LEN, cliente->cognomecliente, false);
	get_input("Modifica l'indirizzo: ", VARCHAR_LEN, cliente->indirizzocliente, false);
	get_input("Modifica il codice fiscale: ", VARCHAR_LEN, cliente->codicefiscale, false);
	get_input("Modifica il recapito telefonico: ", NUM_LEN, cliente->recapitotelefonico, false);
	get_input("Modifica il numero di fax: ", NUM_LEN, cliente->fax, false);
	while(true){
		get_input("Modifica l'ultima data d'invio dei documuenti [YYYY-DD-MM]: ", DATE_LEN, cliente->datadocumentazione, false);
		if(validate_date(cliente->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
		}
	else
		{
		//ritorna al menù
		}
}

void update_prenotation(struct prenotazione *prenotazione)
{	clear_screen();
	printf("** Procedura di update prenotazione **\n\n");
	get_input("Inserisci numero d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("Numero:  %s \n  E-mail cliente: %s \n Data di prenotazione: %s \n Data di conferma: %s \n Data di saldo: %s \n  ", 
		prenotazione->numerodiprenotazione,
		prenotazione->clienteprenotante,
		prenotazione->datadiprenotazione,
		prenotazione->datadiconferma,
		prenotazione->datasaldo
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa prenotazione? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica il numero di prenotazione: ", NUM_LEN, prenotazione->numerodiprenotazione, false);/////Autoincrement
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
		}
	else
		{
		//ritorna al menù
		}
}

void update_seat(struct postoprenotato *postoprenotato)
{	clear_screen();
	printf("** Procedura di update passeggero **\n\n");
	get_input("Inserisci l'ID del viaggio d'interesse : ", NUM_LEN , ID_RSRC, false); 
	get_input("Inserisci il numero di posto d'interesse : ", NUM_LEN , ID_RSRC, false);

    // procedura di select
	printf("Numero di posto:  %s \n  Viaggio: %s \n Età passeggero : %s \n Nome: %s \n Cognome: %s \n  ", 
		postoprenotato->numerodiposto,
		postoprenotato->viaggioassociato,
		postoprenotato->etapasseggero,
		postoprenotato->nomepasseggero,
		postoprenotato->cognomepasseggero
		);
    ANS = yes_or_no("\n\n Vuoi modificare questo posto prenotato? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica il numero di posto  : ", NUM_LEN, postoprenotato->numerodiposto, false);
	get_input("Modifica l'ID del viaggio a cui parteciperà il passeggero: ", NUM_LEN, postoprenotato->viaggioassociato, false);
	get_input("Modifica l'età: ", NUM_LEN, postoprenotato-> etapasseggero, false);
	get_input("Modifica il nome: ", VARCHAR_LEN, postoprenotato-> nomepasseggero, false);
	get_input("Modifica il cognome: ", VARCHAR_LEN, postoprenotato-> cognomepasseggero, false);
		}
	else
		{
		//ritorna al menù
		}
}

void update_review(struct revisione *revisione) 
{	clear_screen();
	printf("** Procedura di update revisione **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("ID:  %s \n  Mezzo: %s \n Addetto alla revisione : %s \n Operazioni eseguite: %s \n Chilometraggio mezzo: %s \n Tipologia: %s \n Data inizio: %s \n Data fine: %s \n ", 
		revisione->idrevisione,
		revisione->mezzorevisionato,
		revisione->addettoallarevisione,
		revisione->operazionieseguite,
		revisione->chilometraggio,
		revisione->tipologiarevisione,
		revisione->datainizio,
		revisione->datafine
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa revisione? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica l'ID: ", NUM_LEN, revisione->idrevisione, false);
	get_input("Modifica l'ID del mezzo revisionato : ", NUM_LEN, revisione->mezzorevisionato, false);
	get_input("Modifica l'ID del meccanico che ha eseguito la revisione : ", NUM_LEN, revisione-> addettoallarevisione, false);
	get_input("Modifica la descrizione delle operazioni eseguite (massimo 5000 caratteri): ", DES_LEN, revisione-> operazionieseguite, false);
	get_input("Modifica il numero di km presenti sul conta chilometri del mezzo revisionato : ", VARCHAR_LEN, revisione-> chilometraggio, false);
	get_input("Modifica la tipologia(ordinaria o straordinaria) : ", VARCHAR_LEN, revisione-> tipologiarevisione, false);
	if(strcmp(revisione->tipologiarevisione,"straordinaria") == 0)
		get_input("Modifica la motivazione della revisione straordinaria (massimo 5000 caratteri) : ", DES_LEN, revisione-> motivazione, false);
	while(true){
		get_input("Modifica la data di inizio[YYYY-DD-MM]: ", DATE_LEN, revisione->datainizio, false);
		if(validate_date(revisione->datainizio))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Modifica la data di conclusione[YYYY-DD-MM]: ", DATE_LEN, revisione->datafine, false);
		if(validate_date(revisione->datafine))
			break;
		fprintf(stderr, "Data errata!\n");
	}
		}
	else
		{
		//ritorna al menù
		}

}

void update_sparepart(struct ricambio *ricambio)
{	clear_screen();
	printf("** Procedura di update ricambio **\n\n");
	get_input("Inserisci il codice d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf(" Codice:  %s \n  Costo : %s \n Quantità di riordino: %s \n Descrizione: %s \n Scorta minima: %s \n Quantità in magazzino: %s \n  ", 
		ricambio->codice,
		ricambio->costounitario,
		ricambio->quantitadiriordino,
		ricambio->descrizione,
		ricambio->scortaminima,
		ricambio->quantitainmagazzino
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa ricambio? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica il codice: ", VARCHAR_LEN, ricambio->codice, false);
	get_input("Modifica il costo unitario: ", DEC_LEN, ricambio->costounitario, false);
	get_input("Modifica la quantità minima di riordino: ", NUM_LEN, ricambio->quantitadiriordino, false);
	get_input("Modifica la descrizione (massimo 5000 caratteri) : ", DES_LEN, ricambio-> descrizione, false);
	get_input("Modifica la scorta minima: ", NUM_LEN, ricambio-> scortaminima, false);
	get_input("Modifica quantità di pezzi disponili: ", NUM_LEN, ricambio-> quantitainmagazzino, false);
		}
	else
		{
		//ritorna al menù
		}
}

void update_bus(struct mezzo *mezzo)
{	clear_screen();
	printf("** Procedura di update mezzo **\n\n");
	get_input("Inserisci la targa d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("Traga:  %s \n  Modello: %s \n Ingombri: %s \n Autonomia: %s \n Chilometraggio: %s \n Data ultima revsione presso motorizzazione: %s \n Data immatricolazione: %s \n", 
		mezzo->targa,
		mezzo->modellomezzo,
		mezzo->ingombri,
		mezzo->autonomia,
		mezzo->valorecontakm,
		mezzo->dataultimarevisioneinmotorizzazione,
		mezzo->dataimmatricolazione
		);
    ANS = yes_or_no("\n\n Vuoi modificare questa mezzo? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica la targa : ", VARCHAR_LEN, mezzo->targa, false);
	get_input("Modifica l'ID del modello : ", NUM_LEN, mezzo->modellomezzo, false);
	get_input("Modifica gli ingombri : ", VARCHAR_LEN, mezzo->ingombri, false);
	get_input("Modifica l'autonomia : ", NUM_LEN, mezzo-> autonomia, false);
	get_input("Modifica il valore attuale del conta chilometri: ", NUM_LEN, mezzo-> valorecontakm, false);
		while(true){
		get_input("Modifica la data dell'ultima revisione presso la motorizzazione [YYYY-DD-MM]: ", DATE_LEN, mezzo->dataultimarevisioneinmotorizzazione, false);
		if(validate_date(mezzo->dataultimarevisioneinmotorizzazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Modifica la data di immatricolazione  [YYYY-DD-MM]: ", DATE_LEN, mezzo->dataimmatricolazione, false);
		if(validate_date(mezzo->dataimmatricolazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
		}
	else
		{
		//ritorna al menù
		}
}

void update_model(struct modello *modello)
{	clear_screen();
	printf("** Procedura di update modello **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("ID:  %s \n  Nome: %s \n Casa costruttrice: %s \n Descrizione: %s \n Numero di posti: %s \n", 
		modello->idmodello,
		modello->nomemodello,
		modello->casacostruttrice,
		modello->datitecnici,
		modello->numeroposti
		);
    ANS = yes_or_no("\n\n Vuoi modificare questo modello? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica l'ID : ", NUM_LEN, modello->idmodello, false); // AUTOINCREMENT???
	get_input("Modifica il nome : ", DEC_LEN, modello->nomemodello, false);
	get_input("Modifica la casa costruttrice : ", NUM_LEN, modello->casacostruttrice, false);
	get_input("Modifica i dati tecnici (massimo 5000 caratteri) : ", DES_LEN, modello-> datitecnici, false);
	get_input("Modifica il numero di posti: ", NUM_LEN, modello-> numeroposti, false);
		}
	else
		{
		//ritorna al menù
		}
}

void update_certify(struct tagliando *tagliando)
{	clear_screen();
	printf("** Procedura di update tagliando **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("ID:  %s \n  Tipologia tagliando : %s \n Validità: %s \n ", 
		tagliando->idtagliando,
		tagliando->tipologiatagliando,
		tagliando->validitasuperate
		);
    ANS = yes_or_no("\n\n Vuoi modificare questo tagliando ? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica l'ID : ", NUM_LEN, tagliando->idtagliando, false); // AUTOINCREMENT???
	get_input("Modifica la tipologia del tagliando: ", VARCHAR_LEN, tagliando->tipologiatagliando, false);
	get_input("Modifica le validità superate (massimo 5000 caratteri) : ", DES_LEN, tagliando->validitasuperate, false);
		}
	else
		{
		//ritorna al menù
		}
}

void update_comfort(struct comfort  *comfort)
{	clear_screen();
	printf("** Procedura di update comfort **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("ID:  %s \n  Nome: %s \n Descrizione: %s \n ",
		comfort->idcomfort,
		comfort->nomecomfort,
		comfort->descrizionecomfort
		);
    ANS = yes_or_no("\n\n Vuoi modificare questo comfort? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica l'ID : ", NUM_LEN, comfort->idcomfort, false); // AUTOINCREMENT???
	get_input("Modifica il nome : ", VARCHAR_LEN, comfort->nomecomfort, false);
	get_input("Modifica la descrizione (massimo 5000 caratteri) : ", DES_LEN, comfort->descrizionecomfort, false);
		}
	else
		{
		//ritorna al menù
		}
}

void update_service(struct servizio *servizio)
{	clear_screen();
	printf("** Procedura di update servizio **\n\n");
	get_input("Inserisci l'ID d'interesse : ", NUM_LEN , ID_RSRC, false); 
    // procedura di select
	printf("ID:  %s \n  Nome: %s \n Descrizione: %s \n ",
		servizio->idservizio,
		servizio->nomeservizio,
		servizio->descrizioneservizio
		);
    ANS = yes_or_no("\n\n Vuoi modificare questo servizio? (s/n) ",'s','n',false,false);
	if(ANS== true)
		{
	get_input("Modifica l'ID : ", NUM_LEN, servizio->idservizio, false); // AUTOINCREMENT???
	get_input("Modifica il nome : ", VARCHAR_LEN, servizio->nomeservizio, false);
	get_input("Modifica la descrizione (massimo 5000 caratteri) : ", DES_LEN, servizio->descrizioneservizio, false);
		}
	else
		{
		//ritorna al menù
		}
}


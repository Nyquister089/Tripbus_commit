#include <string.h>
#include "ins.h"



void ins_prenotation(struct prenotazione *prenotazione) //funziona
{
	printf("\n** Dettagli inserimento prenotazione **\n\n");
	get_input("Inserisci l'indirizzo e-mail del cliente che ha effettuato la prenotazione : ", VARCHAR_LEN, prenotazione->clienteprenotante, false);
	while(true){
		get_input("Inserisci data [YYYY-MM-DD]: ", DATE_LEN, prenotazione->datadiprenotazione, false);
		if(validate_date(prenotazione->datadiprenotazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}

	do_insert_reservation(prenotazione); 
}

void ins_seat(struct postoprenotato *postoprenotato)
{	
	char buff[NUM_LEN]; 
	printf("\n** Dettagli inserimento passeggero **\n\n");
	get_input("Inserisci il numero di posto: ", NUM_LEN, buff, false);

	postoprenotato->numerodiposto = atoi(buff); 

	get_input("Inserisci l'ID del viaggio a cui partecipera' il passeggero: ", NUM_LEN, buff, false);
	postoprenotato->viaggioassociato = atoi(buff); 
	
	get_input("Inserisci l'età: ", NUM_LEN, buff, false);
	postoprenotato->etapasseggero = atoi(buff); 

	get_input("Inserisci il nome: ", VARCHAR_LEN, postoprenotato-> nomepasseggero, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, postoprenotato-> cognomepasseggero, false);

	do_insert_seat(postoprenotato); 
}

void ins_review(struct revisione *revisione, struct sostituito *sostituito, struct ricambio *ricambio)
{	
	char buff[NUM_LEN]; 
	bool ans;
	printf("\n** Dettagli inserimento revisione **\n\n");
	get_input("Inserisci la targa del mezzo revisionato : ", VARCHAR_LEN, revisione->mezzorevisionato, false);
	get_input("Inserisci l'ID del meccanico che ha eseguito la revisione : ", NUM_LEN, buff, false);
	revisione->addettoallarevisione = atoi(buff); 
	get_input("Inserisci la descrizione delle operazioni eseguite (massimo 5000 caratteri): ", DES_LEN, revisione-> operazionieseguite, false);
	get_input("Inserisci il numero di km presenti sul conta chilometri del mezzo revisionato : ",NUM_LEN, buff, false);
	revisione-> chilometraggio = atoi(buff); 
	get_input("Inserisci la tipologia(ordinaria o straordinaria) : ", VARCHAR_LEN, revisione-> tipologiarevisione, false);
	if(strcmp(revisione->tipologiarevisione,"straordinaria") == 0)
		get_input("Inserisci la motivazione della revisione straordinaria (massimo 5000 caratteri) : ", DES_LEN, revisione-> motivazione, false);
	while(true){
		get_input("Inserisci la data di inizio[YYYY-MM-DD]: ", DATE_LEN, revisione->datainizio, false);
		if(validate_date(revisione->datainizio))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci la data di conclusione[YYYY-MM-DD]: ", DATE_LEN, revisione->datafine, false);
		if(validate_date(revisione->datafine))
			break;
		fprintf(stderr, "Data errata!\n");
	}
do_insert_review(revisione);


ans = yes_or_no("In questa revisione sono statti sostituiti dei ricambi? ",'s','n',false, false); 
if(ans)
	{	do_select_max_idreview(revisione); 
		sostituito->revisioneassociata = revisione->idrevisione; 
		
		ins_sostitution(sostituito, ricambio ); 
	}

}

void ins_costumer(struct cliente *cliente) // funziona ma smashing stack su inserimento interi3
{	
	char buff[VARCHAR_LEN]; 
	
	printf("\n** Dettagli inserimento cliente **\n\n");
	get_input("Inserisci l'indirizzo e-mail: ", VARCHAR_LEN, cliente->emailcliente, false);
	get_input("Inserisci il nome: ", VARCHAR_LEN, cliente->nomecliente, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, cliente->cognomecliente, false);
	get_input("Inserisci l'indirizzo: ", VARCHAR_LEN, cliente->indirizzocliente, false);
	get_input("Inserisci il codice fiscale: ", VARCHAR_LEN, cliente->codicefiscale, false);
	get_input("Inserisci il recapito telefonico: ", NUM_LEN, cliente->recapitotelefonico, false);
	get_input("Inserisci il numero di fax: ", NUM_LEN, cliente->fax, false);


	while(true){
		get_input("Inserisci l'ultima data d'invio dei documuenti [YYYY-MM-DD]: ", DATE_LEN, cliente->datadocumentazione, false);
		if(validate_date(cliente->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	do_insert_costumer(cliente); 
}

void ins_sparepart(struct ricambio *ricambio)
{	
	char buff[NUM_LEN]; 
	printf("\n** Dettagli inserimento ricambio **\n\n");
	get_input("Inserisci il codice: ", VARCHAR_LEN, ricambio->codice, false);
	get_input("Inserisci il costo unitario: ", NUM_LEN, buff, false);
	ricambio->costounitario = atof(buff);
	get_input("Inserisci la quantità minima di riordino : ", NUM_LEN, buff, false);
	ricambio->quantitadiriordino= atoi(buff); 
	get_input("Inserisci la descrizione (massimo 5000 caratteri) : ", DES_LEN, ricambio-> descrizione, false);
	get_input("Inserisci la scorta minima: ", NUM_LEN, buff, false);
	ricambio->scortaminima = atoi(buff); 
	get_input("Inserisci quantita' di pezzi disponibili: ", NUM_LEN, buff, false);
	ricambio->quantitainmagazzino = atoi(buff);
}

void ins_bus(struct mezzo *mezzo)
{	
	char buff[VARCHAR_LEN]; 
	printf("\n** Dettagli inserimento mezzo **\n\n");
	get_input("Inserisci la targa : ", VARCHAR_LEN, mezzo->targa, false);
	get_input("Inserisci l'ID del modello : ", VARCHAR_LEN, mezzo->modellomezzo, false);
	get_input("Inserisci gli ingombri : ", VARCHAR_LEN, mezzo->ingombri, false);
	get_input("Inserisci l'autonomia : ", NUM_LEN, buff , false);
	mezzo-> autonomia = atoi(buff); 
	get_input("Inserisci il valore attuale del conta chilometri: ", NUM_LEN, buff, false);
	mezzo-> valorecontakm = atoi(buff); 
		while(true){
		get_input("Inserisci la data dell'ultima revisione presso la motorizzazione [YYYY-MM-DD]: ", DATE_LEN, mezzo->dataultimarevisioneinmotorizzazione, false);
		if(validate_date(mezzo->dataultimarevisioneinmotorizzazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci la data di immatricolazione  [YYYY-MM-DD]: ", DATE_LEN, mezzo->dataimmatricolazione, false);
		if(validate_date(mezzo->dataimmatricolazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
}

void ins_model(struct modello *modello)
{	
	char buff[VARCHAR_LEN];
	printf("\n** Dettagli inserimento modello **\n\n");
	get_input("Inserisci il nome : ", DEC_LEN, modello->nomemodello, false);
	get_input("Inserisci la casa costruttrice : ", NUM_LEN, modello->casacostruttrice, false);
	get_input("Inserisci i dati tecnici (massimo 5000 caratteri) : ", DES_LEN, modello-> datitecnici, false);
	get_input("Inserisci il numero di posti: ", NUM_LEN, buff, false);
	modello->numeroposti = atoi(buff); 
}

void ins_certify(struct tagliando *tagliando)
{	//clear_scren();
	printf("\n** Dettagli inserimento tagliando **\n\n");
	get_input("Inserisci la tipologia del tagliando: ", VARCHAR_LEN, tagliando->tipologiatagliando, false);
	get_input("Inserisci le validita' superate (massimo 5000 caratteri) : ", DES_LEN, tagliando->validitasuperate, false);
}

void ins_association(struct associata *associata)
{	
	char buff[NUM_LEN]; 
	printf("\n** Dettagli associazione camera**\n\n");
	get_input("Inserisci il numero della camera: ", NUM_LEN, buff, false);
	associata->cameraprenotata = atoi(buff); 
	get_input("Inserisci l'albergo in cui è ubicata la camera: ", NUM_LEN, buff,false);	
	associata->albergoinquestione = atoi(buff); 
	while(true){
	get_input("Inserici la data d'inizio del soggiorno [YYYY-MM-DD]: ",DATE_LEN, associata->datainiziosoggiorno,false); 
	if(validate_date(associata->datainiziosoggiorno))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while(true){
		get_input("Inserisci la data di fine soggiorno [YYYY-MM-DD]: ",DATE_LEN, associata->datafinesoggiorno, false);
		if(validate_date(associata->datafinesoggiorno))
				break;
			fprintf(stderr, "Data errata!\n");
		} 
	do_insert_assoc(associata); 
}

void ins_sostitution( struct sostituito *sostituito, struct ricambio *ricambio)
{	
	char buff[NUM_LEN]; 
	int num; 
	printf("\n** Dettagli sostituzione ricambio**\n\n");
	if(&sostituito->revisioneassociata == NULL){
		get_input("Inserisci il numero della revsione in questione: ",NUM_LEN, buff, false);
		sostituito->revisioneassociata = atoi(buff);
	} 
	get_input("Inserisci il codice del ricambio utilizzato : ", NUM_LEN, sostituito->ricambioutilizzato,false);
	get_input("Inserisci la quantità di ricambi sostituiti : ",NUM_LEN, buff, false);
	sostituito->quantitasostituita = atoi(buff); 
	strcpy(ricambio->codice, sostituito->ricambioutilizzato);

	do_insert_sostitution(sostituito); 
	do_select_sparepart(ricambio); 	

	num = ricambio->quantitainmagazzino - sostituito->quantitasostituita; 
	ricambio->quantitainmagazzino = num; 

	do_update_spareparts_number(ricambio);

}

void ins_tour(struct tour *tour){

	char buff[NUM_LEN]; 
	char buffer[DEC_LEN]; 
	char bit[BIT_LEN]; 
	
	printf("** Dettagli inserimento tour **\n\n");
	get_input("Inserisci la denominazione: ", VARCHAR_LEN, tour->denominazionetour, false);
	get_input("Inserisci la descrizione (massimo 5000 caratteri): ", DES_LEN, tour->descrizionetour, false);
	get_input("Inserisci il numero minimo di partecipanti: ", NUM_LEN,buff, false);
	tour->minimopartecipanti = atoi(buff); 
	get_input("Inserisci il costo dell'assicurazione: ", DEC_LEN, buffer , false);
	tour->assicurazionemedica = atof(buffer); 
	get_input("Inserisci il costo del bagaglio: ", DEC_LEN, buffer, false);
	tour->bagaglio = atof(buffer);
	get_input("Inserisci il costo della garanzia di annullamento: ", DEC_LEN, buffer, false);
	tour->garanziaannullamento = atof(buffer); 
	while(true){
		get_input("Inserisci l'indicazione sulla presenza di un'accompagnatrice: ", BIT_LEN, bit, false);
		if(validate_double(bit))
			break;
		fprintf(stderr, "Inserisci un valore compreso tra[0,1]!\n"); 
	}
	tour->accompagnatrice = atoi(bit); 
	do_insert_tour(tour); 
}

void ins_trip(struct viaggio *viaggio)
{	
	char buff[NUM_LEN]; 
	char buffer[DEC_LEN]; 
	printf("** Dettagli inserimento viaggio **\n\n");
	get_input("Inserisci il tour a cui e' associato: ", VARCHAR_LEN, viaggio->tourassociato, false);
	get_input("Inserisci l'ID del conducente assegnato: ", NUM_LEN, buff, false);
	viaggio->conducente = atoi(buff); 
	get_input("Inserisci l'ID dell'eventuale accompagnatrice: ", NUM_LEN, buff, false);
	viaggio->accompagnatrice = atoi(buff); 
	get_input("Inserisci la targa del mezzo impiegato: ", VARCHAR_LEN, viaggio->mezzoimpiegato, false);

	while(true) {
		get_input("Inserisci la data di partenza [YYYY-MM-DD]: ", DATE_LEN, viaggio->datadipartenzaviaggio, false);
		if(validate_date(viaggio->datadipartenzaviaggio))
			break;
		fprintf(stderr, "Data Errata!\n");
		}
	while(true) {
		get_input("Inserisci la data di ritorno [YYYY-MM-DD]: ", DATE_LEN, viaggio->datadiritornoviaggio, false);
		if(validate_date(viaggio->datadiritornoviaggio))
			break;
		fprintf(stderr, "Data Errata!\n");
		}

	get_input("Inserisci il prezzo: ", DEC_LEN, buffer, false);
	viaggio->costodelviaggio = atof(buffer); 
	get_input("Inserisci il numero di Km che verranno percorsi: ", NUM_LEN, buff, false);
	viaggio->numerodikm = atoi (buff); 
	get_input("Inserisci i posti disponibili totali: ", NUM_LEN, buff, false);
	viaggio->postidisponibili = atoi(buff); 
	do_insert_trip(viaggio); 
}


void ins_destination(struct meta *meta)
{	
	printf("** Dettagli inserimento meta **\n\n");
	get_input("Inserisci la localita di appartenenza: ", VARCHAR_LEN, meta->localitadiappartenenza, false);
	get_input("Inserisci il nome: ", VARCHAR_LEN, meta->nomemeta, false);
	get_input("Inserisci l'indirizzo e-mail: ", VARCHAR_LEN, meta->emailmeta, false);
	get_input("Inserisci il numero di telefono: ", VARCHAR_LEN, meta->telefonometa, false);
	get_input("Inserisci il numero di fax: ", VARCHAR_LEN, meta->faxmeta, false);
	get_input("Inserisci l'indirizzo: ", VARCHAR_LEN, meta->indirizzo, false);
	get_input("Inserisci la tipologia (bene o albergo )", VARCHAR_LEN, meta->tipologiameta, false);

	if(strcmp(meta->tipologiameta, "albergo") == 0)
		get_input("Inserisci la categoria dell'albergo: ", VARCHAR_LEN, meta->categoriaalbergo, false);
	else
		while(true) {
	get_input("Inserisci l'orario di apertura del bene [HH:MM]: ", TIME_LEN, meta->orariodiapertura, false);
	if(validate_time(meta->orariodiapertura))
		break;
		}

	do_insert_destination(meta); 
}

/*
void ins_visit(struct visita *visita)
{	clear_screen();
	printf("** Dettagli inserimento visita **\n\n");
	get_input("Inserisci l'ID: ", NUM_LEN, visita->idvisita, false); // ID è autoincrement, quindi non va inserito?
	get_input("Inserisci l'ID del viaggio associato: ", NUM_LEN, visita->viaggiorelativo, false);
	get_input("Inserisci l'ID della meta visitata: ", NUM_LEN, visita->metavisitata, false);
	while(true) {
		get_input("Inserisci la data di arrivo prevista [YYYY-MM-DD]: ", DATE_LEN, visita->datadiarrivo, false);
		if(validate_date(visita->datadiarrivo))
			break;
		fprintf(stderr,"Data errata!"); 
			
	}
	while(true) {
		get_input("Inserisci la data di partenza prevista [YYYY-MM-DD]: ", DATE_LEN, visita->datadipartenza, false);
		if(validate_date(visita->datadipartenza))
			break;
		fprintf(stderr,"Data errata!");	
	}

while(true) {
		get_input("Inserisci l'orario di arrivo previsto [HH:MM]", TIME_LEN, visita->oradiarrivo, false);
	if(validate_time(visita->oradiarrivo))
		break;
	fprintf(stderr,"Orario errato!");	
	}
while(true) {
		get_input("Inserisci l'orario di partenza previsto [HH:MM]", TIME_LEN, visita->oradipartenza, false);
	if(validate_time(visita->oradipartenza))
		break;
	fprintf(stderr,"Orario errato!");
	}

	get_input("Inserisci l'indicazione sulla presenza della guida(si/no): ", BIT_LEN, visita->guida, false);
	get_input("Inserisci l'importo dell'eventuale supplemento: ", DEC_LEN, visita->supplemento, false);
	getinput("Inserisci la descrizione dell'eventuale trattamento alberghiero (massimo 5000 caratteri)", DES_LEN, visita->trattamentoalberghiero, false); 
}

void ins_picture(struct documentazionefotografica *documentazionefotografica) 
{	clear_screen();
	printf("** Dettagli inserimento nuova foto **\n\n");
	get_input("Inserisci l'ID : ", NUM_LEN, documentazionefotografica->idfoto, false); // ID è autoincrement, quindi non va inserito?
	get_input("Inserisci l'immagine: ", PIC, documentazionefotografica->foto, false);
}


void ins_employee(struct dipendente *dipendente) 
{	clear_screen();
	printf("** Dettagli inserimento dipendente **\n\n");
	get_input("Inserisci l'ID: ", NUM_LEN, dipendente->iddipendente, false); // ID è autoincrement, quindi non va inserito?
	get_input("Inserisci il nome: ", VARCHAR_LEN, dipendente->nomedipendente, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, dipendente->cognomedipendente, false);
	get_input("Inserisci la tipologia (Autista, Hostess o Meccanico): ", BIT_LEN, dipendente->tipologiadipendente, false);
	get_input("Inserisci il numero di telefono aziendale: ", NUM_LEN,  dipendente->telefonoaziendale, false); 
}

void ins_room(struct camera *camera)
{	clear_screen();
	printf("** Dettagli inserimento camera di albergo **\n\n");
	get_input("Inserisci il numero della camera : ", NUM_LEN, camera->numerocamera, false);
	get_input("Inserisci l'ID dell'albergo in cui la camera è ubicata : ", NUM_LEN, camera->albergo, false);
	get_input("Inserisci la tipologia: ", VARCHAR_LEN, camera->tipologia, false);
	get_input("Inserisci il prezzo giornaliero del soggiorno: ", DEC_LEN, camera->costo, false);
}

void ins_location(struct localita *localita)
{	clear_screen();
	printf("** Dettagli inserimento localita **\n\n");
	get_input("Inserisci il nome: ", VARCHAR_LEN, localita->nomelocalita, false);
	get_input("Inserisci ll nome della regione: ", VARCHAR_LEN, localita->regione, false);
	get_input("Inserisci il nome dello stato: ", VARCHAR_LEN, localita->stato, false);
}

void ins_map(struct mappa *mappa)
{	clear_screen();
	printf("** Dettagli inserimento mappa **\n\n");
	get_input("Inserisci l'ID: ", NUM_LEN, mappa->idmappa, false); //Autoincrement ???
	get_input("Inserisci il nome della citta' rappresentata nella mappa: ", VARCHAR_LEN, mappa->citta, false);
	get_input("Inserisci il livello di dettaglio: ", VARCHAR_LEN, mappa->livellodidettaglio, false);
	get_input("Inserisci il nome della zona rappresentata dalla mappa: ", VARCHAR_LEN, mappa->zona, false);
	get_input("Inserisci il nome della località in cui è ubicata la citta' rappresentata: ", VARCHAR_LEN, mappa->zona, false);
}
void ins_costumer(struct cliente *cliente)
{	clear_screen();
	printf("** Dettagli inserimento cliente **\n\n");
	get_input("Inserisci l'indirizzo e-mail: ", VARCHAR_LEN, cliente->emailcliente, false);
	get_input("Inserisci il nome: ", VARCHAR_LEN, cliente->nomecliente, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, cliente->cognomecliente, false);
	get_input("Inserisci l'indirizzo: ", VARCHAR_LEN, cliente->indirizzocliente, false);
	get_input("Inserisci il codice fiscale: ", VARCHAR_LEN, cliente->codicefiscale, false);
	get_input("Inserisci il recapito telefonico: ", NUM_LEN, cliente->recapitotelefonico, false);
	get_input("Inserisci il numero di fax: ", NUM_LEN, cliente->fax, false);
	while{
		get_input("Inserisci l'ultima data d'invio dei documuenti [YYYY-DD-MM]: ", DATE_LEN, cliente->datadocumentazione, false);
		if(validate_date(cliente->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
}

void ins_reservation(struct prenotazione *prenotazione)
{	clear_screen();
	printf("** Dettagli inserimento prenotazione **\n\n");
	get_input("Inserisci il numero di prenotazione: ", NUM_LEN, prenotazione->numerodiprenotazione, false);/////Autoincrement
	get_input("Inserisci l'indirizzo e-mail del cliente che ha effettuato la prenotazione : ", VARCHAR_LEN, prenotazione->clienteprenotante, false);
	while{
		get_input("Inserisci data [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datadiprenotazione, false);
		if(validate_date(prenotazione->datadiprenotazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while{
		get_input("Inserisci data di conferma [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datadiconferma, false);
		if(validate_date(prenotazione->datadiconferma))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	while{
		get_input("Inserisci data di saldo [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datasaldo, false);
		if(validate_date(prenotazione->datasaldo))
			break;
		fprintf(stderr, "Data errata!\n");
	}
}
void ins_seat(struct postoprenotato *postoprenotato)
{	clear_screen();
	printf("** Dettagli inserimento passeggero **\n\n");
	get_input("Inserisci il numero di posto  : ", NUM_LEN, postoprenotato->numerodiposto, false);
	get_input("Inserisci l'ID del viaggio a cui partecipera' il passeggero: ", NUM_LEN, postoprenotato->viaggioassociato, false);
	get_input("Inserisci l'eta': ", NUM_LEN, postoprenotato-> etapasseggero, false);
	get_input("Inserisci il nome: ", VARCHAR_LEN, postoprenotato-> nomepasseggero, false);
	get_input("Inserisci il cognome: ", VARCHAR_LEN, postoprenotato-> cognomepasseggero, false);
}

void ins_review(struct revisione *revisione)
{	clear_screen();
	printf("** Dettagli inserimento revisione **\n\n");
	get_input("Inserisci l'ID: ", NUM_LEN, revisione->idrevisione, false);
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

void ins_sparepart(struct ricambio *ricambio)
{	clear_screen();
	printf("** Dettagli inserimento ricambio **\n\n");
	get_input("Inserisci il codice: ", VARCHAR_LEN, ricambio->codice, false);
	get_input("Inserisci il costo unitario: ", DEC_LEN, ricambio->costounitario, false);
	get_input("Inserisci la quantita' minima: ", NUM_LEN, ricambio->quantitadiriordino, false);
	get_input("Inserisci la descrizione (massimo 5000 caratteri) : ", DES_LEN, ricambio-> descrizione, false);
	get_input("Inserisci la scorta minima: ", NUM_LEN, ricambio-> scortaminima, false);
	get_input("Inserisci quantita' di pezzi disponili: ", NUM_LEN, ricambio-> quantitainmagazzino, false);
}

void ins_bus(struct mezzo *mezzo)
{	clear_screen();
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
{	clear_screen();
	printf("** Dettagli inserimento modello **\n\n");
	get_input("Inserisci l'ID : ", NUM_LEN, modello->idmodello, false); // AUTOINCREMENT???
	get_input("Inserisci il nome : ", DEC_LEN, modello->nomemodello, false);
	get_input("Inserisci la casa costruttrice : ", NUM_LEN, modello->casacostruttrice, false);
	get_input("Inserisci i dati tecnici (massimo 5000 caratteri) : ", DES_LEN, modello-> datitecnici, false);
	get_input("Inserisci il numero di posti: ", NUM_LEN, modello-> numeroposti, false);
}

void ins_certify(struct tagliando *tagliando)
{	clear_screen();
	printf("** Dettagli inserimento tagliando **\n\n");
	get_input("Inserisci l'ID : ", NUM_LEN, tagliando->idtagliando, false); // AUTOINCREMENT???
	get_input("Inserisci la tipologia del tagliando: ", VARCHAR_LEN, tagliando->tipologiatagliando, false);
	get_input("Inserisci le validita' superate (massimo 5000 caratteri) : ", DES_LEN, tagliando->validitasuperate, false);
}

void ins_comfort(struct comfort *comfort)
{	clear_screen();
	printf("** Dettagli inserimento comfort **\n\n");
	get_input("Inserisci l'ID : ", NUM_LEN, comfort->idcomfort, false); // AUTOINCREMENT???
	get_input("Inserisci il nome : ", VARCHAR_LEN, comfort->nomecomfort, false);
	get_input("Inserisci la descrizione (massimo 5000 caratteri) : ", DES_LEN, comfort->descrizionecomfort, false);
}

void ins_service(struct servizio *servizio)
{	clear_screen();
	printf("** Dettagli inserimento servizio **\n\n");
	get_input("Inserisci l'ID : ", NUM_LEN, servizio->idservizio, false); // AUTOINCREMENT???
	get_input("Inserisci il nome : ", VARCHAR_LEN, servizio->nomeservizio, false);
	get_input("Inserisci la descrizione (massimo 5000 caratteri) : ", DES_LEN, servizio->descrizioneservizio, false);
}
*/
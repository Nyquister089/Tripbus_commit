#include <string.h>
#include "../model/trpdb.h"
#include "show.h" 

void show_reservation (struct prenotazione * prenotazione)
{	
	char buff[NUM_LEN];
	printf("\n\n**  Dettagli prenotazione ** \n\n"); 
	get_input("Inserisci numero d'interesse : ", NUM_LEN , buff, false); 
	prenotazione->numerodiprenotazione = atoi(buff); 
    do_select_reservation(prenotazione);
	printf("\n\n** Dettagli prenotazione **\n\n");
 	printf(" Prenotazione numero: 	%d \n E-mail cliente: 	%s \n Data di prenotazione: 	%s \n Data di conferma: 	%s \n Data Saldo: 		%s \n\n",
		prenotazione->numerodiprenotazione, 
		prenotazione->clienteprenotante,
		prenotazione->datadiprenotazione, 
		prenotazione->datadiconferma, 
		prenotazione->datasaldo); 

}

void show_trip(struct viaggio *viaggio)
{	
	char buff[NUM_LEN]; 
	printf("\n\n**  Dettagli viaggio ** \n\n"); 
	get_input("Inserisci l'id d'interesse: ", NUM_LEN, buff, false); 
	viaggio->idviaggio = atoi(buff); 
	do_select_trip(viaggio); 
 	printf("*Tour:				%s \n Conducente:			%d \n Accompagnatrice:		%d \n Targa mezzo:			%s \n Data di partenza:		%s \n Data di ritorno:		%s \n Costo:				%f \n Chilometri da percorrere:	%d \n Posti disponibili:		%d \n Data annullamento:		%s \n\n", 
		viaggio->tourassociato,
		viaggio->conducente, 					
		viaggio->accompagnatrice, 				
		viaggio->mezzoimpiegato, 			
		viaggio->datadipartenzaviaggio, 
		viaggio->datadiritornoviaggio, 
		viaggio->costodelviaggio, 
		viaggio->numerodikm, 
		viaggio->postidisponibili,
		viaggio->datadiannullamento); 
}

void show_costumer (struct cliente * cliente)
{	
	
	get_input("Inserisci la mail d'interesse : ", VARCHAR_LEN , cliente->emailcliente, false);
    do_select_costumer(cliente); 
	printf("\n\n**  Dettagli cliente ** \n\n");
		printf("\n E-mail:  %s \n Nome: %s \n Cognome: %s \n Indirizzo: %s \n Codice fiscale: %s \n Recapito telefonico: %s \n Fax: %s \n Data documentazione: %s \n", 
		cliente->emailcliente,
		cliente->nomecliente,
		cliente->cognomecliente,
		cliente->indirizzocliente,
		cliente->codicefiscale,
		cliente->recapitotelefonico,
		cliente->fax,
		cliente->datadocumentazione
		);
}

void show_tour(struct tour *tour)
{
	printf("\n\n**  Dettagli tour ** \n\n");
	get_input("Inserisci la denomiazione d'interesse: ", VARCHAR_LEN, tour->denominazionetour, false); 
	do_select_tour(tour); 
	printf("*Descrizione:		%s \n Minimo partecipanti:	%d \n Assicurazione medica:	%f \n Bagaglio: 		%f \n Garanzia annullamento:	%f \n Accompagnatrice:	%d \n",  
		tour->descrizionetour, 
		tour->minimopartecipanti,
		tour->assicurazionemedica, 
		tour->bagaglio, 
		tour->garanziaannullamento, 
		tour->accompagnatrice
		);
}



void show_sparepart(struct ricambio *ricambio)
{	


	printf("\n\n**  Dettagli ricambio ** \n\n");
	get_input("Inserisci il codice del ricambio d'interesse: ",VARCHAR_LEN, ricambio->codice, false);
	do_select_sparepart(ricambio); 
	printf("*Costo unitario:	%f \n Quatità di Riordino: 	%d \n Scorta Minima:		%d \n Quantità in magazzino:	%d \n Descrizione:		%s \n", 
		ricambio->costounitario,
		ricambio->quantitadiriordino,
		ricambio->scortaminima,
		ricambio->quantitainmagazzino,
		ricambio->descrizione
		);
}

void show_review (struct revisione *revisione){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli revisione **\n\n");
	get_input("Inserisci l'id d'interesse: ", NUM_LEN, buff, false); 
	revisione->idrevisione = atoi(buff);
	do_select_review(revisione); 
 	printf("*Mezzo revsionato:	%s \n Id adetto: 		%d \n Data inizio: 		%s \n Data fine: 		%s\n Chilometraggio:	%d\n Operazioni eseguite:	%s \n Tipologia revsione:	%s \n Motivazione:	%s \n\n",
	revisione->mezzorevisionato,
	revisione->addettoallarevisione,
	revisione->datainizio,
	revisione->datafine,
	revisione->chilometraggio,
	revisione->operazionieseguite,
	revisione->tipologiarevisione,
	revisione->motivazione
	); 
}

void show_bus(struct mezzo *mezzo)
{	
	printf("\n\n** Dettagli mezzo **\n\n");
	get_input("Inserisci la targa del mezzo d'interesse: ", VARCHAR_LEN, mezzo->targa, false); 
	do_select_bus(mezzo); 
 	printf(" *Modello:		%s\n Ultima revisone mtc: 	%s \n Ingombri: 		%s \n Autonomia: 		%d\n Chilometraggio:	%d\n Data immatricolazione:	%s \n\n",
		mezzo->modellomezzo,
		mezzo->dataultimarevisioneinmotorizzazione, 
		mezzo->ingombri, 
		mezzo->autonomia,
		mezzo->valorecontakm, 
		mezzo->dataimmatricolazione); 

}

void show_assoc(struct associata *associata)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli associata **\n\n");
	get_input("Inserisci il codice dell'albergo:",NUM_LEN, buff, false); 
	associata->albergoinquestione = atoi(buff); 
	get_input("Inserisci il codice della camera :",NUM_LEN, buff, false);
	associata->cameraprenotata = atoi(buff); 
	get_input("Inserisci il numero dell'ospite :",NUM_LEN, buff, false);
	associata->ospite = atoi(buff); 
	do_select_assoc(associata);
 	printf("*Data inizio soggiorno:%s \n Data fine soggiorno:	%s \n\n",
		associata->datainiziosoggiorno,
		associata->datafinesoggiorno); 

}

void show_skills(struct competenze *competenze)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli competenze  **\n\n");
	get_input("Inserisci l'id del meccanico competente :",NUM_LEN, buff, false); 
	competenze->meccanicocompetente = atoi(buff); 
	get_input("Inserisci il modello d'interesse :",VARCHAR_LEN, competenze->modelloassociato, false);
	
	do_select_skills(competenze);
 	printf("*Nome meccanico:%s \n Telefono :	%s \n\n",
		competenze->nomemeccanico,
		competenze->telefono); 
}

void show_employee(struct dipendente *dipendente)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli Dipendente  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	dipendente->iddipendente = atoi(buff); 
	do_select_employee(dipendente);
 	printf("*Nome:		%s \n Cognome:	%s \n Tipologia:	%s \n Telefono:	%s \n\n",
		dipendente->nomedipendente,
		dipendente->cognomedipendente,
		dipendente->tipologiadipendente,
		dipendente->telefonoaziendale ); 
}


void show_fmo(struct fmo *fmo)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli Foto-Modelli  **\n\n");
	get_input("Inserisci l'id della foto d'interesse:",NUM_LEN, buff, false); 
	fmo->foto = atoi(buff); 
	get_input("Inserisci il nome del modello d'interesse:",VARCHAR_LEN, fmo->modello,  false);

	do_select_fmo(fmo);
 	printf("*Descrizione:	%s \n Immagine:	%s\n\n",
		fmo->descrizione,
		fmo->immagine); 
}

void show_fme(struct fme *fme)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli Foto-Mete  **\n\n");
	get_input("Inserisci l'id della foto d'interesse:",NUM_LEN, buff, false); 
	fme->foto = atoi(buff); 
	get_input("Inserisci l'id della meta d'interesse:",NUM_LEN, buff, false);
	fme->meta = atoi(buff); 
	do_select_fme(fme);
 	printf("*Nome:	%s\n Descrizione:	%s \n Immagine:	%s\n\n",
		fme->nome,
		fme->descrizione,
		fme->immagine); 
}

void show_ofr(struct offre *offre)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli servizi-offerti  **\n\n");
	get_input("Inserisci l'id del servizio d'interesse:",NUM_LEN, buff, false); 
	offre->idservizio = atoi(buff); 
	get_input("Inserisci l'id dell'albergo offerente:",NUM_LEN, buff, false);
	offre->albergoofferente = atoi(buff); 
	do_select_ofr(offre);
 	printf("*Albergo:	%s\n Servizio:	%s \n Descrizione:	%s\n\n",
		offre->meta,
		offre->servizio,
		offre->descrizione); 
}

void show_tome(struct tome *tome)
{	
	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli tour-meta  **\n\n");
	get_input("Inserisci il nome del tour d'interesse:",VARCHAR_LEN, tome->tourinquestione, false); 
	get_input("Inserisci l'id della meta d'interesse:",NUM_LEN, buff, false);
	tome->metainquestione = atoi(buff); 
	do_select_tome(tome);
 	printf("*Descrizione tour:	%s\n Meta:		%s\n\n",
		tome->descrizione,
		tome->meta); 
}


void show_user(struct utente *utente){

	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli utente **\n\n");
	get_input("Inserisci l'id dell'utente d'interesse:", NUM_LEN, buff, false);
	utente->id = atoi(buff); 
	do_select_user(utente);
 	printf("*Email:		%s\n Password:	%s \n Tipo:		%d\n\n",
		utente->email,
		utente->pswrd,
		utente->tipo); 
}

void show_seat(struct postoprenotato *postoprenotato){

	char buff [NUM_LEN]; 
	printf("\n\n** Dettagli posto prenotato  **\n\n");
	get_input("Inserisci il numero di posto d'interesse:",NUM_LEN, buff, false); 
	postoprenotato->numerodiposto = atoi(buff); 
	get_input("Inserisci l'id del viaggio d'interesse:",NUM_LEN, buff, false);
	postoprenotato->viaggioassociato = atoi(buff); 
	do_select_seat(postoprenotato);
 	printf("*Nome passeggero:	%s\n Cognome passeggero:	%s \n Età:			%d \n Numero di prenotazione:%d\n\n",
		postoprenotato->nomepasseggero,
		postoprenotato->cognomepasseggero,
		postoprenotato->etapasseggero,
		postoprenotato->prenotazioneassociata);

}

void show_model(struct modello *modello){
	
	printf("\n\n** Dettagli modello  **\n\n");
	get_input("Inserisci l'id del modello d'interesse:",VARCHAR_LEN, modello->nomemodello, false); 
	do_select_model(modello);
 	printf("* Casa costruttrice:	%s\n Dati tecnici:		%s \n Numero di posti:	%d\n\n",
		modello->casacostruttrice,
		modello->datitecnici,
		modello->numeroposti);
}

void show_certify(struct tagliando *tagliando){
	
	char buff[NUM_LEN];
	printf("\n\n** Dettagli tagliando  **\n\n");
	get_input("Inserisci l'id  d'interesse:",NUM_LEN, buff, false); 
	tagliando->idtagliando= atoi(buff); 
	do_select_certify(tagliando);
 	printf("*Tipologia:		%s\n Validità superate:	%s \n\n",
		tagliando->tipologiatagliando,
		tagliando->validitasuperate);
}

void show_destination(struct meta *meta){

	char buff[NUM_LEN];
	printf("\n\n** Dettagli meta  **\n\n");
	get_input("Inserisci l'id  d'interesse:",NUM_LEN, buff, false); 
	meta->idmeta= atoi(buff); 
	do_select_destination(meta); 
	printf("*Nome:		%s\n Tipologia:	%s\n Località:	%s\n Indirizzo:	%s\n Telefono:	%s\n E-mail:	%s\n Fax:		%s\n",
		meta->nomemeta,
		meta->tipologiameta,
		meta->localitadiappartenenza,
		meta->indirizzo,
		meta->telefonometa,
		meta->emailmeta,
		meta->faxmeta); 
	if(strcmp((meta->tipologiameta), "Albergo") == 0)
		printf(" Categoria:	%s\n\n", meta->categoriaalbergo); 
	else
		printf(" Orario di apertura:%s\n\n", meta->orariodiapertura); 

}

void show_service (struct servizio  *servizio ){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli servizio   **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	servizio ->idservizio  = atoi(buff); 
	do_select_service (servizio ); 
	printf("*Nome:		%s \n Descrizione:	%s  \n\n",
		servizio->nomeservizio ,
		servizio->descrizioneservizio 
		
		);
}

void show_comfort(struct comfort *comfort){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli comfort  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	comfort->idcomfort = atoi(buff); 
	do_select_comfort(comfort); 
	printf("*Nome:		%s \n Descrizione:	%s  \n\n",
		comfort->nomecomfort,
		comfort->descrizionecomfort
		
		);
}


void show_picture(struct documentazionefotografica *documentazionefotografica){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli documentazionefotografica  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	documentazionefotografica->idfoto = atoi(buff); 
	do_select_picture(documentazionefotografica); 
	printf("*Foto:		%s \n Descrizione:	%s  \n\n",
		documentazionefotografica->foto,
		documentazionefotografica->descrzione
		
		);
}


void show_map(struct mappa *mappa){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli mappa  **\n\n");
	get_input("Inserisci il numero d'interesse:",NUM_LEN, buff, false); 
	mappa->idmappa = atoi(buff); 
	do_select_map(mappa); 
	printf("*Città:		%s \n Località:	%s \n Dettaglio:	%s \n Zona:		%s \n Immagine: 	%s \n\n",
		mappa->citta,
		mappa->localitarappresentata,
		mappa->dettaglio, 
		mappa->zona,
		mappa->immagine
		);

}

void show_room(struct camera *camera){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli camera  **\n\n");
	get_input("Inserisci il numero d'interesse:",NUM_LEN, buff, false); 
	camera->numerocamera = atoi(buff); 
	get_input("Inserisci l'id dell'albergo d'interesse:",NUM_LEN, buff, false); 
	camera->albergo = atoi(buff);
	do_select_room(camera); 
	printf("*Tipologia:	%s \n Costo:		%f\n\n",
		camera->tipologia,
		camera->costo
		);

}

void show_location(struct localita *localita){


	printf("\n\n** Dettagli localita  **\n\n");
	get_input("Inserisci il nome d'interesse: ",VARCHAR_LEN, localita->nomelocalita, false); 
	get_input("Inserisci il nome della regione: ", VARCHAR_LEN, localita->regione, false);
	do_select_location(localita); 
	printf("*Stato:		%s\n\n",
		
		localita->stato
		);

}

void show_visit(struct visita *visita){
	char buff[NUM_LEN];
	printf("\n\n** Dettagli visita  **\n\n");
	get_input("Inserisci l'id  d'interesse:",NUM_LEN, buff, false); 
	visita->idvisita= atoi(buff); 
	do_select_visit(visita); 
	printf("*Tour:		%s  Id viaggio:	%d*\n*Nome meta:	%s Id meta:	%d*\n Data di arrivo:	%s\n Ora di arrivo:		%s\n Data di partenza:	%s\n Ora di partenza:	%s\n Guida:			%d\n Supplemento:		%f\n Trattamento:		%s\n\n",
		visita->tour,
		visita->viaggiorelativo,
		visita->meta,
		visita->metavisitata,
		visita->datadiarrivo,
		visita->oradiarrivo,
		visita->datadipartenza,
		visita->oradipartenza, 
		visita->guida,
		visita->supplemento,
		visita->trattamentoalberghiero);

}


void show_expired_review (void) 
{	
	printf("** Ecco i mezzi le cui revisioni risultano scadute o in scadenza**\n\n");
	get_info_revisioni();
}
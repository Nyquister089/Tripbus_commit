#include <string.h>
#include "../model/trpdb.h"
#include "show.h" 

void show_reservation (struct prenotazione * prenotazione)
{
printf("\n\n** Dettagli prenotazione **\n\n");
 	printf(" Prenotazione numero: 	%d \n E-mail cliente: 	%s \n Data di prenotazione: 	%s \n Data di conferma: 	%s \n Data Saldo: 		%s \n\n",
		prenotazione->numerodiprenotazione, 
		prenotazione->clienteprenotante,
		prenotazione->datadiprenotazione, 
		prenotazione->datadiconferma, 
		prenotazione->datasaldo); 

}

void show_trip(struct viaggio *viaggio)
{printf("\n\n**  Dettagli viaggio ** \n\n"); 
 	printf(" ID : %d \n Tour : %s \n Conducente : %d \n Accompagnatrice : %d \n Targa mezzo : %s \n Data di partenza : %s \n Data di ritorno : %s \n Costo : %f \n Chilometri da percorrere : %d \n Posti disponibili: %d \n Data annullamento: %s \n ",
 		viaggio->idviaggio, 
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
{printf("\n\n**  Dettagli cliente ** \n\n");
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
		printf("\n Denominazione:  	%s \n Descrizione:		   %s \n Minimo partecipanti: 	%d \n Assicurazione medica:	%f \n Bagaglio: 		%f \n Garanzia annullamento:	%f \n Accompagnatrice:	%d \n", 
		tour->denominazionetour, 
		tour->descrizionetour, 
		tour->minimopartecipanti,
		tour->assicurazionemedica, 
		tour->bagaglio, 
		tour->garanziaannullamento, 
		tour->accompagnatrice
		);
}

void show_service (struct servizio * servizio)
{
	printf("\n\n**  Dettagli servizio ** \n\n");
		printf("\n ID:  	%d\n Nome:		   %s \n Descrizione : 	%s \n", 
		servizio->idservizio, 
		servizio->nomeservizio, 
		servizio->descrizioneservizio
		);
}

void show_sparepart(struct ricambio *ricambio)
{	
	printf("\n\n**  Dettagli ricambio ** \n\n");
		printf("\n Codice:		%s \n Costo unitario:	%f \n Quatità di Riordino: 	%d \n Scorta Minima:		%d \n Quantità in magazzino:	%d \n Descrizione:		%s \n", 
		ricambio->codice,
		ricambio->costounitario,
		ricambio->quantitadiriordino,
		ricambio->scortaminima,
		ricambio->quantitainmagazzino,
		ricambio->descrizione
		);
}

void show_review (struct revisione *revisione)
{
printf("\n\n** Dettagli prenotazione **\n\n");
 	printf(" *ID:			%d *\n Mezzo revsionato:	%s \n Id adetto: 		%d \n Data inizio: 		%s \n Data fine: 		%s\n Chilometraggio:	%d\n Operazioni eseguite:	%s \n Tipologia revsione:	%s \n Motivazione:	%s \n\n",
	revisione->idrevisione,
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
 	printf(" *Targa:		%s *\n Modello:		%s \n Ultima revisone mtc: 	%s \n Ingombri: 		%s \n Autonomia: 		%d\n Chilometraggio:	%d\n Data immatricolazione:	%s \n\n",
		mezzo->targa,
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
	get_input("Inserisci il modello d'interesse :",NUM_LEN, competenze->modelloassociato, false);
	do_select_skills(competenze);
 	printf("*Nome meccanico:%s \n Telefono :	%s \n\n",
		competenze->modelloassociato,
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
	get_input("Inserisci il nome del modello d'interesse:",NUM_LEN, fmo->modello, false);
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

void show_expired_review (void) 
{	
	printf("** Ecco i mezzi le cui revisioni risultano scadute o in scadenza**\n\n");
	get_info_revisioni();
}
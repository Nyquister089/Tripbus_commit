#include <string.h>
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

void show_expired_review (void) 
{
	printf("** Ecco i mezzi le cui revisioni risultano scadute o in scadenza**\n\n");
	get_info_revisioni();
}
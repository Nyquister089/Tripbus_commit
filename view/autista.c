#include <stdio.h>

#include "autista.h"
#include "../utils/io.h"
#include "../utils/validation.h"
 
char DATE[DATE_LEN]; 
char TARGA[VARCHAR_LEN]; 
char ID_RSRC[VARCHAR_LEN];

int get_drvr_action(void)
{
	char options[6] = {'1','2','3','4','5','6'};
	char op;

	clear_screen();
	puts("*********************************");
	puts("*   INTERFACCIA AUTISTA    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consulta i dati relativi ai viaggi a cui sei assegnato");
	puts("2) Consulta le mete visitate durante un viaggio");
	puts("3) Consulta le mappe");
	puts("4) Consulta l'orario di apertura dei beni tursitici");
	puts("5) Aggiorna il valore del conta km dopo un viaggio"); 
	puts("6) Esci");
	/*Consultare i dati temporali relativi al viaggio a cui è assegnato
Consultare le mete incluse in un viaggio in modo da tracciare il percorso
Aggiornare il valore del contatore chilometrico del mezzo che ha utilizzato per  svolgere il viaggio
*/

	op = multi_choice("Select an option", options, 6);
	return op - '1';
}

bool exe_drvr_act(drvr_act sel)
{	
	struct meta *meta; 
	switch (sel)
		{case VIAGGI_ASSEGNATI:{
				struct viaggio *viaggio; 
				show_assigned_trip(viaggio); 
		return true;
		}
     	
     	case ORARIO_APERTURA:{
     	show_opening_hour(meta);
		return true; 
		 }

	 	case MAPPE:	{
		struct mappa *mappa; 
	 	show_map(mappa); 
		return true;
		 }

	 	case AGGIORNA_KM:{
		struct mezzo *mezzo; 
		update_km(mezzo);
		return true; 
		 }

		case METE_VISITATE: {
		show_destination(meta,NULL,NULL); 
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


void show_assigned_trip(struct viaggio *viaggio)
{	clear_screen();
	char buffer[VARCHAR_LEN]; 
	get_input("Inserisci l'ID del conducente:", VARCHAR_LEN, buffer, false);
	while(true) {
	get_input("Inserisci la data di interesse [YYYY-MM-DD]: ", DATE_LEN, DATE, false);
	if(validate_date(DATE))
		break;
	fprintf(stderr, "Data Errata!\n");
	}
	do_select_assigned_trip(viaggio); 
	printf("** Dettagli del viaggio assegnato **\n\n");
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
}

void show_opening_hour(struct meta *meta)
{	clear_screen();	
	char buffer[VARCHAR_LEN]; 
	printf("** Visualizzazione orario di apertura **\n\n");
	get_input("Inserisci l'ID della meta desiderata:", VARCHAR_LEN, buffer, false);
	while(true) {
	get_input("Inserisci la data di interesse [YYYY-MM-DD]: ", DATE_LEN, DATE, false);
	if(validate_date(DATE))
		break;
	fprintf(stderr, "Data Errata!\n");
	}
	//esegui procedura di select sul meta e visita
	printf(" Il bene turistico %s aprira' alle ore %s ",
			meta->nomemeta, 
			meta->orariodiapertura 
			);
}

void show_map(struct mappa *mappa)
{	clear_screen();	
	char buffer[VARCHAR_LEN]; 
	printf("** Visualizzazione mappa  **\n\n");
	get_input("Inserisci l'ID della mappa desiderata:", VARCHAR_LEN, buffer, false);
	//esegui procedura di select su mappa 
	printf(" Ecco la mappa di  %s:  ",
			mappa->citta  
			);// come si visualizza un dato di tipo blob 
}

void update_km(struct mezzo *mezzo)
{	
	clear_screen();
	char buffer[VARCHAR_LEN]; 	
	printf("** Aggiornamento conta Km **\n\n");
	get_input("Inserisci la targa del mezzo :", VARCHAR_LEN, TARGA, false);
	//esegui procedura di select su mappa 
	get_input("Inserisci il valore attuale del conta chilometri: ", VARCHAR_LEN, mezzo-> valorecontakm, false);

}

void show_destination (struct meta *meta, struct visita *visita, struct viaggio *viaggio)
{
	clear_screen();
	printf("** Procedura visualizzazione mete viaggio **\n\n");
	get_input("Inserisci l'ID del viaggio : ", NUM_LEN , ID_RSRC, false); 
    do_select_trip_destination(meta, viaggio, visita); 
    printf("ID  %s \n : Nome: %s \n Tipologia: %s \n Località: %s \n Indirizzo: %s \n", 
			meta->idmeta,
			meta->nomemeta,
			meta->tipologiameta,
			meta->localitadiappartenenza,
			meta->indirizzo
		);


}

void run_drvr_interface (void)
{ 	drvr_act sel; 
	while (true){
	get_drvr_action(); 
	if (!exe_drvr_act(sel))
		break; 
	
	}
}


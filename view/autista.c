#include <stdio.h>

#include "autista.h"
#include "../utils/io.h"
#include "../utils/validation.h"

int ID; 
char DATE[DATE_LEN]; 
char TARGA[VARCHAR_LEN]; 

int get_driver_action(void)
{
	char options[5] = {'1','2','3','4','5'};
	char op;

	clear_screen();
	puts("*********************************");
	puts("*   INTERFACCIA AUTISTA    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consulta i viaggi a cui sei assegnato");
	puts("2) Consulta l'orario di apertura dei beni tursitici");
	puts("3) Consulta le mappe");
	puts("4) Aggiorna il valore del conta km dopo il viaggio ");
	puts("5) Esci");


	op = multi_choice("Select an option", options, 5);
	return op - '1';
}

bool exe_drvr_act(drv_act sel)
{	
	switch (sel)
		{case VIAGGI_ASSEGNATI:
		show_assigned_trip(struct viaggio *viaggio); 
		return ;
     	
     		case ORARIO_APERTURA:
     		show_opening_hour(struct meta *meta, struct visita *visita);
		return ; 

	 	case MAPPE:		
	 	show_map(struct mappa *mappa); 
		return ;

	 	case AGGIORNA_KM:
		update_km(struct mezzo *mezzo)
		return ; 
		
		case QUIT:
		// gestire l'uscita dal Db (disconnessione e ritorno a schermata iniziale) 
		return ; 
		
	break;
		default:
			fprintf(stderr, "Il carattere digitato non corrisponde a nessuna azione \n");
			exit(EXIT_FAILURE);
	}

	return true;
}


void show_assigned_trip(struct viaggio *viaggio)
{	clear_screen();
	get_input("Inserisci l'ID del conducente:", NUM_LEN, ID, false);
	while(true) {
	get_input("Inserisci la data di interesse [YYYY-MM-DD]: ", DATE_LEN, DATE, false);
	if(validate_date(DATE))
		break;
	fprintf(stderr, "Data Errata!\n");
	}
	//esegui procedura di select sul viaggio, visualizzare il viaggio successivo alla data inserita
	printf("** Dettagli del viaggio assegnato **\n\n");
	printf(" Il conducente %d è assegnato al seguente viaggio : \n Tour associato: %s \n Accompagnatrice: %d\n Targa mezzo: %s \n Data di partenza: %s \n Data di ritorno %s \n Numero di Km da percorrere: %d ",
			viaggio.conducente, 
			viaggio.tourassociato,
			viaggio.accompagnatrice, 
			viaggio.mezzoimpiegato, 
			viaggio.datadipartenzaviaggio,
			viaggio.datadiritornoviaggio,
			viaggio.numerodikm);
}

void show_opening_hour(struct meta *meta, struct visita *visita)
{	clear_screen();	
	printf("** Visualizzazione orario di apertura **\n\n");
	get_input("Inserisci l'ID della meta desiderata:", NUM_LEN, ID, false);
	while(true) {
	get_input("Inserisci la data di interesse [YYYY-MM-DD]: ", DATE_LEN, DATE, false);
	if(validate_date(DATE))
		break;
	fprintf(stderr, "Data Errata!\n");
	}
	//esegui procedura di select sul meta e visita
	printf(" Il bene turistico %s avente ID %d aprira' alle ore %s ",
			meta.nomemeta, 
			visita.metavisitata, 
			visita.orario di apertura,  
			);
}

void show_map(struct mappa *mappa)
{	clear_screen();	
	printf("** Visualizzazione mappa  **\n\n");
	get_input("Inserisci l'ID della mappa desiderata:", NUM_LEN, ID, false);
	//esegui procedura di select su mappa 
	printf(" Ecco la mappa di  %s:  ",
			mappa.citta,  
			);// come si visualizza un dato di tipo blob 
}

void update_km(struct mezzo *mezzo)
{lear_screen();	
	printf("** Aggiornamento conta Km **\n\n");
	get_input("Inserisci la targa del mezzo :", VARCHAR_LEN, TARGA, false);
	//esegui procedura di select su mappa 
	get_input("Inserisci il valore attuale del conta chilometri: ", NUM_LEN, mezzo-> valorecontakm, false);

}

void quit_action (void)
{
	
}

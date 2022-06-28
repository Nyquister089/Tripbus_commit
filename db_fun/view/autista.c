#include <stdio.h>

#include "autista.h"
#include "../utils/io.h"
#include "../utils/validation.h"


int get_drvr_action(void)
{
	char options[5] = {'1','2','3','4','5'};
	char op;

	puts("*********************************");
	puts("*   INTERFACCIA AUTISTA    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consulta i viaggi ed i mezzi a cui sei assegnato");
	puts("2) Consulta le località ed i dati temporali delle mete previste per un viaggio ");
	puts("3) Consulta le mappe");
	puts("4) Aggiorna il valore del conta km dopo un viaggio"); 
	puts("5) Esci");
	/*Consulta le mappe
	Aggiornare il valore del contatore chilometrico del mezzo che ha utilizzato per  svolgere il viaggio
	*/

	op = multi_choice("Select an option", options, 5);
	return op - '1';
}

void show_assigned_trip(void)
{	
	char buff[NUM_LEN];
	int dvr; 

	printf("** Ricerca viaggi assegnati **\n\n");
	get_input("Inserisci l'ID del conducente:", VARCHAR_LEN, buff, false);
	dvr = atoi(buff); 
	printf("** Dettagli del viaggio assegnato **\n\n");
	get_viaggi_assegnati(dvr); 
}

void show_dest_time(void)
{	
	char buff[NUM_LEN];
	int dvr; 

	printf("** Ricerca visite d'interesse **\n\n");
	get_input("Inserisci l'ID del viaggio:", VARCHAR_LEN, buff, false);
	dvr = atoi(buff); 
	printf("** Dettagli temporali delle visite **\n\n");
	get_mete_visite(dvr); 
}

void show_drvr_map(void)
{
	char buff[VARCHAR_LEN];
	printf("** Ricerca la mappa d'interesse **\n\n");
	get_input("Inserisci il nome della località:", VARCHAR_LEN, buff, false);
	printf("** Dettagli mappe relative alla località inserita **\n\n");
	get_mappe(buff); 
}


bool exe_drvr_act(drvr_act sel)
{	
	switch (sel)
		{case VIAGGI_ASSEGNATI:{
		show_assigned_trip(); 
		return true;
		}
     	
     	case ORARI_VISITE:{
     	show_dest_time();
		return true; 
		 }

	 	case MAPPE:	{
	 	show_drvr_map(); 
		return true;
		 }

	 	case AGGIORNA_KM:{ 
		//update_km(mezzo);
		return true; 
		 }

		case QUIT_DRVR:
		// gestire l'uscita dal Db (disconnessione e ritorno a schermata iniziale) 
		return false; 
		
	break;
	}

	return true;
}



/*
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


}*/

void run_drvr_interface (void)
{ 	char sel; 
	while (true){
	sel =  get_drvr_action(); 
	if (!exe_drvr_act(sel))
		break; 
	
	}
}


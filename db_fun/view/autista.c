#include <stdio.h>

#include "autista.h"
#include "show.h"
#include "../utils/io.h"
#include "../utils/validation.h"

struct mezzo *mezzo_drvr;

int drvr_allocation (void)
{
	mezzo_drvr = malloc (sizeof(struct mezzo));
	if(mezzo_drvr == NULL){
		printf("Fallimento malloc su mezzo (Autista)\n\n"); 
		return -1; 
	}
}

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

void update_km(void)
{
	char buff[VARCHAR_LEN];
	bool ans; 
	printf("** Selezione del mezzo d'interesse **\n\n");
	get_input("Inserisci la targa :", VARCHAR_LEN, mezzo_drvr->targa, false);
	printf("** Dettagli mezzo d'interesse **\n\n");
	do_select_bus(mezzo_drvr);
	show_bus(mezzo_drvr); 
	ans =yes_or_no("Vuoi modificare i km di questo mezzo ? ", 's', 'n', false, false); 
	if(ans){
		get_input("\nInserisci l'attuale numero di km : ",NUM_LEN, buff, false); 
		mezzo_drvr->valorecontakm = atoi(buff); 
		do_update_km(mezzo_drvr); 
		}

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
		update_km();
		return true; 
		 }

		case QUIT_DRVR:
		return false; 
		
	break;
	}

	return true;
}

void run_drvr_interface (void)
{ 	char sel; 
	if(mezzo_drvr == NULL)
		drvr_allocation(); 
	while (true){
	sel =  get_drvr_action(); 
	if (!exe_drvr_act(sel))
		break; 
	
	}
}


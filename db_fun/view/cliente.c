#include <stdio.h>

#include"cliente.h"
#include "ins.h"
#include "show.h"

#include "../utils/io.h"
#include "../utils/validation.h"


int get_cstmr_action(void)
{
	char options[5] = {'1','2','3','4','5'};
	char op;
	puts("*********************************");
	puts("*   Interfaccia cliente     *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Visualizza i tour disponibili ed i relativi viaggi previsti");
	puts("2) Consulta le mete relative ad un tour");
	puts("3) Consulta i servizi offerti da un albergo");
	puts("4) Consulta i comfort presenti su un modello");
	puts("5) Esci ");

	op = multi_choice("Scegli un opzione? ", options, 5);
	return op - '1';
}

bool exe_cstmr_act(cstmr_act sel)
{
	switch (sel)
		{case TOUR_INFO:{
		show_tour_information(); 
		return true; 
		}
		
		case METE_TOUR:{
		show_tour_destination(); 
		return true;
		}

	 	case SERVIZI_ALBERGO:{
		show_service_destination();
		return true;
		 }

	 	case COMFORT_MODELLO:{
		show_comfort_model();
		return true; 
		 }
		
		case QUIT_CSTMR:
		return false;
	}

	return true;
}



void show_tour_information(void)
{	
	printf("\n\n** Tour offerti  **\n\n"); 
	get_tour_info(); 
}

void show_tour_destination(void)
{
	char buff[VARCHAR_LEN]; 
	int idv; 
	printf("\n\n ** Esplora le destinazioni dei viaggi **\n\n"); 
	get_input("Inserisca il numero del viaggio a cui è interessato: ",VARCHAR_LEN, buff, false);  
	printf("\n**\n**\n"); 
	idv = atoi(buff); 
	get_mete_info(idv); 
}


void show_service_destination(void)
{	
	char buff[VARCHAR_LEN]; 
	int idh; 
	printf("\n\n ** Esplora i servizi offerti dagli alberghi **\n\n"); 
	get_input("Inserisca il codice dell'albergo a cui è interessato: ",VARCHAR_LEN, buff, false);  
	printf("\n**\n**\n"); 
	idh = atoi(buff); 
	get_servizi_albergo(idh); 
}


void show_comfort_model(void)
{	
	char buff[VARCHAR_LEN]; 
	
	printf("\n\n ** Esplora comfort presenti sui nostri pullman  **\n\n"); 
	get_input("Inserisca il nome del modello a cui è interessato: ",VARCHAR_LEN, buff, false);  
	printf("\n**\n**\n");  
	get_info_modello(buff); 
}

void run_cstmr_interface (void)
{ 	char sel; 
	while (true){
	sel = get_cstmr_action(); 
	if (!exe_cstmr_act(sel))
		break; 
	}
}



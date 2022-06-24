#include <stdio.h>

#include"cliente.h"
#include "ins.h"
#include "show.h"

#include "../utils/io.h"
#include "../utils/validation.h"
 
struct viaggio *viaggio; 
struct servizio *servizio; 
struct comfort *comfort; 
struct modello *modello; 
struct documentazionefotografica *documentazionefotografica; 
struct camera *camera; 

void allocation_cstmr(void)
{
	viaggio = malloc(sizeof(struct viaggio)); 
	if(viaggio == NULL){
		printf("Fallimento malloc su viaggio (cliente) \n\n"); 
		exit(0); 
	}
	servizio = malloc (sizeof(struct servizio));
	if(servizio == NULL){
		printf("Fallimento malloc su servizio (cliente) \n\n"); 
		exit(0); 
	}
	comfort = malloc (sizeof(struct comfort)); 
	if(comfort == NULL){
		printf("Fallimento malloc su comfort (cliente) \n\n"); 
		exit(0); 
	}
	modello = malloc(sizeof(struct modello)); 
	if(modello == NULL){
		printf("Fallimento malloc su modello (cliente) \n\n"); 
		exit(0); 
	}
	documentazionefotografica = malloc(sizeof(struct documentazionefotografica)); 
	if(documentazionefotografica == NULL){
		printf("Fallimento malloc su documentazionefotografica (cliente) \n\n"); 
		exit(0); 
	}
	camera = malloc(sizeof(struct camera)); 
	if(camera == NULL){
		printf("Fallimento malloc su camera (cliente) \n\n"); 
		exit(0); 
	}
	

}


int get_cstmr_action(void)
{
	char options[5] = {'1','2','3','4','5'};
	char op;
	//clear_screen();
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

bool exe_cstmr_act(cstmr_act sel,struct viaggio *viaggio, 
struct servizio *servizio,struct comfort *comfort,struct modello *modello,
struct documentazionefotografica *documentazionefotografica, struct camera * camera)
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
		//show_service_destination(servizi_albergo);
		return true;
		 }

	 	case COMFORT_MODELLO:{
		//show_comfort_model(comfort_mezzo, elenco_modelli);
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
	get_input("Inserisca il numero del viaggio a cui è interessato: ", VARCHAR_LEN, buff, false); 
	printf("\n\n"); 
	idv = atoi(buff); 
	get_mete_info(idv); 
}

/*
void show_service_destination(struct servizi_albergo *servizi_albergo)
{	//clear_screen();
	char buffer[VARCHAR_LEN]; 
	get_input("** Inserire il nome dell'albergo d'interesse **\n\n", VARCHAR_LEN, buffer, false);
	//  lancio procedura select per individuare l'albergo d'interesse e restituisco i relativi servizi offerti, inserisco il numero degli ultimi nella variabile COUNT
	//clear_screen(); 
	printf("** Servizi offerti da: %s \n\n", buffer);
	for(size_t i = 0; i < COUNT; i++) {
		printf("Nome servizio: %s \n Descrizione: %s \n\n",
			servizi_albergo->servizi_albergo[i].nomeservizio,
			servizi_albergo->servizi_albergo[i].descrizioneservizio); 

	}

}

void show_comfort_model(struct comfort_mezzo *comfort_mezzo, struct elenco_modelli *elenco_modelli)
{	//clear_screen();
	char buffer[VARCHAR_LEN]; 
	puts("** Elenco modelli **"); 
	for(size_t i = 0; i < COUNT; i++) {
		printf("%ld) Modello :  %s Id Modello %s \n",
			i,
			elenco_modelli->elenco_modelli[i].nomemodello, 
			elenco_modelli->elenco_modelli[i].idmodello); 
	}
	get_input("** Inserire l'id del modello d'interesse **\n\n", VARCHAR_LEN, buffer, false);
	//  lancio procedura select per individuare il modello d'interesse e restituisco i relativi servizi offerti, inserisco il numero degli ultimi nella variabile COUNT
	//clear_screen(); 
	printf("** Comfort offerti dal bus modello : %s \n\n", buffer);
	
	for(size_t i = 0; i < COUNT; i++) {
		printf("Nome comfort: %s \n Descrizione: %s \n\n",
			comfort_mezzo->comfort_mezzo[i].nomecomfort,
			comfort_mezzo->comfort_mezzo[i].descrizionecomfort); 
	}
}*/

void run_cstmr_interface (void)
{ 	char sel; 
	if(	 viaggio == NULL || servizio == NULL|| comfort == NULL || documentazionefotografica == NULL || camera == NULL ) 
		allocation_cstmr();
	while (true){
	sel = get_cstmr_action(); 
	if (!exe_cstmr_act(sel, viaggio, servizio, comfort, modello, documentazionefotografica, camera))
		break; 
	}
}



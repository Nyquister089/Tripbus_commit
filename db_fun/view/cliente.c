#include <stdio.h>

#include"cliente.h"
#include "ins.h"
#include "show.h"

#include "../utils/io.h"
#include "../utils/validation.h"

struct tour *tour;  
struct meta *meta; 
struct viaggio *viaggio; 
struct servizio *servizio; 
struct comfort *comfort; 
struct modello *modello; 
struct documentazionefotografica *documentazionefotografica; 
struct camera *camera; 

void allocation_cstmr(void)
{
	tour = malloc(sizeof(struct tour)); 
	if(tour == NULL){
		printf("Fallimento malloc su tour (cliente) \n\n"); 
		exit(0); 
	}
	viaggio = malloc(sizeof(struct viaggio)); 
	if(viaggio == NULL){
		printf("Fallimento malloc su viaggio (cliente) \n\n"); 
		exit(0); 
	}
	meta = malloc (sizeof(struct meta )); 
	if(meta == NULL){
		printf("Fallimento malloc su meta (cliente) \n\n"); 
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
	char options[6] = {'1','2','3','4','5','6'};
	char op;
	//clear_screen();
	puts("*********************************");
	puts("*   Interfaccia cliente     *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consulta le informazioni relative tour");
	puts("2) Consulta le mete relative ad un tour");
	puts("3) Consulta i viaggi relativi ad un tour");
	puts("4) Consulta i servizi offerti da un albergo");
	puts("5) Consulta i comfort presenti su un modello");
	puts("6) Esci ");

	op = multi_choice("Scegli un opzione? ", options, 6);
	return op - '1';
}

bool exe_cstmr_act(cstmr_act sel, struct tour *tour,struct viaggio *viaggio, 
struct meta *meta,struct servizio *servizio,struct comfort *comfort,struct modello *modello,
struct documentazionefotografica *documentazionefotografica, struct camera * camera)
{
	switch (sel)
		{case TOUR_INFO:{
		show_tour_information(tour); 
		return true; 
		}
		
		case METE_TOUR:{
		//show_tour_destination(mete_tour, foto_mete); 
		return true;
		}
		
     	case VIAGGI_TOUR:{
     	//show_trip_tour(viaggi_tour,viaggio);
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



void show_tour_information(struct tour *tour)
{	
	printf("\n\n** Tour offerti  **\n\n"); 
	get_input("Inserisci il codice d'interesse: ", VARCHAR_LEN, tour->denominazionetour, false); 
	// seleziona i nominativi dei tour
	//do_select_tour(tour); 
	do_select_all_tour(tour); 
	// seleziona il tour 
	show_tour(tour); 
	
	
	/*char buffer[VARCHAR_LEN]; 
	//  lancio procedura select Tour tramite denominazione
	printf("Descrizione %s \n\n Accompagnatrice %s \n Costo bagaglio %f\n Costo assicurazione medica : %f",
			tour->descrizionetour, 
			tour->accompagnatrice,
			tour->bagaglio,
			tour->assicurazionemedica);*/
}

/*void show_tour_destination(struct mete_tour *mete_tour, struct foto_mete *foto_mete)
{	
	//select_tour(TOUR_SEL); TODO: Da verificare l'utilizzo di questa istruzione
	//clear_screen();
	printf("** Mete visitate dal tour **\n\n");
	//  lancio procedura select mete tramite denominazione tour nella tabella me-to per passare a mete e  conteggio delle stesse  tale conteggio viene inserito in COUNT inoltre deve effettuare una select su foto relative ed un ulteriore conteggio da inserire in COUNT_PIC 
	for(size_t i = 0; i < COUNT; i++) {
		printf("ID: %s \n %s\n Tipologia: %s \n Località di appartenenza: %s \n Categoria albergo: %s \n Orario di apertura: %s \n",
			mete_tour->mete_tour[i].idmeta,
			mete_tour->mete_tour[i].nomemeta,
			mete_tour->mete_tour[i].tipologiameta,
			mete_tour->mete_tour[i].localitadiappartenenza,
			mete_tour->mete_tour[i].categoriaalbergo,
			mete_tour->mete_tour[i].orariodiapertura
			);
			for (size_t j = 0; j < COUNT_PIC; j++){
				printf("%s    ", 
					foto_mete->foto_mete[j].foto); 
		}
	}

}

void show_trip_tour(struct viaggi_tour *viaggi_tour, struct viaggio *viaggio)
{
	//clear_screen(); 
	puts("** Inserire il periodo d'interesse **\n\n");

	while(true) {
		get_input("Inserisci la data di partenza [YYYY-MM-DD]: ", DATE_LEN, DATE_D, false);
		if(validate_date(viaggio->datadipartenzaviaggio))
			break; 
		fprintf(stderr, "Data errata !\n");
	}

	while(true) {
		get_input("Inserisci la data di ritorno [YYYY-MM-DD]: ", DATE_LEN, DATE_R, false);
		if(validate_date(viaggio->datadiritornoviaggio))
			break;
		fprintf(stderr, "Data errata !\n");
	}// procedura select viaggi in base a tour richiesto e date indicate ed inserisca il numero dei viaggi trovati in COUNT
	//clear_screen();
	char buffer[VARCHAR_LEN]; 
	printf("** Viaggi realtivi al tour %s **\n\n", buffer);
	for(size_t i = 0; i < COUNT; i++) {
		printf("Partenza %s Ritorno: %s  Prezzo: %sPosti disponibili: %s\n data annulamento: %s \n\n",
			viaggi_tour->viaggi_tour[i].datadipartenzaviaggio,
			viaggi_tour->viaggi_tour[i].datadiritornoviaggio,
			viaggi_tour->viaggi_tour[i].costodelviaggio,
			viaggi_tour->viaggi_tour[i].postidisponibili,
			viaggi_tour->viaggi_tour[i].datadiannullamento);
	}
 	
}

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
	if(	tour == NULL || viaggio == NULL || meta == NULL || servizio == NULL|| comfort == NULL || documentazionefotografica == NULL || camera == NULL ) 
		allocation_cstmr();
	while (true){
	sel = get_cstmr_action(); 
	if (!exe_cstmr_act(sel, tour,viaggio,  meta, servizio, comfort, modello, documentazionefotografica, camera))
		break; 
	}
}



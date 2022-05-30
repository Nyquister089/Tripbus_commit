#include <stdio.h>
#include"cliente.h"
#include "../utils/io.h"
#include "../utils/validation.h"

char * BUFFER [VARCHAR_LEN];
char * PIC_DEST [VARCHAR_LEN]; 
char * ANS [5]; 
char * DATE_D[DATE_LEN];
char * DATE_R[DATE_LEN];
size_t COUNT; 
size_t COUNT_PIC; 

int get_cstmr_action(void)
{
	char options[6] = {'1','2','3','4','5','6'};
	char op;
	clear_screen();
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

	op = multi_choice("Select an option", options, 6);
	return op - '1';
}

bool exe_cstmr_act(cstmr_act sel)
{
	switch (sel)
		{case TOUR_INFO:
		show_tour_information(struct tour *tour); 
		return; 
		
		case METE_TOUR:
		show_tour_destination(struct mete_tour *mete_tour, struct foto_mete *foto_mete); 
		return ;
     	
     		case VIAGGI_TOUR:
     		show_trip (struct viaggi_tour *viaggi_tour);
		return ; 

	 	case SERVIZI_ALBERGO:		
		show_service(struct servizi_albergo *servizi_albergo);
		return ;

	 	case COMFORT_MODELLO:
		show_comfort(struct comfort_mezzo *comfort_mezzo, struct elenco_modelli *elenco_modelli);

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

char* select_tour(struct tour *tour)
{   clear_screen();
	char tour_options[4] = {'1','2','3','4'}; 
	char t;  
	puts("** Seleziona il tour d'interesse  **\n\n");
	puts("1) Fuga da Tor Vergata");
	puts("2) Ingegneria estrema");
	puts("3) Il miraggio della laurea");
	puts("4) Mille splendidi crediti");
	t = multi_choice("Seleziona un opzione", tour_options, 4);
	return t - '1';// Return la denominazione del tour scelto
}

void show_tour_information(struct tour *tour)
{	BUFFER = select_tour(tour); 
	// procedura di select del tour in base alla scelta sopra menzionata 
	clear_screen();
	printf("** Dettagli tour: %s **\n\n", BUFFER);
	//  lancio procedura select Tour tramite denominazione
	printf("Descrizione %s \n\n Accompagnatrice %s \n Costo bagaglio %d \n Costo assicurazione medica : %d",
			tour.descrizionetour, 
			tour.accompagnatrice,
			tour.bagaglio,
			tour.assicurazionemedica);
}

void show_tour_destination(struct mete_tour *mete_tour, struct foto_mete *foto_mete)
{	BUFFER = select_tour(tour); 
	clear_screen();
	printf("** Mete visitate dal tour %s **\n\n", BUFFER);
	//  lancio procedura select mete tramite denominazione tour nella tabella me-to per passare a mete e  conteggio delle stesse  tale conteggio viene inserito in COUNT inoltre deve effettuare una select su foto relative ed un ulteriore conteggio da inserire in COUNT_PIC 
	for(size_t i = 0; i < COUNT; i++) {
		printf("%s\n Tipologia: %s \n Località di appartenenza: %s \n Categoria albergo: %s \n Orario di apertura: %s \n",
			mete_tour->mete_tour[i].nomemeta,
			mete_tour->mete_tour[i].tipologiameta,
			mete_tour->mete_tour[i].localitadiappartenenza,
			mete_tour->mete_tour[i].categoriaalbergo,
			mete_tour->mete_tour[i].orariodiapertura,
			mete_tour->mete_tour[i].idmeta);
			for (size_t j = 0; j < COUNT_PIC; j++){
				printf("%s    ", 
					foto_mete->foto_mete[j].foto); 
		}
	}
free(BUFFER);
}

void show_trip (struct viaggi_tour *viaggi_tour)
{	BUFFER = select_tour(tour); 
	clear_screen(); 
	puts("** Inserire il periodo d'interesse **\n\n");

	while(true) {
		get_input("Inserisci la data di partenza [YYYY-MM-DD]: ", DATE_LEN, DATE_D, false);
		if(validate_date(flight->giorno))
			break;
		fprintf(stderr, "Data errata !\n");
	}

	while(true) {
		get_input("Inserisci la data di ritorno [YYYY-MM-DD]: ", DATE_LEN, DATE_R, false);
		if(validate_date(flight->giorno))
			break;
		fprintf(stderr, "Data errata !\n");
	}// procedura select viaggi in base a tour richiesto e date indicate ed inserisca il numero dei viaggi trovati in COUNT
	clear_screen();
	printf("** Viaggi realtivi al tour %s **\n\n", BUFFER);
	for(size_t i = 0; i < COUNT; i++) {
		printf("Partenza %s Ritorno: %s  Prezzo: %d Posti disponibili: %d \n data annulamento: %s \n\n",
			viaggi_tour->viaggi_tour[i].datadipartenzaviaggio,
			viaggi_tour->viaggi_tour[i].datadiritornoviaggio,
			viaggi_tour->viaggi_tour[i].costodelviaggio,
			viaggi_tour->viaggi_tour[i].postidisponibili,
			viaggi_tour->viaggi_tour[i].dataannullamento,);
	}
	free(BUFFER); 	
}

void show_service(struct servizi_albergo *servizi_albergo)
{	clear_screen();
	get_input("** Inserire il nome dell'albergo d'interesse **\n\n", BUFFER, VARCHAR_LEN, false);
	//  lancio procedura select per individuare l'albergo d'interesse e restituisco i relativi servizi offerti, inserisco il numero degli ultimi nella variabile COUNT
	clear_screen(); 
	printf("** Servizi offerti da: %s \n\n", BUFFER);
	for(size_t i = 0; i < COUNT; i++) {
		printf("Nome servizio: %s \n Descrizione: %s \n\n",
			servizi_albergo->servizi_albergo[i].nomeservizio,
			servizi_albergo->servizi_albergo[i].descrizioneservizio); 

	}
	free(BUFFER); 
}

void show_comfort(struct comfort_mezzo *comfort_mezzo, struct elenco_modelli *elenco_modelli)
{	clear_screen();
	puts("** Elenco modelli **"); 
	for(size_t i = 0; i < COUNT; i++) {
		printf("%d) Modello :  %s Id Modello %s \n",
			i,
			elenco_modelli->elenco_modelli[i].nomemodello, 
			elenco_modelli->elenco_modelli[i].idmodello,
	}
	get_input("** Inserire l'id del modello d'interesse **\n\n", BUFFER, VARCHAR_LEN, false);
	//  lancio procedura select per individuare il modello d'interesse e restituisco i relativi servizi offerti, inserisco il numero degli ultimi nella variabile COUNT
	clear_screen(); 
	printf("** Comfort offerti dal bus modello : %s \n\n", BUFFER);
	for(i = 0; i < COUNT; i++) {
		printf("Nome comfort: %s \n Descrizione: %s \n\n",
			comfort_mezzo->comfort_mezzo[i].nomecomfort,
			comfort_mezzo->comfort_mezzo[i].descrizionecomfort); 
	}
	free(BUFFER); 
}

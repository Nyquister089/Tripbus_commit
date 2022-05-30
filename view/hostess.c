
#include <stdio.h>

#include "hostess.h"
#include "ins.h"
#include "upd.h"
#include "../utils/io.h"
#include "../utils/validation.h"

char *BUFFER[VARCHAR_LEN];
int NUM; 

int get_hstss_action(void)
{
	char options[6] = {'1','2','3','4','5','6'};
	char op;
			
	clear_screen();
	puts("*********************************");
	puts("*   INTERFACCIA HOSTESS    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consultare prenotazioni");
	puts("2) Inserire un nuovo cliente");
	puts("3) Inserire una nuova prenotazione");
	puts("4) Modifica posti disponibili per un viaggio");
	puts("5) Conferma prenotazione ed intestazione posti");
	puts("6) Esci");
	


	op = multi_choice("Select an option", options, 6);
	return op - '1';
}

bool exe_hstss_act(hstss_act sel)
{
	struct prenotazione *prenotazione;
	switch (sel)
		{case INSERT_CLIENTE:
		struct cliente *cliente; 
		insert_costumer(cliente); 
		return; 
		
		case INSERT_PRENOTAZIONE:
		insert_prenotation(prenotazione); 
		return ;
     	
     		case POSTI_VIAGGIO:
     		struct  viaggio *viaggio; 
     		update_trip_seat(viaggio);
		return ; 

	 	case CONFERMA_PRENOTAZIONE:		
		validate_prenotation (prenotazione); 
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

void show_prenotation_details(struct prenotazione *prenotazione ) // Procedura visualizzazione dettagli prenotazione
{clear_screen(); 
 get_input("Inserisci il numero di prenotazione : ", VARCHAR_LEN, BUFFER, false);
 // procedura di select prenotazione
 clear_screen(); 
 printf("** Dettagli prenotazione **");
 printf("Penotazione numero: %d  E-mail cliente: %s \n Data di prenotazione: %s \n Data di conferma: %s \n Data Saldo: %s \n",
	prenotazione->numerodiprenotazione, 
	prenotazione->clienteprenotante,
	prenotazione->datadiprenotazione, 
	prenotazione->datadiconferma, 
	prenotazione->datasaldo); 
}

void update_trip_seat(struct  viaggio *viaggio) // Procedura modifica posti dipsonibili per viaggio 
{clear_screen(); 
 get_input("Inserisci il codice del viaggio : ", NUM_LEN, NUM , false);
 //procedura select viaggio
 clear_screen(); 
 printf("**  Dettagli Viaggio : %d", NUM); 
 printf("Tour : %s \n Posti disponibili: %d \n Data annullamento: %d \n ",
 		viaggio->tourassociato, 
		viaggio->postidisponibili, 
 		viaggio->dataannullamento); 
 get_input ("Inserisci i nuovi posti disponibili :", NUM_LEN , viaggio->postidisponibili, false); 

}

void validate_prenotation(struct prenotazione *prenotazione)
{
	clear_screen();
	printf("** Procedura conferma prenotazione **\n\n");
	get_input("Inserisci numero d'interesse : ", VARCHAR_LEN , BUFFER, false); 
    // procedura di select
	printf("Numero:  %s \n  E-mail cliente: %s \n Data di prenotazione: %s \n Data di conferma: %s \n Data di saldo: %s \n  ", 
		prenotazione->numerodiprenotazione,
		prenotazione->clienteprenotante,
		prenotazione->datadiprenotazione,
		prenotazione->datadiconferma,
		prenotazione->datasaldo
		);
 	bool answer_update = yes_or_no("\n\n Vuoi confermare questa prenotazione? (s/n) ",'s','n',false,false);
	if(!answer_update) {
		return;
		}
	while(true){
		get_input("Modifica data di conferma [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datadiconferma, false);
		if(validate_date(prenotazione->datadiconferma))
			break;
		fprintf(stderr, "Data errata!\n");
		}
	while(true){
		get_input("Modifica data di saldo [YYYY-DD-MM]: ", DATE_LEN, prenotazione->datasaldo, false);
		if(validate_date(prenotazione->datasaldo))
			break;
		fprintf(stderr, "Data errata!\n");
		}
}
//int main ()
void run_hstss_interface (void)
{ 	hstss_act sel; 
	while (true){
	get_hstss_action(); 
	if (!exe_hstss_act(sel))
		break; 
	
	}
}	



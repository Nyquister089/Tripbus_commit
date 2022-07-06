
#include <stdio.h>

#include "hostess.h"
#include "ins.h"
#include "show.h"

#include "../utils/io.h"
#include "../utils/validation.h"

struct cliente *cliente_hstss; 
struct prenotazione *prenotazione_hstss;
struct postoprenotato *postoprenotato_hstss;
struct  viaggio *viaggio_hstss;
struct associata * associata_hstss;

int allocation_hstss(void)
{
	cliente_hstss = malloc(sizeof(struct cliente)); 
	if(cliente_hstss == NULL)
		{printf("Fallimento malloc su cliente (hostess) \n\n"); 
		 return -1; 
		}
	prenotazione_hstss = malloc(sizeof(struct prenotazione)); 
	if(prenotazione_hstss == NULL)
		{printf("Fallimento malloc su prenotazione (hostess) \n\n");
		 return -1; 
		}
	postoprenotato_hstss = malloc(sizeof(struct postoprenotato));
	if(postoprenotato_hstss == NULL)
		{printf("Fallimento malloc su postoprenotato (hostess) \n\n"); 
		 return -1; 
		}
	viaggio_hstss = malloc(sizeof(struct viaggio)); 
	if(viaggio_hstss == NULL)
		{printf("Fallimento malloc su viaggio (hostess) \n\n"); 
		 return -1;
		}
	associata_hstss = malloc(sizeof(struct associata));
	if(associata_hstss == NULL)
		{printf("Fallimento malloc associata (hostess) \n\n"); 
		 return -1; 
		 }
}

void show_prenotation_details(void ) // Procedura visualizzazione dettagli prenotazione
{	
	char buff[VARCHAR_LEN]; 
	printf("** Procedura visualizzazione dettagli prenotazione **\n\n"); 
	get_input("Inserisci il numero di prenotazione : ", VARCHAR_LEN, buff, false);
	prenotazione_hstss->numerodiprenotazione = atoi(buff); 
	do_select_reservation(prenotazione_hstss); 
 	show_reservation( prenotazione_hstss); 
}

void mod_trip_seat(void) // Procedura modifica posti dipsonibili per viaggio 
{
	
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura modifica posti viaggio **\n\n"); 
	show_trip (viaggio_hstss);
	bool ans = yes_or_no("\n\n Vuoi modificare i posti disponibili per questo viaggio? (s/n) ",'s','n',false,false);
	if(!ans) {
		return;
	}

 	get_input ("Inserisci i nuovi posti disponibili :", NUM_LEN , buffer, false); 
	viaggio_hstss->postidisponibili = atoi(buffer); 

	do_update_trip_seat(viaggio_hstss); 
}

void validate_reservation(void)
{
	 
	printf("** Procedura conferma prenotazione **\n\n"); 
	show_reservation(prenotazione_hstss); 

 	bool ans = yes_or_no("\n\n Vuoi confermare questa prenotazione? (s/n) ",'s','n',false,false);
	if(!ans) {
		return;
		}

	while(true){
		get_input("\nModifica data di conferma [YYYY-MM-DD]: ", DATE_LEN, prenotazione_hstss->datadiconferma, false);
		if(validate_date(prenotazione_hstss->datadiconferma))
			break;
		fprintf(stderr, "Data errata!\n");
		}

	while(true){
		get_input("\nModifica data di saldo [YYYY-MM-DD]: ", DATE_LEN, prenotazione_hstss->datasaldo, false);
		if(validate_date(prenotazione_hstss->datasaldo))
			break;
		fprintf(stderr, "Data errata!\n");
		}
		do_validate_reservation(prenotazione_hstss);
		bool seat_ans, association_ans;   

	do {
		printf("\n\n** Associa un passeggero alla prenotazione ** \n\n"); 

		postoprenotato_hstss->prenotazioneassociata = prenotazione_hstss->numerodiprenotazione; 
		printf(" Numero di prenotazione hostess %d \n", postoprenotato_hstss->prenotazioneassociata);

		ins_seat(postoprenotato_hstss); 

		ans = yes_or_no("\n\n Vuoi associare una camera a questo passeggero? (s/n) ",'s','n',false,false);
		if (ans)
			do{	printf("** Associa camera al passeggero ** ");
			 	associata_hstss->ospite = postoprenotato_hstss->numerodiposto; 
				ins_association(associata_hstss); 
				association_ans= yes_or_no("\n\n Vuoi associare un'altra camera a questo passeggero? (s/n) ",'s','n',false,false);
			}while(association_ans);
		seat_ans =yes_or_no("\n\n Vuoi associare un'altro passeggero a questa prenotazione ? (s/n) ",'s','n',false,false);
	} while(seat_ans); 

}

void update_d_doc(void)
{ 	
	printf("\n\n** Procedura di modifica data documenti cliente **\n\n");
	show_costumer (cliente_hstss); 
    bool ans = yes_or_no("\n\n Vuoi modificare la data documentazione di questo cliente? (s/n) ",'s','n',false,false);
	if(!ans) {
		return;
	}
	while(true){
		get_input("\nModifica l'ultima data d'invio dei documuenti [YYYY-MM-DD]: ", DATE_LEN, cliente_hstss->datadocumentazione, false);
		if(validate_date(cliente_hstss->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	do_update_data_doc(cliente_hstss); 

}

int get_hstss_action(void)
{
	char options[7] = {'1','2','3','4','5','6','7'};
	char op;
	
	puts("*********************************");
	puts("*   INTERFACCIA HOSTESS    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consultare prenotazioni");
	puts("2) Inserire un nuovo cliente");
	puts("3) Inserire una nuova prenotazione");  
	puts("4) Modifica posti disponibili per un viaggio");
	puts("5) Conferma prenotazione ed intestazione posti");
	puts("6) Modificare la data di invio degli ultimi documenti di un cliente"); 
	puts("7) Esci");

	op = multi_choice("Scegli un opzione", options, 7);

	return op -'1'; 
}

bool exe_hstss_act(char sel)
{	

	switch (sel)
		{	
			case INFO_PRENOTAZIONI: {
				show_prenotation_details(); 
				return true;
				}
			case INSERT_CLIENTE:{
				ins_costumer(cliente_hstss); 
				return true; 
				}
		
			case INSERT_PRENOTAZIONE:{
				ins_prenotation(prenotazione_hstss); 
				return true;
				}
     		case POSTI_VIAGGIO:{
     			mod_trip_seat();
				return true; 
				}
			case CONFERMA_PRENOTAZIONE:{
				validate_reservation (); 
				return true;
		 		}

			case UPDATE_DATA_DOC:{
				update_d_doc(); 
				return true;
				}
		
			case QUIT_HSST: 
				return false; 
		
	}
	return true;
}




void run_hstss_interface (void)
{ 	
	char sel;
				
	if(	cliente_hstss == NULL || prenotazione_hstss == NULL || postoprenotato_hstss == NULL ||viaggio_hstss == NULL||associata_hstss == NULL) {
		allocation_hstss();
		printf("\n\nAllocazione avvenuta.\n\n"); }

	while (true){
	sel = get_hstss_action(); 
	if (!exe_hstss_act(sel))
		break; 
	}

}	

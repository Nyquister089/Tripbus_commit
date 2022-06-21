
#include <stdio.h>

#include "hostess.h"
#include "ins.h"
#include "show.h"

#include "../utils/io.h"
#include "../utils/validation.h"


struct cliente *cliente; 
struct prenotazione *prenotazione;
struct postoprenotato *postoprenotato;
struct  viaggio *viaggio;
struct associata * associata;

void  allocation_hstss(void)
{
	cliente = malloc(sizeof(struct cliente)); 
	if(cliente == NULL)
		{printf("Fallimento malloc su cliente (hostess) \n\n"); 
		 exit(0); 
		}
	prenotazione = malloc(sizeof(struct prenotazione)); 
	if(prenotazione == NULL)
		{printf("Fallimento malloc su prenotazione (hostess) \n\n");
		 exit(0); 
		}
	postoprenotato = malloc(sizeof(struct postoprenotato));
	if(postoprenotato == NULL)
		{printf("Fallimento malloc su postoprenotato (hostess) \n\n"); 
		 exit(0); 
		}
	viaggio = malloc(sizeof(struct viaggio)); 
	if(viaggio == NULL)
		{printf("Fallimento malloc su viaggio (hostess) \n\n"); 
		 exit(0);
		}
	associata = malloc(sizeof(struct associata));
	if(associata == NULL)
		{printf("Fallimento malloc associata (hostess) \n\n"); 
		 exit(0); 
		 }
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

bool exe_hstss_act(char sel, struct cliente *cliente,struct prenotazione * prenotazione,
	struct postoprenotato *postoprenotato, struct viaggio *viaggio, struct associata *associata)
{	

	switch (sel)
		{	
			case INFO_PRENOTAZIONI: {
				show_prenotation_details(prenotazione); 
				return true;
				}
			case INSERT_CLIENTE:{
				ins_costumer(cliente); 
				return true; 
				}
		
			case INSERT_PRENOTAZIONE:{
				ins_prenotation(prenotazione); 
				return true;
				}
     		case POSTI_VIAGGIO:{
     			mod_trip_seat(viaggio);
				return true; 
				}
			case CONFERMA_PRENOTAZIONE:{
				validate_reservation (prenotazione, postoprenotato, associata); 
				return true;
		 		}

			case UPDATE_DATA_DOC:{
				update_d_doc(cliente); 
				return true;
				}
		
			case QUIT_HSST: 
				return false; 
		
	}
	return true;
}

void show_prenotation_details(struct prenotazione *prenotazione ) // Procedura visualizzazione dettagli prenotazione
{	
	char buff[VARCHAR_LEN]; 
	printf("** Procedura visualizzazione dettagli prenotazione **\n\n"); 
	get_input("Inserisci il numero di prenotazione : ", VARCHAR_LEN, buff, false);
	prenotazione->numerodiprenotazione = atoi(buff); 
	do_select_reservation(prenotazione); 
 	show_reservation( prenotazione); 
}

void mod_trip_seat(struct  viaggio *viaggio) // Procedura modifica posti dipsonibili per viaggio 
{
	
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura modifica posti viaggio **\n\n"); 
 	get_input("Inserisci il codice del viaggio : ", VARCHAR_LEN, buffer, false);
	viaggio->idviaggio = atoi(buffer);

 	do_select_trip(viaggio);
	show_trip (viaggio);

	bool ans = yes_or_no("\n\n Vuoi modificare i posti disponibili per questo viaggio? (s/n) ",'s','n',false,false);
	if(!ans) {
		return;
	}

 	get_input ("Inserisci i nuovi posti disponibili :", NUM_LEN , buffer, false); 
	viaggio->postidisponibili = atoi(buffer); 

	do_update_trip_seat(viaggio); 
}

void validate_reservation(struct prenotazione *prenotazione, struct postoprenotato *postoprenotato, struct associata *associata)
{
	char buff[NUM_LEN]; 
	printf("** Procedura conferma prenotazione **\n\n");
	get_input("Inserisci numero d'interesse : ", NUM_LEN , buff, false); 
	prenotazione->numerodiprenotazione = atoi(buff); 

    do_select_reservation(prenotazione); 
	show_reservation(prenotazione); 

 	bool ans = yes_or_no("\n\n Vuoi confermare questa prenotazione? (s/n) ",'s','n',false,false);
	if(!ans) {
		return;
		}

	while(true){
		get_input("\nModifica data di conferma [YYYY-MM-DD]: ", DATE_LEN, prenotazione->datadiconferma, false);
		if(validate_date(prenotazione->datadiconferma))
			break;
		fprintf(stderr, "Data errata!\n");
		}

	while(true){
		get_input("\nModifica data di saldo [YYYY-MM-DD]: ", DATE_LEN, prenotazione->datasaldo, false);
		if(validate_date(prenotazione->datasaldo))
			break;
		fprintf(stderr, "Data errata!\n");
		}
		do_validate_reservation(prenotazione);
		bool seat_ans, association_ans;   

	do {
		printf("\n\n** Associa un passeggero alla prenotazione ** \n\n"); 

		postoprenotato->prenotazioneassociata = prenotazione->numerodiprenotazione; 
		printf(" Numero di prenotazione hostess %d \n", postoprenotato->prenotazioneassociata);

		ins_seat(postoprenotato); 

		ans = yes_or_no("\n\n Vuoi associare una camera a questo passeggero? (s/n) ",'s','n',false,false);
		if (ans)
			do{	printf("** Associa camera al passeggero ** ");
			 	associata->ospite = postoprenotato->numerodiposto; 
				ins_association(associata); 
				association_ans= yes_or_no("\n\n Vuoi associare un'altra camera a questo passeggero? (s/n) ",'s','n',false,false);
			}while(association_ans);
		seat_ans =yes_or_no("\n\n Vuoi associare un'altro passeggero a questa prenotazione ? (s/n) ",'s','n',false,false);
	} while(seat_ans); 

}

void update_d_doc(struct cliente  *cliente)
{ 
	printf("\n\n** Procedura di modifica data documenti cliente **\n\n");
	get_input("Inserisci la mail d'interesse : ", VARCHAR_LEN , cliente->emailcliente, false);
	printf("\n\n");  

    do_select_costumer(cliente); 
	show_costumer (cliente); 

    bool ans = yes_or_no("\n\n Vuoi modificare la data documentazione di questo cliente? (s/n) ",'s','n',false,false);
	if(!ans) {
		return;
	}
	while(true){
		get_input("\nModifica l'ultima data d'invio dei documuenti [YYYY-MM-DD]: ", DATE_LEN, cliente->datadocumentazione, false);
		if(validate_date(cliente->datadocumentazione))
			break;
		fprintf(stderr, "Data errata!\n");
	}
	do_update_data_doc(cliente); 

}


void run_hstss_interface (void)
{ 	
	char sel;  
	struct cliente *cliente; 
	struct prenotazione *prenotazione;
	struct postoprenotato *postoprenotato;
	struct  viaggio *viaggio;
	struct associata * associata;
				
	if(	cliente == NULL || prenotazione == NULL || postoprenotato == NULL ||viaggio == NULL||associata == NULL) 
		allocation_hstss(); 

	while (true){
	sel = get_hstss_action(); 
	if (!exe_hstss_act(sel, cliente, prenotazione,postoprenotato, viaggio, associata))
		break; 
	}

}	


#include <stdio.h>
#include "hostess.h"
#include "ins.h"

#include "../utils/io.h"
#include "../utils/validation.h"

struct cliente *cliente; 
struct prenotazione *prenotazione;
struct postoprenotato *postoprenotato;
struct  viaggio *viaggio; 
struct associata * associata;

void  allocation_hstss(void)
{
	cliente = malloc(sizeof(struct cliente)*8); 
	prenotazione = malloc(sizeof(struct prenotazione)*8); 
	postoprenotato = malloc(sizeof(struct postoprenotato)*8);
	viaggio = malloc(sizeof(struct viaggio)*8); 
	associata = malloc(sizeof(struct associata)*8);
}

int get_hstss_action(void)
{
	char options[8] = {'1','2','3','4','5','6','7','8'};
	char op;
	
	puts("*********************************");
	puts("*   INTERFACCIA HOSTESS    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consultare prenotazioni");
	puts("2) Inserire un nuovo cliente");
	puts("3) Inserire una nuova prenotazione"); 
	puts("4) Inserire un nuovo posto prenotato"); 
	puts("5) Modifica posti disponibili per un viaggio");
	puts("6) Conferma prenotazione ed intestazione posti");
	puts("7) Modificare la data di invion ultimi documenti di un cliente"); 
	puts("8) Esci");

	op = multi_choice("Select an option", options, 8);

	return op -'1'; 
}

bool exe_hstss_act(char sel, 
	struct cliente *cliente,
	struct prenotazione * prenotazione,
	struct postoprenotato *postoprenotato, 
	struct viaggio *viaggio, 
	struct associata *associata)
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
     		case INSERT_POSTPRENOTATO: {
				ins_seat(postoprenotato); 
				return true; 
				}
     		case POSTI_VIAGGIO:{
     			mod_trip_seat(viaggio);
				return true; 
				}
			case CONFERMA_PRENOTAZIONE:{
				validate_prenotation (prenotazione, postoprenotato, associata); 
				return true;
		 		}

			case UPDATE_DATA_DOC:{
				update_d_doc(cliente); 
				return true;
				}
		
			case QUIT:
		// gestire l'uscita dal Db (disconnessione e ritorno a schermata iniziale) 
		return false; 
		
	break;
		/*default:
			fprintf(stderr, "Il carattere digitato non corrisponde a nessuna azione \n");
			exit(EXIT_FAILURE);*/
	}

	return true;
}

void show_prenotation_details(struct prenotazione *prenotazione ) // Procedura visualizzazione dettagli prenotazione
{	
	////clear_scren(); 
	char buffer[VARCHAR_LEN]; 
	get_input("Inserisci il numero di prenotazione : ", VARCHAR_LEN, buffer, false);
	printf("\n\n"); 
	do_select_reservation(prenotazione); 
	
 	printf("\n\n** Dettagli prenotazione **\n\n");
 	printf("Penotazione numero: %s  E-mail cliente: %s \n Data di prenotazione: %s \n Data di conferma: %s \n Data Saldo: %s \n",
		prenotazione->numerodiprenotazione, 
		prenotazione->clienteprenotante,
		prenotazione->datadiprenotazione, 
		prenotazione->datadiconferma, 
		prenotazione->datasaldo); 
}

void mod_trip_seat(struct  viaggio *viaggio) // Procedura modifica posti dipsonibili per viaggio 
{
	////clear_scren(); 
	char buffer[VARCHAR_LEN]; 
 	get_input("Inserisci il codice del viaggio : ", VARCHAR_LEN, buffer, false);
	
	viaggio->idviaggio = atoi(buffer);

 	do_select_trip(viaggio);
 	////clear_scren(); 
 	printf("\n\n**  Dettagli Viaggio ** \n\n"); 
 	printf(" Tour : %s \n Posti disponibili: %d \n Data annullamento: %s \n ",
 		viaggio->tourassociato, 
		viaggio->postidisponibili, 
 		viaggio->datadiannullamento); 
 	get_input ("Inserisci i nuovi posti disponibili :", NUM_LEN , buffer, false); 

	viaggio->postidisponibili = atoi(buffer); 

	do_update_trip_seat(viaggio); 
}

void validate_prenotation(struct prenotazione *prenotazione, struct postoprenotato *postoprenotato, struct associata *associata)
{
	////clear_scren();
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura conferma prenotazione **\n\n");
	get_input("Inserisci numero d'interesse : ", VARCHAR_LEN , buffer, false); 
    do_select_reservation(prenotazione); 
	printf("\nNumero:  %s \n  E-mail cliente: %s \n Data di prenotazione: %s \n Data di conferma: %s \n Data di saldo: %s \n  ", 
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
		printf("** Associa un passeggero alla prenotazione ** \n"); 
		ins_seat(postoprenotato); 
		do{	printf("** Associa camera al passeggero ** "); 
			ins_association(associata); 
			association_ans= yes_or_no("\n\n Vuoi associare un'altra camera a questo passeggero? (s/n) ",'s','n',false,false);
		
		}while(association_ans);
		
		seat_ans = yes_or_no("\n\n Vuoi associare un altro passeggero a questa prenotazione? (s/n) ",'s','n',false,false);
		} while(seat_ans); 

}

void update_d_doc(struct cliente  *cliente)
{
	//clear_scren();
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura di modifica data documenti cliente **\n\n");
	get_input("Inserisci la mail d'interesse : ", VARCHAR_LEN , cliente->emailcliente, false);
	printf("\n\n");  

    do_select_costumer(cliente); 
	
	printf("\nE-mail:  %s \n Nome: %s \n Cognome: %s \n Indirizzo: %s \n Codice fiscale: %s \n Recapito telefonico: %s \n Fax: %s \n Data documentazione: %s \n", 
		cliente->emailcliente,
		cliente->nomecliente,
		cliente->cognomecliente,
		cliente->indirizzocliente,
		cliente->codicefiscale,
		cliente->recapitotelefonico,
		cliente->fax,
		cliente->datadocumentazione
		);
    bool answer_update = yes_or_no("\n\n Vuoi modificare la data documentazione di questo cliente? (s/n) ",'s','n',false,false);
	if(!answer_update) {
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
				
	if(	cliente == NULL || prenotazione == NULL || postoprenotato == NULL ||viaggio == NULL||associata == NULL) 
		allocation_hstss(); 

	while (true){
		printf("Get hostess action\n\n"); 
	sel = get_hstss_action(); 
	if (!exe_hstss_act(sel, cliente, prenotazione,postoprenotato, viaggio, associata))
		break; 
	}

}	

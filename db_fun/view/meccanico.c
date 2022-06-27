#include <stdio.h>

#include "meccanico.h"
#include "ins.h"
#include "show.h"
#include "../utils/io.h"
#include "../utils/validation.h"

struct revisione *revisione_mch; 
struct sostituito *sostituito_mch; 
struct ricambio *ricambio_mch; 

int allocation_mch(void)
{
	revisione_mch = malloc(sizeof( struct revisione)); 
	if(revisione_mch == NULL){
		printf("Impossibile eseguire malloc su revisone\n"); 
		return -1; 
	}

	sostituito_mch = malloc(sizeof(struct sostituito));
	if(sostituito_mch == NULL){
		printf("Impossibile eseguire malloc su sostituito\n"); 
		return -1;
	} 

	ricambio_mch = malloc(sizeof(struct ricambio));
	if(ricambio_mch == NULL){
		printf("Impossibile eseguire malloc su ricambio\n"); 
		return -1;
	}
}

void selection (void)
{
char buff[NUM_LEN];
get_input("Inserisci il codice ricambio : ", VARCHAR_LEN, buff, false); 
revisione_mch->idrevisione = atoi(buff);
do_select_review(revisione_mch); 
show_review(revisione_mch); 
}


int get_mch_action(void)
{
	char options[3] = {'1','2','3'};
	char op;
			
	puts("*********************************");
	puts("*   INTERFACCIA MECCANICO    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Inserisci una nuova revisione");
	puts("2) Consulta le revisioni scadute");
	puts("3) Esci");

	op = multi_choice("Select an option", options,3);
	return op - '1';
}

bool exe_mch_act(mch_act sel)
{	
	 
	switch (sel){
		case INS_REVISIONE:{
			ins_review(revisione_mch, sostituito_mch, ricambio_mch); 
		return true;   
		}
		
		case PIANIFICA_REVISIONE: {
			show_expired_review(); 
		return true; 
		}
		case QUIT_MCH:
		return false;
		
	break;
	}

	return true; 
}

void run_mch_interface (void)
{ 	
	char sel; 
	if(revisione_mch == NULL || sostituito_mch == NULL || ricambio_mch == NULL) 
		allocation_mch(); 
	while (true){
	sel = get_mch_action(); 
	if(!exe_mch_act(sel))
		break; 
	
	}
}




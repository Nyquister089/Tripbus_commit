#include <stdio.h>

#include "meccanico.h"
#include "ins.h"
#include "show.h"
#include "../utils/io.h"
#include "../utils/validation.h"

struct revisione *revisione_mch; 

int allocation_mch(void)
{
	revisione_mch = malloc(sizeof( struct revisione)); 
	if(revisione_mch == NULL){
		printf("Impossibile eseguire malloc su revisone"); 
		return -1; 
	}
}


int get_mch_action(void)
{
	char options[9] = {'1','2','3','4','5','6','7','8','9'};
	char op;
			
	//clear_screen();
	puts("*********************************");
	puts("*   INTERFACCIA MECCANICO    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Inserisci una nuova revisione");
	puts("2) Consulta le revisioni scadute");
	puts("3) Inserire una revisione effettuata");
	puts("4) Inserire un nuovo modello");
	puts("5) Inserire un nuovo ricambio");
	puts("6) Inserire un nuovo mezzo");
	puts("7) Inserire nuovi tagliandi");
	puts("8) Modificare la quantita' dei ricambi presenti");
	puts("9) Esci");

	op = multi_choice("Select an option", options, 9);
	return op - '1';
}

bool exe_mch_act(mch_act sel)
{	
	 
	switch (sel){
		case INS_REVISIONE:{
			ins_review(revisione_mch); 
		return true;   
		}
		
		case PIANIFICA_REVISIONE: {
			show_expired_review(); 
		return true; 
		}
 
		case INSERT_MODELLO:{
		struct modello *modello;
		//ins_model (modello); 
		return true;   
		}
     	
     	case INSERT_RICAMBIO:{
     	//ins_sparepart(ricambio);
		return true; 
		 }

	 	case INSERT_MEZZO:{
	 	struct mezzo *mezzo;		
		//ins_bus(mezzo); 
		return true;  
		 }

		case INSERT_TAGLIANDO:	{
		struct tagliando *tagliando;	
		//ins_certify(tagliando); 
		return true; 
		}
		
		case MODIFICA_RICAMBIO:	{
		//update_sparepart_number (ricambio);
		return true; 
		}
		
		case QUIT_MCH:
		return false;
		
	break;
	}

	return true; 
}



/*
void show_sparepart (struct ricambio *ricambio) // procedura visualizazzione ricambio
{
	clear_screen();
	char buffer[VARCHAR_LEN];  
 	printf("** Procedura consultazione magazzino **\n\n");
 	get_input("Inserisci il codice d'interesse : ", VARCHAR_LEN , buffer, false); 
    // procedura di select
	printf(" Codice:  %s \n  Costo : %s \n Quantità di riordino: %s \n Descrizione: %s \n Scorta minima: %s \n Quantità in magazzino: %s \n  ", 
		ricambio->codice,
		ricambio->costounitario,
		ricambio->quantitadiriordino,
		ricambio->descrizione,
		ricambio->scortaminima,
		ricambio->quantitainmagazzino
		);
}

void update_sparepart_number(struct ricambio *ricambio)
{	
	clear_screen();
	char buffer[VARCHAR_LEN]; 
	printf("** Procedura di modifica quantità ricambio **\n\n");
	get_input("Inserisci il codice d'interesse : ", VARCHAR_LEN , buffer, false); 
    // procedura di select
	printf(" Codice:  %s \n  Costo : %s \n Quantità di riordino: %s \n Descrizione: %s \n Scorta minima: %s \n Quantità in magazzino: %s \n  ", 
		ricambio->codice,
		ricambio->costounitario,
		ricambio->quantitadiriordino,
		ricambio->descrizione,
		ricambio->scortaminima,
		ricambio->quantitainmagazzino
		);
	bool answer_update = yes_or_no("\n\n Vuoi modificare il numero dei pezzi presenti in magazzino? (s/n)",'s','n',false,false);
	if(!answer_update) {
		return;
		}
	get_input("Modifica quantità di pezzi disponili: ", NUM_LEN, ricambio-> quantitainmagazzino, false);
}*/
void run_mch_interface (void)
{ 	
	char sel; 
	if(revisione_mch == NULL) 
		allocation_mch(); 
	while (true){
	sel = get_mch_action(); 
	if(!exe_mch_act(sel))
		break; 
	
	}
}




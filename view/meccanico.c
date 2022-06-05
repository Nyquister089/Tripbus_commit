#include <stdio.h>

#include "meccanico.h"
#include "ins.h"
#include "../utils/io.h"
#include "../utils/validation.h"

#define KM 50000; 

int get_mch_action(void)
{
	char options[9] = {'1','2','3','4','5','6','7','8','9'};
	char op;
			
	clear_screen();
	puts("*********************************");
	puts("*   INTERFACCIA MECCANICO    *");
	puts("*********************************\n");
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Consultare le revisioni scadute");
	puts("2) Consultare la presenza di un ricambio in magazzino");
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
	struct ricambio *ricambio;
	 
	switch (sel)
		{case REVISIONI_SCADUTE:{
		struct revisioni_scadute *revisioni_scadute;
		show_expired_revisions (revisioni_scadute);
		return true;   
		}
		
		case CONSULTA_MAGAZZINO: {
		show_sparepart (ricambio);
		return true; 
		}
 
		case INSERT_MODELLO:{
		struct modello *modello;
		insert_model (modello); 
		return true;   
		}
     	
     	case INSERT_RICAMBIO:{
     	insert_sparepart(ricambio);
		return true; 
		 }

	 	case INSERT_MEZZO:{
	 	struct mezzo *mezzo;		
		insert_bus(mezzo); 
		return true;  
		 }

		case INSERT_TAGLIANDO:	{
		struct tagliando *tagliando;	
		insert_certify(tagliando); 
		return true; 
		}
		
		case MODIFICA_RICAMBIO:	{
		update_sparepart_number (ricambio);
		return true; 
		}
		
		case QUIT:
		return false;
		
	break;
		default:
			fprintf(stderr, "Il carattere digitato non corrisponde a nessuna azione \n");
			exit(EXIT_FAILURE);
	}

	return true; 
}


void show_expired_revisions (struct revisioni_scadute *revisioni_scadute) // Procedura visualizazzione revisioni scadute
{clear_screen();
	int count; 
	printf("** Ecco i mezzi le cui revisioni risultano in scadenza o scadute **\n\n");
	// eseguire una select che utilizzi come parametri sia la data (revisione annuale) e sia il chilometraggio dei mezzi presenti in archivio(confrontandolo con il km segnato sulla revisione) e conti il numero di mezzi che rispettano i parametri ed inserisca tale numero in COUNT 
for(size_t i = 0; i < count; i++) {
		printf("Targa mezzo: %s Data ultima revisione %s \n\n",
			revisioni_scadute->revisioni_scadute[i].mezzorevisionato,
			revisioni_scadute->revisioni_scadute[i].datafine);
	}	
}

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
}
void run_mch_interface (void)
{ 	
	mch_act sel; 
	while (true){
	get_mch_action(); 
	if(!exe_mch_act(sel))
		break; 
	
	}
}



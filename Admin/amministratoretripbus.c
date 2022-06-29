#include <stdio.h>
// DA REALIZZARE: DELETE ED UPDATE
#include "manager.h"

#include "../utils/io.h"
#include "../utils/validation.h"

int CODE_OP[3]; 

int get_admin_section(void) //Preleva il codice dell' insieme di tabelle su cui si intende lavorare 
{	char options[5] = {'1','2','3','4','5'};
	char op; 
	clear_screen();
	puts("*********************************");
	puts("*   INTERFACCIA AMMINISTRATORE    *");
	puts("*********************************\n");
	puts("*** In quale ambito ? ***\n");
	puts("1) Gestione dipendenti");// riporta direttamente alla tabella dipendenti
	puts("2) Gestione tour");
	puts("3) Gestione officina");
	puts("4) Gestione Clienti");
	puts("5) Esci");

	op = multi_choice("Seleziona un'opzione", options, 5);
	return op - '1';

}

int get_admin_action(void) // Preleva il codice dell'operazione da eseguire 
{	char options[4] = {'1','2','3','4'};
	char op; 
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Inserimento");
	puts("2) Modifica");
	puts("3) Cancellazione");
	puts("4) Esci");
	op = multi_choice("Seleziona un'opzione", options, 4);
	return op - '1';
}


int tour_section(void) //sezione tour
{	int num_op = 8; 
	char options[num_op] = {'1','2','3','4','5','6','7','8'};

		puts("*** Su quale tabella della gestione tour? ***\n");
		puts("1) Tour");
		puts("2) Viaggio");
		puts("3) Meta");
		puts("4) Visita");
		puts("5) Camera"); 
		puts("6) Località"); 
		puts("7) Mappa")
		puts("8) Esci");
		op = multi_choice("Seleziona un'opzione", options, num_op);
		return op - '1';
}


int workshop_section(void) // sezione officina 
 {	int num_op = 6;
		char options[num_op] = {'1','2','3','4','5','6'};

		 puts("*** Su quale tabella della gestione officina? ***\n");
	 	 puts("1) Modello ");
	 	 puts("2) Mezzo");
	 	 puts("3) Ricambio");
		 puts("4) Revisione");
		 puts("5) Tagliando");
		 puts("6) Esci");
		 op = multi_choice("Seleziona un'opzione", options, num_op);
		 return op - '1';
}


int costumer_section(void) // sezione clienti
{	num_op = 4;
	char options[num_op] = {'1','2','3','4'};
		 puts("*** Su quale tabella della gestione clienti? ***\n");
		 puts("1) Cliente");
		 puts("2) Prenotazione");
		 puts("3) Posto prenotato");
		 puts("4) Esci");
		 op = multi_choice("Seleziona un'opzione", options, num_op);
		 return op - '1';
}



int get_admin_table(void) //preleva il codice della tablla su cui si vuole eseguire l'operazione  
{	clear_screen();
	puts("*********************************");
	puts("*   INTERFACCIA AMMINISTRATORE    *");
	puts("*********************************\n");
	char op; 
   
	switch (COD_OP[1])
		{case 1:	//Dipendenti 
		op = '1'; 
		return op;
     	
     	case 2:		//Tour
     	op = tour_section(); 
		return op-'1'; 

	 	case 3:		//Officina
	 	op = workshop_section(); 
		return op-'1';

	 	case 4:		//Clienti
		op = costumer_section(); 
		return op-'1'; 
}

// Prevedere l'inserimento del codice d'uscita

/**
 * Funzione d'avvio
 */
}

void run_action(void) 
{	clear_screen();
	COD_OP[1]=get_admin_section();// 1= dipendenti, 2= tour, 3= officina, 4= clienti
	COD_OP[2]=get_admin_table(); //1 = Dipendenti, 
	COD_OP[3]=get_admin_action();// 1 = insert, 2 = Update, 3 = Delete 
	puts("*********************************");
	puts("*   INTERFACCIA AMMINISTRATORE    *");
	puts("*********************************\n");
	char op; 
	switch(GESTIONE)
		{
			case 1:								 //Dipendenti
			switch(COD_OP[3])					 //Operazione
			{
				case 1: 
					insert_employee(dipendente);
				case 2: 
					update_employee(dipendente); 
				case 3:
					delete_employee(dipendente); 
			}
			case 2: 								//Tour
			switch(COD_OP[2]) 					    // tabella 
				{ 
					case 1:								// Tour 
				    switch(COD_OP[3]) 						//Operazione
					{
						case 1: 
						insert_tour(tour);
						case 2: 
						update_tour(tour); 
						case 3:
						delete_tour(tour); 
					}
					case 2: 							// Viaggio
					switch(COD_OP[3]) 						//Operazione
					{	
						case 1: 
						insert_trip(viaggio);
						case 2: 
						update_trip(viaggio); 
						case 3:
						delete_trip(viaggio);
					}
					case 3: 							// Meta
					switch(COD_OP[3]) 						//Operazione
					{	
						case 1: 
						insert_destination(meta);
						case 2: 
						update_destination(meta);; 
						case 3:
						delete_destination(meta);;
					}
					case 4: 							// Visita
					switch(COD_OP[3]) 						//Operazione
					{	
						case 1: 
						insert_visit(visita);
						case 2: 
						update_visit(visita); 
						case 3:
						delete_visit(visita);
					}
					case 5: 							// Camera
					switch(COD_OP[3]) 						//Operazione
					{	
						case 1: 
						insert_room(camera);
						case 2: 
						update_room(camera); 
						case 3:
						delete_room(camera);
					}
					case 6:								 // Località
					switch(COD_OP[3]) 						//Operazione
					{	
						case 1: 
						insert_location(localita);
						case 2: 
						update_location(localita); 
						case 3:
						delete_location(localita);
					}
					case 7:								// Mappa 
					switch(COD_OP[3]) 						//Operazione
					{	
						case 1: 
						insert_map(mappa);
						case 2: 
						update_map(mappa); 
						case 3:
						delete_map(mappa);
					}
					case 8: // Esci ;
			}
			case 3: 										//Officina
			switch(COD_OP[2])								//Tabella 	
			{
		 		case 1:											//Modello								
				switch(COD_OP[3]) 									//Operazione
					{	
						case 1: 											
						insert_model(modello);
						case 2: 
						update_model(modello); 
						case 3:
						delete_model(modello);
					}
					case 2:										//Mezzo 
					switch(COD_OP[3]) 								//Operazione
					{	
						case 1: 
						insert_bus(mezzo);
						case 2: 
						update_bus(mezzo); 
						case 3:
						delete_bus(mezzo);
					}
					case 3:									 	// Ricambio
					switch(COD_OP[3]) 								//Operazione
					{	
						case 1: 
						insert_sparepart(ricambio);
						case 2: 
						update_sparepart(ricambio); 
						case 3:
						delete_sparepart(ricambio);
					}
					case 4:										 // Revisione
					switch(COD_OP[3])								 //Operazione
					{	
						case 1: 
						insert_review(revisione);
						case 2: 
						update_review(revisione); 
						case 3:
						delete_review(revisione);
					}
					case 5:										 // Tagliando 
					switch(COD_OP[3]) 								//Operazione
					{	
						case 1: 
						insert_certify(tagliando);
						case 2: 
						update_certify(tagliando); 
						case 3:
						delete_certify(tagliando);
					}
					case 6:											 // Esci ;
				
			}
			case 4: 									//Clienti
			switch(COP_OP[2])							//Tabella
				{
					case 1: 								//Cliente														
					switch(COD_OP[3]) 							//Operazione					
					{	
						case 1: 
						insert_costumer(employee);
						case 2: 
						update_costumer(employee); 
						case 3:
						delete_costumer(employee);
					}
					/*
		
		 			 puts("3) Posto prenotato");
					 puts("4) Esci");*/

					case 2:									 // Prenotazione
					switch(COD_OP[3]) 							//Operazione
					{	
						case 1: 
						insert_prenotation(prenotazione);
						case 2: 
						update_prenotation(prenotazione); 
						case 3:
						delete_prenotation(prenotazione);
					}
					case 4: 								// Posto prenotato
					switch(COD_OP[3]) 							//Operazione
					{	
						case 1: 
						insert_seat(postoprenotato);
						case 2: 
						update_seat(postoprenotato); 
						case 3:
						delete_seat(postoprenotato);
					}
					case 5: //Esci
				
			}
		}
   

}
	
/*char options[45] = {'1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17', '18','19','20', '21', '22','23', '24', '25','26','27','28','29','30','31','32','33','34','35','36',	 '37','38','39','40','41','42','43','44','45','46','47','48','49','50','51'};
	char op;
	puts("1) Inserire un nuovo tour");
	puts("2) Inserire una nuova meta");
	puts("3) Inserire un nuovo viaggio");
	puts("4) Inserire una nuova visita");
	puts("5) Inserire una nuova foto");
	puts("6) Inserire un nuovo dipendente");
	puts("7) Inserire una nuova camera");
	puts("8) Inserire una nuova località");
	puts("9) Inserire una nuova mappa");
	puts("10) Inserire un nuovo cliente");
	puts("11) Inserire una nuova prenotazione");
	puts("12) Inserire un nuovo posto prenotato");
	puts("13) Inserire una nuova revisione");
	puts("14) Inserire un nuovo ricambio");
	puts("15) Inserire un nuovo mezzo");
	puts("16) Inserire un nuovo modello");
	puts("17) Inserire un nuovo tagliando");
	puts("18) Eliminare un tour");
	puts("19) Eliminare una meta");
	puts("20) Eliminare un viaggio");
	puts("21) Eliminare una visita");
	puts("22) Eliminare una foto");
	puts("23) Eliminare un dipendente");
	puts("24) Eliminare una camera");
	puts("25) Eliminare una località");
	puts("26) Eliminare una mappa");
	puts("27) Eliminare un cliente");
	puts("28) Eliminare una prenotazione");
	puts("29) Eliminare un posto prenotato");
	puts("30) Eliminare una revisione");
	puts("31) Eliminare un ricambio");
	puts("32) Eliminare un mezzo");
	puts("33) Eliminare un modello");
	puts("34) Eliminare un tagliando");
	puts("35) Modificare un tour");
	puts("36) Modificare un viaggio");
	puts("37) Modificare una visita");
	puts("38) Modificare una foto");
	puts("39) Modificare un dipendente");
	puts("40) Modificare una camera");
	puts("41) Modificare una località");
	puts("42) Modificare una mappa");
	puts("43) Modificare un cliente");
	puts("44) Modificare una prenotazione");
	puts("45) Modificare un posto prenotato");
	puts("46) Modificare una revisione");
	puts("47) Modificare un ricambio");
	puts("48) Modificare un mezzo");
	puts("49) Modificare un modello");
	puts("50) Modificare un tagliando");
	puts("51) Esci");

	op = multi_choice("Seleziona un'opzione", options, 51);
	return op - '1';*/

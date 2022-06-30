
#include <stdio.h>

#include "manager.h"
#include "ins.h"
#include "show.h"

#include "../utils/io.h"
#include "../utils/validation.h"

struct associata * associata;
struct competenze *competenze; 
struct dipendente * dipendente; 
struct fmo *fmo; 
struct fme *fme; 
struct offre *offre; 
struct tome *tome;
struct utente *utente; 

int allocation_gest(void)
{

	associata = malloc(sizeof(struct associata)); 
	if(associata == NULL)
		{printf("Fallimento malloc su associata (manager)) \n\n"); 
		 return -1; 
		}
	competenze = malloc(sizeof(struct competenze)); 
	if(competenze == NULL)
		{printf("Fallimento malloc su competenze (manager) \n\n");
		 return -1; 
		}
	dipendente = malloc(sizeof(struct dipendente));
	if(dipendente == NULL)
		{printf("Fallimento malloc su dipendente (manager) \n\n"); 
		 return -1; 
		}
	fmo = malloc(sizeof(struct fmo)); 
	if(fmo == NULL)
		{printf("Fallimento malloc su fmo (manager) \n\n"); 
		 return -1;
		}
	fme = malloc(sizeof(struct fme));
	if(fme == NULL)
		{printf("Fallimento malloc fme (manager) \n\n"); 
		 return -1; 
		 }
    offre = malloc(sizeof(struct offre));
	if(offre == NULL)
		{printf("Fallimento malloc offre (manager) \n\n"); 
		 return -1; 
	    }
    tome = malloc(sizeof(struct tome));
	if(tome == NULL)
		{printf("Fallimento malloc tome (manager) \n\n"); 
		 return -1; 
		 }
    utente = malloc(sizeof(struct utente));
	if(utente == NULL)
		{printf("Fallimento malloc utente (manager) \n\n"); 
		 return -1; 
		 }
}

int get_admin_action(void) 
{	char options[4] = {'1','2','3','4'};
	char op; 
	puts("*** Quale operazione vorresti eseguire? ***\n");
	puts("1) Visualizzazione");
	puts("2) Inserimento");
	puts("3) Cancellazione");
	puts("4) Esci");
	op = multi_choice("Seleziona un'opzione", options, 4);
	return op - '1';
}

int get_mngr_group(void)
{	char options[5] = {'1','2','3','4','5'};
	char op; 
	puts("*********************************");
	puts("*   INTERFACCIA AMMINISTRATORE    *");
	puts("*********************************\n");
	puts("*** In quale ambito ? ***\n");
	puts("1) Gestione interna");
	puts("2) Gestione tour");
	puts("3) Gestione officina");
	puts("4) Gestione clienti");
	puts("5) Esci");

	op = multi_choice("Seleziona un'opzione", options, 5);
	return op - '1';

}

int tour_section(void) //sezione tour
{	
	char options[8] = {'1','2','3','4','5','6','7','8'};
    char op; 
		puts("*** Su quale tabella della gestione tour? ***\n");
		puts("1) Tour");
		puts("2) Viaggio");
		puts("3) Meta");
		puts("4) Visita");
		puts("5) Camera"); 
		puts("6) Località"); 
		puts("7) Mappa");
		puts("8) Esci");
		op = multi_choice("Seleziona un'opzione", options, 8);
		return op - '1';
}


int workshop_section(void) // sezione officina 
 {	    
		char options[6] = {'1','2','3','4','5','6'};
        char op; 
		 puts("*** Su quale tabella della gestione officina? ***\n");
	 	 puts("1) Modello ");
	 	 puts("2) Mezzo");
	 	 puts("3) Ricambio");
		 puts("4) Revisione");
		 puts("5) Tagliando");
		 puts("6) Esci");
		 op = multi_choice("Seleziona un'opzione", options, 6);
		 return op - '1';
}


int costumer_section(void) // sezione clienti
{	

	char options[4] = {'1','2','3','4'};
    char op; 
    puts("*** Su quale tabella della gestione clienti? ***\n");
	puts("1) Cliente");
    puts("2) Prenotazione");
	puts("3) Posto prenotato");
	puts("4) Esci");
    op = multi_choice("Seleziona un'opzione", options, 4);
	return op - '1';
}

bool get_table_gest (char sel)
{   char act;
    if(associata == NULL ||	 competenze == NULL || dipendente == NULL ||fme == NULL ||fmo == NULL|| offre == NULL || tome == NULL || utente == NULL) {
		allocation_gest();
		printf("\n\nAllocazione gest avvenuta.\n\n");
     } 
    switch(sel){
        case TABELLA_DIPENDENTI: {
        printf("dipendente\n"); 
        return true; 
        }

        case TABELLA_UTENTI: {
         printf("utenti\n");
        return true; 
        }
        case TABELLA_ASSOCIATA: {
        act = get_admin_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_assoc(associata); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    //ins_assoc(associata); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    //del_associata(associata); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                    return false; 
                }
            } 
        } 
        case TABELLA_OFFRE: {
		return true; 
        }
        case TABELLA_COMPETENZE: {
            act = get_admin_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_skills(competenze); 
                return true; 
                }
	            case GESTIONE_INSERT: {
                    //ins_assoc(associata); 
                return true; 
                }
	            case GESTIONE_DELETE: {
                    //del_associata(associata); 
                return true; 
                }
	            case QUIT_GEST_OP: {
                return false; 
				}
			}
        }
        case TABELLA_TOME: {
        
        return true; 
        }
        case TABELLA_FMO: {
        
        return true; 
        } 
        case TABELLA_FME: {
        
        return true; 
        }
        case QUIT_ANAG: {

        return false; 
        }
    }

}

int gest_section(void)
 {	    
		char options[9] = {'1','2','3','4','5','6','7','8','9'};
        char op; 
		 puts("*** Su quale tabella della gestione officina? ***\n");
	 	 puts("1) Dipendenti");
	 	 puts("2) Utenti");
	 	 puts("3) Associata");
		 puts("4) Offre");
		 puts("5) Competenze");
		 puts("6) Collegamento tour-mete");
         puts("7) Collegamento foto-modelli");
         puts("8) Collegamento foto-mete");
         puts("9) Esci"); 
		 op = multi_choice("Seleziona un'opzione", options, 9);
         get_table_gest((op - '1')); 
}




bool exe_mngr_group(char sel)
{	

	switch (sel)
		{	
			case GESTIONE_DIPENDENTI: {
				gest_section(); 
				return true;
				}
			case GESTIONE_CLIENTI:{
				costumer_section();  
				return true; 
				}
		
			case GESTIONE_OFFICINA:{
				workshop_section();  
				return true;
				}
     		case GESTIONE_TOUR:{
                tour_section(); 
				return true; 
				}
			case QUIT_GEST_GROUP:{ 
				return false;
		 		} 
		
	}
	return true;
}


void run_mngr_interface (void)
{ 	
	char sel;
	while (true){
	sel = get_mngr_group(); 
	if (!exe_mngr_group(sel))
		break; 
	}

}	

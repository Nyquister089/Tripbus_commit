
#include <stdio.h>

#include "manager.h"
#include "ins.h"
#include "show.h"

#include "../utils/io.h"
#include "../utils/validation.h"

struct associata * associata;
struct camera *camera; 
struct documentazionefotografica *documentazionefotografica; 
struct cliente *cliente; 
struct competenze *competenze; 
struct dipendente * dipendente; 
struct fmo *fmo; 
struct fme *fme; 
struct localita *localita; 
struct mappa *mappa; 
struct meta *meta; 
struct mezzo *mezzo; 
struct modello *modello; 
struct offre *offre; 
struct postoprenotato *postoprenotato; 
struct prenotazione *prenotazione; 
struct revisione *revisione; 
struct ricambio *ricambio; 
struct tagliando *tagliando; 
struct tome *tome;
struct tour *tour; 
struct viaggio *viaggio;
struct visita *visita;  
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

int allocation_costumer(void)
{

	cliente = malloc(sizeof(struct cliente)); 
	if(cliente == NULL)
		{printf("Fallimento malloc su cliente (manager)) \n\n"); 
		 return -1; 
		}
	prenotazione = malloc(sizeof(struct prenotazione)); 
	if(prenotazione == NULL)
		{printf("Fallimento malloc su prenotazione (manager) \n\n");
		 return -1; 
		}
	postoprenotato = malloc(sizeof(struct postoprenotato));
	if(postoprenotato == NULL)
		{printf("Fallimento malloc su postoprenotato (manager) \n\n"); 
		 return -1; 
		}

}

int allocation_workshop(void)
{	

	mezzo = malloc(sizeof(struct mezzo));
	if(mezzo == NULL)
		{printf("Fallimento malloc su mezzo (manager) \n\n"); 
		 return -1;
		}
	modello = malloc (sizeof(struct modello));
	if(modello == NULL)
		{printf("Fallimento malloc su modello (manager) \n\n"); 
		 return -1;
		}
	revisione = malloc(sizeof(struct revisione));
	if(revisione == NULL)
		{printf("Fallimento malloc su revisione (manager) \n\n"); 
		 return -1;
		}

	ricambio = malloc(sizeof(struct ricambio));
	if(ricambio == NULL)
		{printf("Fallimento malloc su ricambio (manager) \n\n"); 
		 return -1;
		}
	
	tagliando = malloc(sizeof(struct tagliando));
	if(tagliando == NULL)
		{printf("Fallimento malloc su tagliando (manager) \n\n"); 
		 return -1;
		}
}

int allocation_tour(void){

	camera = malloc(sizeof(struct camera));
	if(camera == NULL)
		{printf("Fallimento malloc su camera (manager) \n\n"); 
		 return -1;
		}
	documentazionefotografica = malloc(sizeof(struct documentazionefotografica));
	if(documentazionefotografica == NULL)
		{printf("Fallimento malloc su documentazionefotografica (manager) \n\n"); 
		 return -1;
		}
	localita = malloc(sizeof(struct localita));
	if(localita == NULL)
		{printf("Fallimento malloc su localita (manager) \n\n"); 
		 return -1;
		}
	mappa = malloc(sizeof(struct mappa));
	if(mappa == NULL)
		{printf("Fallimento malloc su mappa (manager) \n\n"); 
		 return -1;
		}
	meta = malloc(sizeof(struct meta));
	if(meta == NULL)
		{printf("Fallimento malloc su meta (manager) \n\n"); 
		 return -1;
		}
	viaggio = malloc(sizeof(struct viaggio));
	if(viaggio == NULL)
		{printf("Fallimento malloc su viaggio (manager) \n\n"); 
		 return -1;
		}
	visita = malloc(sizeof(struct visita));
	if(visita == NULL)
		{printf("Fallimento malloc su visita (manager) \n\n"); 
		 return -1;
		}
	tour = malloc(sizeof(struct tour));
	if(tour == NULL)
		{printf("Fallimento malloc su tour (manager) \n\n"); 
		 return -1;
		}

}


int get_mngr_action(void) 
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


bool get_table_tour(char sel)
{
	char act; 
	if(camera == NULL || documentazionefotografica == NULL || localita == NULL || mappa == NULL || meta == NULL ){
		allocation_tour();
		printf("Allocazione tour avvenuta\n\n"); 
	}
	switch(sel){
		case TABELLA_TOUR:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_costumer(cliente); 
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
    	case TABELLA_VIAGGIO:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_costumer(cliente); 
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
    	case TABELLA_META:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_costumer(cliente); 
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
    	case TABELLA_VISITA:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_costumer(cliente); 
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
    	case TABELLA_LOCALITA:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_costumer(cliente); 
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
    	case TABELLA_MAPPA:{
			act = get_mngr_action();
						switch(act){
				case GESTIONE_SELECT: {
                    show_costumer(cliente); 
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
    case QUIT_GEST_TOUR:{
		return false; 
	}
	}
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
		get_table_tour(( op - '1'));
}


bool get_table_workshop(char sel){ 
	char act; 
	if (mezzo == NULL || modello == NULL || revisione == NULL || ricambio == NULL || tagliando == NULL)
		{
			allocation_workshop(); 
			printf("Allocazione costumer avvenuta\n\n"); 
		}
	switch(sel){
		case TABELLA_MODELLO: {
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_model(modello); 
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

    	case TABELLA_MEZZO:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_bus(mezzo); 
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
    	case TABELLA_RICAMBIO:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_sparepart(ricambio); 
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
    	case TABELLA_REVISIONE:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_review(revisione); 
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
    	case TABELLA_TAGLIANDO:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_costumer(cliente); 
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
    	case QUIT_GEST_OFFICINA:{
			return false; 
		}
	}
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
		 get_table_workshop((op - '1'));
}


bool get_table_costumer (char sel )
{ 	
	char act; 
	if(cliente == NULL || prenotazione  == NULL || postoprenotato == NULL) {
		allocation_costumer();
		printf("\n\nAllocazione costumer avvenuta.\n\n");
     } 
    switch(sel){
		case TABELLA_CLIENTE: {
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_costumer(cliente); 
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

    	case TABELLA_PRENOTAZIONE:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_reservation(prenotazione); 
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

    	case TABELLA_POSTO_PRENOTATO:{
			act = get_mngr_action(); 
			switch(act){
				case GESTIONE_SELECT: {
                    show_seat(postoprenotato); 
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
    	case QUIT_GEST_CLIENTE: {
		return false; 
		}
	}

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
	get_table_costumer((op-'1')); 
}


bool get_table_gest (char sel)
{   char act;
    if(associata == NULL ||	 competenze == NULL || dipendente == NULL ||fme == NULL ||fmo == NULL|| offre == NULL || tome == NULL || utente == NULL) {
		allocation_gest();
		printf("\n\nAllocazione gest avvenuta.\n\n");
     } 
    switch(sel){
        case TABELLA_DIPENDENTI: {
         act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_employee(dipendente); 
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
			return true; 
        }

        case TABELLA_UTENTI: {
         act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_user(utente); 
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
        return true; 
        }
        case TABELLA_ASSOCIATA: {
        act = get_mngr_action();
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
			return true;
        } 
        case TABELLA_OFFRE: {
			act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_ofr(offre); 
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
		return true; 
        }
        case TABELLA_COMPETENZE: {
            act = get_mngr_action();
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
			return true;
        }
        case TABELLA_TOME: {
        act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_tome(tome); 
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
        
        return true; 
        }
        case TABELLA_FMO: {
			act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_fmo(fmo); 
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
			return true;
        
        } 
        case TABELLA_FME: {
			act = get_mngr_action();
            switch (act){
                case GESTIONE_SELECT: {
                    show_fme(fme); 
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

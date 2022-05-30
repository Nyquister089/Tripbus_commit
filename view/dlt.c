#include<stdio.h>
#include<stdlib.h>
#inlcude"...\modeltripbus\tripbus.h"

char *BUFFER[VARCHAR_LEN]; // variabile d'appoggio per  stringhe per ricerca
char *RES[VARCHAR_LEN]; // variabile d'appoggio che riceve le stringhe restituite dalla ricerca (utile per debug)
int ID_RSRC; // variabile d'appoggio che preleva l'id per la ricerca
int ID_RES;  // variabile d'appoggio che riceve l'id restuito dalla ricerca (utile per debug)
bool ANS; // variabile per prelevare le risposte "si" o "no"

void delete_tour(struct tour *tour)
{	clear_screen();
	printf("** Dettagli  tour **\n\n");
	get_input("Inserisci la denominazione del tour:", VARCHAR_LEN, BUFFER, false);
	// esegui procedura di select
	printf (" Denominazione: %s ", 
			tour.denominazionetour); 
	ANS = yes_or_no("\n\n Vuoi cancellare questo tour? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna.
}

void delete_destination(struct meta *meta)
{	clear_screen();
	printf("** Dettagli  meta **\n\n");
	get_input("Inserisci l'ID della meta:", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID Meta: %d \n Nome: %d \n  ",
			meta.idmeta,
			meta.nomemeta); 

	ANS = yes_or_no("\n\n Vuoi cancellare questa meta? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna.
}

void delete_trip(struct viaggio *viaggio)
{	clear_screen();
	printf("** Dettagli  viaggio **\n\n");
	get_input("Inserisci l'ID della viaggio:", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID: %d \n Tour associato: %s \n Data di partenza: %s \n Data di ritorno: %s  ",
			viaggio.idviaggio,
			viaggio.tourassociato,
			viaggio.datadipartenzaviaggio, 
			viaggio.datadiritornoviaggio); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo viaggio? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna.
}

void delete_visit(struct visita *visita, struct meta *meta)
{	clear_screen();
	printf("** Dettagli  visita **\n\n");
	get_input("Inserisci l'ID della visita:", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID: %d \n ID viaggio associato: %d \n ID meta visitata: %d \n Nome meta visitata: %s \n Data di arrivo: %s \n Data di partenza: %s \n Ora di arrivo %s \n Ora di partenza: %s  ",
			visita.idvisita,
			visita.viaggiorelativo,
			visita.metavisitata, 
			meta.nomemeta,
			visita.datadiarrivo,
			visita.datadipartenza,
			visita.oradiarrivo, 
			visita.oradipartenza); 

	ANS = yes_or_no("\n\n Vuoi cancellare questa visita? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna. 
}

void delete_picture(struct documentazionefotografica *documentazionefotografica) 									 
{	clear_screen();
	printf("** Dettagli foto **\n\n");
	get_input("Inserisci l'ID della foto", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID: %d \n  %s ",
			documentazionefotografica.idfoto,
			documentazionefotografica.foto); 

	ANS = yes_or_no("\n\n Vuoi cancellare questa foto? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna. 
}


void delete_employee(struct dipendente *dipendente)
{	clear_screen();
	printf("** Dettagli  dipendente **\n\n");
	get_input("Inserisci l'ID del dipendente", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID: %d \n Nome: %s \n Cognome: %s \n ",
			dipendente.iddipendente,
			dipendente.nome, 
			dipendente.cognome); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo dipendente? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna. 
}

void delete_room(struct camera *camera, struct albergo *albergo)
{	clear_screen();
	printf("** Dettagli  camera di albergo **\n\n");

	get_input("Inserisci l'ID dell'albergo", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	get_input("Inserisci il numero della camera ",ID_LEN, ID_RSRC, false )
	// esegui procedura di select
	printf (" ID albergo: %d \n Nome albergo: %s \n Numero camera: %s \n ",
			meta.idmeta,
			meta.nomemeta, 
			camera.numerocamera); 

	ANS = yes_or_no("\n\n Vuoi cancellare questa camera? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna. 
}

void delete_location(struct localita *localita) 
{	clear_screen();
	printf("** Dettagli  localita' **\n\n");
	get_input("Inserisci il nome della  localita'", VARCHAR_LEN, BUFFER, false);
	// esegui procedura di select
	printf (" Nome: %s \n ", RES); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo dipendente? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna. 
}

void delete_map(struct mappa *mappa) 
{	clear_screen();
	printf("** Dettagli  mappa **\n\n");
	get_input("Inserisci il numero della mappa ", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID : %d \n citta': %s \n livello di dettaglio: %s zona: %s ",
			mappa.numeromappa,
			mappa.citta,
			mappa.livellodidettaglio,
			mappa.zona); 

	ANS = yes_or_no("\n\n Vuoi cancellare questa mappa? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna. 
	}

void delete_costumer(struct cliente *cliente)
{	clear_screen();
	printf("** Dettagli  cliente **\n\n");
	get_input("Inserisci l'indirizzo e-mail", VARCHAR_LEN, BUFFER false);
	// esegui procedura di select
	printf (" E-mail: %s \n Nome: %s \n Cognome: %s Codice fiscale: %s ",
			cliente.emailcliente,
			cliente.nomecliente,
			cliente.cognomecliente,
			cliente.codicefiscale
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo cliente? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna.
}

void delete_prenotation(struct prenotaizone *prenotazione) 
{	clear_screen();
	printf("** Dettagli  prenotazione **\n\n");
	get_input("Inserisci il numero di prenotazione : ", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" Numero : %d \n E-mail prenotante: %s \n data di prenotazione: %s ",
			prenotazione.numerodiprenotazione,
			prenotazione.clienteprenotante,
			prenotazione.datadiprenotazione,
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questa prenotazione? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna.
}

void delete_seat(struct postoprenotato *postoprenotato, struct viaggio *viaggio)
{	clear_screen();
	printf("** Dettagli  passeggero **\n\n");
	get_input("Inserisci l'ID del viaggio : ", ID_LEN,ID_RSRC, false);
	get_input("Inserisci il numero di posto: ", ID_LEN,ID_RSRC, false);
	// esegui procedura di select
	printf (" Id Viaggio: %d \n Numero di posto: %s \n Nome passeggero : %s \n Cognome passeggero: %s ",
			viaggio.idviaggio,
			postoprenotato.numerodiposto,
			postoprenotato.nomepasseggero,
			postoprenotato.cognomepasseggero,
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo posto prenotato? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna.
}

void delete_review(struct revisione *revisione)
{	clear_screen();
	printf("** Dettagli  revisione **\n\n");
	get_input("Inserisci l'ID della revisione  : ", NUM_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID: %d \n Targa mezzo: %s \n Data inizio : %s \n Data fine : %s ",
			revisione.idrevisione,
			revisione.mezzorevisionato,
			revisione.datainizio,
			revisione.datafine,
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questa revisione? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna
}

void delete_sparepart(struct ricambio *ricambio)
{	clear_screen();
	printf("** Dettagli  ricambio **\n\n");
	get_input("Inserisci il codice del ricambio  : ", VARCHAR_LEN, BUFFER, false);
	// esegui procedura di select
	printf (" Codice: %s \n Descrizione: %s \n Quantita in magazzino : %s ",
			ricambio.codicericambio,
			ricambio.mezzorevisionato,
			ricambio.datainizio,
			ricambio.datafine,
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo ricambio? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna
}

void delete_bus(struct mezzo *mezzo, struct modello *modello)
{	clear_screen();
	printf("** Dettagli  mezzo **\n\n");
	get_input("Inserisci la targa del mezzo : ", VARCHAR_LEN, BUFFER, false);
	// esegui procedura di select
	printf (" Targa : %s \n Nome modello: %s ",
			mezzo.targa,
			Modello.nomemodello,
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo mezzo? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna
}

void delete_model(struct modello *modello)
{	clear_screen();
	printf("** Dettagli  modello **\n\n");
	get_input("Inserisci l'ID del modello : ", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID: %s \n Nome modello: %s \n Casa costruttrice: %s ",
			modello.idmodello,
			modello.nomemodello,
			modello.casacostruttrice
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo modello? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna
}

void delete_certify(struct tagliando *tagliando)
{	clear_screen();
	printf("** Dettagli  tagliando **\n\n");
	get_input("Inserisci l'ID del modello : ", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID: %s \n tipologia: %s ",
			tagliando.idtagliando,
			tagliando.tipologiatagliando,
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo tagliando? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna
}

void delete_comfort(struct *comfort)
{	clear_screen();
	printf("** Dettagli  comfort **\n\n");
	get_input("Inserisci l'ID del comfort : ", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID : %s \n Nome: %s \n Descrizione: %s \n",
			comfort.idcomfort,
			comfort.nomecomfort,
			comfort.descrizionecomfort,
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo comfort? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna
	}

void delete_service(struct *servizio)
{	clear_screen();
	printf("** Dettagli  servizio **\n\n");
	get_input("Inserisci l'ID del servizio : ", ID_LEN, ID_RSRC, false);
	// esegui procedura di select
	printf (" ID : %s \n Nome: %s \n Descrizione: %s \n",
			servizio.idservizio,
			servizio.nomeservizio,
			servizio.descrizioneservizio,
			); 

	ANS = yes_or_no("\n\n Vuoi cancellare questo servizio? (s/n) ",'s','n',false,false);
	// esegui delete o ritorna
}



#include <string.h>
#include "../model/trpdb.h"
#include "dlt.h" 
#include "show.h"



void dlt_trip(struct viaggio *viaggio)
{	
	show_trip(viaggio); 
    if(yes_or_no("Vuoi cancellare questo viaggio? (s/n)",'s','n',false,false) == true)
        do_delete_trip(viaggio); 
}
void dlt_tour(struct tour *tour)
{
	show_tour(tour); 
    if(yes_or_no("Vuoi cancellare questo tour? (s/n)",'s','n',false,false) == true)
        do_delete_tour(tour); 
}
void dlt_sparepart(struct ricambio *ricambio)
{	
    
}
void dlt_review (struct revisione *revisione)
{
	show_review(revisione); 
    if(yes_or_no("Vuoi cancellare questa revisione? (s/n)",'s','n',false,false) == true)
        do_delete_review(revisione);
}
void dlt_bus(struct mezzo *mezzo)
{	
	show_bus(mezzo); 
    if(yes_or_no("Vuoi cancellare questo mezzo? (s/n)",'s','n',false,false) == true)
        do_delete_bus(mezzo);
}
void dlt_reservation (struct prenotazione * prenotazione)
{	
	show_reservation(prenotazione); 
    if(yes_or_no("Vuoi cancellare questa prenotazione? (s/n)",'s','n',false,false) == true)
        do_delete_reservation(prenotazione);
    
}

void dlt_costumer (struct cliente * cliente)
{	
	show_costumer(cliente); 
    if(yes_or_no("Vuoi cancellare questo cliente? (s/n)",'s','n',false,false) == true)
        do_delete_costumer(cliente);
    
}
void dlt_assoc(struct associata *associata)
{ 	
    show_assoc(associata); 
    if(yes_or_no("Vuoi cancellare questa associazione? (s/n)",'s','n',false,false) == true)
        do_delete_assoc(associata);
}
void dlt_skills(struct competenze *competenze)
{ 
    show_skills(competenze); 
    if(yes_or_no("Vuoi cancellare queste competenze? (s/n)",'s','n',false,false) == true)
        do_delete_skills(competenze);
}
 void dlt_employee(struct dipendente *dipendente)
{	
	show_employee(dipendente);
	 if(yes_or_no("Vuoi cancellare questo dipendente? (s/n)",'s','n',false,false) == true)
        do_delete_employee(dipendente);

}   
void dlt_fmo(struct fmo *fmo)
{	
	show_fmo(fmo);
	 if(yes_or_no("Vuoi cancellare questa relazione foto-modello? (s/n)",'s','n',false,false) == true)
        do_delete_fmo(fmo);
}
void dlt_fme(struct fme *fme)
{	
	show_fme(fme);
	 if(yes_or_no("Vuoi cancellare questa relazione foto-meta? (s/n)",'s','n',false,false) == true)
        do_delete_fme(fme);
}
void dlt_ofr(struct offre *offre)
{	
	show_ofr(offre);
	 if(yes_or_no("Vuoi cancellare questa offerta? (s/n)",'s','n',false,false) == true)
        do_delete_ofr(offre);
}
void dlt_tome(struct tome *tome)
{		
	show_tome(tome);
	 if(yes_or_no("Vuoi cancellare questa associazione tour-mete? (s/n)",'s','n',false,false) == true)
        do_delete_tome(tome);
}
void dlt_user(struct utente *utente)
{
	show_user(utente);
	 if(yes_or_no("Vuoi cancellare questo utente? (s/n)",'s','n',false,false) == true)
        do_delete_user(utente);
}
void dlt_seat(struct postoprenotato *postoprenotato)
{
	show_seat(postoprenotato);
	 if(yes_or_no("Vuoi cancellare questo posto prenotato? (s/n)",'s','n',false,false) == true)
        do_delete_seat(postoprenotato);
}
void dlt_model(struct modello *modello)
{
	show_model(modello);
	 if(yes_or_no("Vuoi cancellare questo modello? (s/n)",'s','n',false,false) == true)
        do_delete_model(modello);
}
void dlt_certify(struct tagliando *tagliando)
{
	show_certify(tagliando);
	 if(yes_or_no("Vuoi cancellare questo tagliando? (s/n)",'s','n',false,false) == true)
        do_delete_certify(tagliando);
}
void dlt_destination(struct meta *meta)
{	
	show_destination(meta);
	 if(yes_or_no("Vuoi cancellare questa meta? (s/n)",'s','n',false,false) == true)
        do_delete_destination(meta);
}
void dlt_visit(struct visita *visita)
{	
	show_visit(visita);
	 if(yes_or_no("Vuoi cancellare questa visita? (s/n)",'s','n',false,false) == true)
        do_delete_visit(visita);
}
/*











void dlt_comfort(struct comfort *comfort){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli comfort  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	comfort->idcomfort = atoi(buff); 
	do_select_comfort(comfort); 
	printf("*Nome:		%s \n Descrizione:	%s  \n\n",
		comfort->nomecomfort,
		comfort->descrizionecomfort
		
		);
}


void dlt_picture(struct documentazionefotografica *documentazionefotografica){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli documentazionefotografica  **\n\n");
	get_input("Inserisci l'id d'interesse:",NUM_LEN, buff, false); 
	documentazionefotografica->idfoto = atoi(buff); 
	do_select_picture(documentazionefotografica); 
	printf("*Foto:		%s \n Descrizione:	%s  \n\n",
		documentazionefotografica->foto,
		documentazionefotografica->descrzione
		
		);
}


void dlt_map(struct mappa *mappa){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli mappa  **\n\n");
	get_input("Inserisci il numero d'interesse:",NUM_LEN, buff, false); 
	mappa->idmappa = atoi(buff); 
	do_select_map(mappa); 
	printf("*Città:		%s \n Località:	%s \n Dettaglio:	%s \n Zona:		%s \n Immagine: 	%s \n\n",
		mappa->citta,
		mappa->localitarappresentata,
		mappa->dettaglio, 
		mappa->zona,
		mappa->immagine
		);

}

void dlt_room(struct camera *camera){

	char buff[NUM_LEN]; 
	printf("\n\n** Dettagli camera  **\n\n");
	get_input("Inserisci il numero d'interesse:",NUM_LEN, buff, false); 
	camera->numerocamera = atoi(buff); 
	get_input("Inserisci l'id dell'albergo d'interesse:",NUM_LEN, buff, false); 
	camera->albergo = atoi(buff);
	do_select_room(camera); 
	printf("*Tipologia:	%s \n Costo:		%f\n\n",
		camera->tipologia,
		camera->costo
		);

}

void dlt_location(struct localita *localita){


	printf("\n\n** Dettagli localita  **\n\n");
	get_input("Inserisci il nome d'interesse:",VARCHAR_LEN, localita->nomelocalita, false); 

	do_select_location(localita); 
	printf("*Regione:	%s \n Stato:		%s\n\n",
		localita->regione,
		localita->stato
		);

}


	char buff[NUM_LEN];
	printf("\n\n** Dettagli visita  **\n\n");
	get_input("Inserisci l'id  d'interesse:",NUM_LEN, buff, false); 
	visita->idvisita= atoi(buff); 
	do_select_visit(visita); 
	printf("*Tour:		%s  Id viaggio:	%d*\n*Nome meta:	%s Id meta:	%d*\n Data di arrivo:	%s\n Ora di arrivo:		%s\n Data di partenza:	%s\n Ora di partenza:	%s\n Guida:			%d\n Supplemento:		%f\n Trattamento:		%s\n\n",
		visita->tour,
		visita->viaggiorelativo,
		visita->meta,
		visita->metavisitata,
		visita->datadiarrivo,
		visita->oradiarrivo,
		visita->datadipartenza,
		visita->oradipartenza, 
		visita->guida,
		visita->supplemento,
		visita->trattamentoalberghiero);

}

*/
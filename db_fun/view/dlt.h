#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "../utils/io.h"
#include "../utils/validation.h"
#include "../model/trpdb.h"


extern void dlt_costumer(struct cliente *cliente);
extern void dlt_reservation(struct prenotazione *prenotazione);
extern void dlt_seat(struct postoprenotato *postoprenotato);
extern void dlt_review(struct revisione *revisione);
extern void dlt_sparepart(struct ricambio *ricambio);
extern void dlt_bus(struct mezzo *mezzo);
extern void dlt_model(struct modello *modello);
extern void dlt_certify(struct tagliando *tagliando);
extern void dlt_assoc(struct associata *associata);
extern void dlt_sostitution( struct sostituito *sostituito, struct ricambio *ricambio); 
extern void dlt_tour(struct tour *tour);
extern void dlt_trip(struct viaggio *viaggio);
extern void dlt_destination(struct  meta *meta);
extern void dlt_visit(struct visita *visita);
extern void dlt_room(struct camera *camera);
extern void dlt_location(struct localita *localita);
extern void dlt_map(struct mappa *mappa);
extern void dlt_picture(struct documentazionefotografica *documentazionefotografica) ;
extern void dlt_employee(struct dipendente *dipendente);
extern void dlt_user(struct utente *utente);
extern void dlt_ofr(struct offre *offre); 
extern void dlt_service(struct servizio *servizio);
extern void dlt_tome(struct tome *tome); 
extern void dlt_fmo(struct fmo *fmo); 
extern void dlt_fme(struct fme *fme); 
extern void dlt_bus(struct mezzo *mezzo);
extern void dlt_sparepart(struct ricambio *ricambio);
extern void dlt_comfort(struct comfort *comfort);
extern void dlt_skills(struct competenze *competenze); 

#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "../utils/io.h"
#include "../utils/validation.h"
#include "../model/trpdb.h"


extern void ins_costumer(struct cliente *cliente);
extern void ins_prenotation(struct prenotazione *prenotazione);
extern void ins_seat(struct postoprenotato *postoprenotato);
extern void ins_review(struct revisione *revisione, struct sostituito *sostituito, struct ricambio *ricambio);
extern void ins_sparepart(struct ricambio *ricambio);
extern void ins_bus(struct mezzo *mezzo);
extern void ins_model(struct modello *modello);
extern void ins_certify(struct tagliando *tagliando);
extern void ins_association(struct associata *associata);
extern void ins_sostitution( struct sostituito *sostituito, struct ricambio *ricambio); 
extern void ins_tour(struct tour *tour);
extern void ins_trip(struct viaggio *viaggio);
extern void ins_destination(struct  meta *meta);
extern void ins_visit(struct visita *visita);
extern void ins_room(struct camera *camera);
extern void ins_location(struct localita *localita);
extern void ins_map(struct mappa *mappa);
extern void ins_picture(struct documentazionefotografica *documentazionefotografica) ;
extern void ins_employee(struct dipendente *dipendente);
extern void ins_user(struct utente *utente);
extern void ins_offert(struct offre *offre); 
extern void ins_service(struct servizio *servizio);
extern void ins_tome(struct tome *tome); 
extern void ins_fmo(struct fmo *fmo); 
extern void ins_fme(struct fme *fme); 
extern void ins_bus(struct mezzo *mezzo);
extern void ins_sparepart(struct ricambio *ricambio);
extern void ins_comfort(struct comfort *comfort);
extern void ins_skills(struct competenze *competenze); 

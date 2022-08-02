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
/*
void ins_picture(struct documentazionefotografica *documentazionefotografica) ;
void ins_employee(struct dipendente *dipendente);



void ins_costumer(struct cliente *cliente);
void ins_prenotation(struct prenotazione *prenotazione);
void ins_seat(struct postoprenotato *postoprenotato);
void ins_review(struct revisione *revisione);
void ins_sparepart(struct ricambio *ricambio);
void ins_bus(struct mezzo *mezzo);
void ins_model(struct modello *modello);
void ins_certify(struct tagliando *tagliando);
void ins_comfort(struct comfort *comfort);
void ins_service(struct servizio *servizio);*/
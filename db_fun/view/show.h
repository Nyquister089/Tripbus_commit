#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "../utils/io.h"
#include "../utils/validation.h"
#include "../model/trpdb.h"

extern void show_reservation (struct prenotazione * prenotazione);
extern void show_trip(struct viaggio *viaggio); 
extern void show_costumer (struct cliente * cliente); 
extern void show_tour(struct tour *tour); 
extern void show_service(struct servizio * servizio); 
extern void show_sparepart(struct ricambio *ricambio);
extern void show_review(struct revisione *revisione); 
extern void show_bus(struct mezzo *mezzo); 
extern void show_assoc(struct associata *associata); 
extern void show_skills(struct competenze *competenze);
extern void show_employee(struct dipendente *dipendente); 
extern void show_fmo(struct fmo *fmo); 
extern void show_fme(struct fme *fme); 
extern void show_ofr(struct offre *offre);
extern void show_tome(struct tome *tome); 
extern void show_user(struct utente *utente); 
extern void show_seat(struct postoprenotato *postoprenotato); 
extern void show_model(struct modello *modello); 
extern void show_certify(struct tagliando *tagliando); 
extern void show_destination(struct meta *meta); 
extern void show_visit(struct visita *visita); 
extern void show_location(struct localita *localita); 
extern void show_room(struct camera *camera); 
extern void show_map(struct mappa *mappa); 
extern void show_picture(struct documentazionefotografica *documentazionefotografica); 
extern void show_comfort(struct comfort *comfort); 
extern void show_service(struct servizio *servizio); 
extern void show_expired_review (void); 
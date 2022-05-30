#include<stdio.h>
#include<stdlib.h>
#include"deletetripbus.c"

void delete_tour(struct tour *tour);
void delete_destination(struct meta *meta);
void delete_trip(struct viaggio *viaggio);
void delete_visit(struct visita *visita, struct meta *meta);
void delete_picture(struct documentazionefotografica *documentazionefotografica); 						
void delete_employee(struct dipendente *dipendente);
void delete_room(struct camera *camera, struct albergo *albergo);
void delete_location(struct localita *localita);
void delete_map(struct mappa *mappa);
void delete_costumer(struct cliente *cliente);
void delete_prenotation(struct prenotaizone *prenotazione);
void delete_seat(struct postoprenotato *postoprenotato, struct viaggio *viaggio);
void delete_review(struct revisione *revisione);
void delete_sparepart(struct ricambio *ricambio);
void delete_bus(struct mezzo *mezzo, struct modello *modello);
void delete_model(struct modello *modello);
void delete_certify(struct tagliando *tagliando);
void delete_comfort(struct *comfort);
void delete_service(struct *servizio);



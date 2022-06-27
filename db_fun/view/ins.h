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

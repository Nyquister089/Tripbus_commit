#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "../utils/io.h"
#include "../utils/validation.h"
#include "../model/trpdb.h"


extern void insert_costumer(struct cliente *cliente);
extern void insert_prenotation(struct prenotazione *prenotazione);
extern void insert_seat(struct postoprenotato *postoprenotato);
extern void insert_review(struct revisione *revisione);
extern void insert_sparepart(struct ricambio *ricambio);
extern void insert_bus(struct mezzo *mezzo);
extern void insert_model(struct modello *modello);
extern void insert_certify(struct tagliando *tagliando);

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
extern void show_all_tour(struct tour_info *tour_info); 
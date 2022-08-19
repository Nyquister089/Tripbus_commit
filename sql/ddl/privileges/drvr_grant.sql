/*grant select on 
tripdb.viaggio
to 'Autista'@'localhost'; 

grant select on 
tripdb.mezzo
to 'Autista'@'localhost'; 

grant select on 
tripdb.modello
to 'Autista'@'localhost'; 

grant select on 
tripdb.dipendente
to 'Autista'@'localhost'; 

grant select on 
tripdb.tour
to 'Autista'@'localhost'; 

grant select on 
tripdb.visita
to 'Autista'@'localhost'; 

grant select on 
tripdb.localita
to 'Autista'@'localhost'; 

grant select on 
tripdb.mappa
to 'Autista'@'localhost'; 

grant update on 
tripdb.mezzo
to 'Autista'@'localhost'; */ 

grant execute on procedure login to 'Autista'@'localhost';

grant execute on procedure 
select_bus
to 'Autista'@'localhost';

grant execute on procedure 
select_assigned_trip 
to 'Autista'@'localhost';

grant execute on procedure 
select_dest_time	
to 'Autista'@'localhost';

grant execute on procedure 
update_km 
to 'Autista'@'localhost';

grant execute on procedure 
select_dvr_map 
to 'Autista'@'localhost';

flush privileges; 
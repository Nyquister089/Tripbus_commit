/*create user if not exists 'Autista'@'localhost' identified by 'drvr'; 
grant usage on tripdb.* to 'Austista'@'localhost'; */
grant select on 
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
to 'Autista'@'localhost';  

grant execute on procedure 
login
TO 'Autista'@'localhost';

grant execute on procedure 
select_bus
TO 'Autista'@'localhost';

grant execute on procedure 
select_assigned_trip 
TO 'Autista'@'localhost';

grant execute on procedure 
select_dest_time	
TO 'Autista'@'localhost';

grant execute on procedure 
update_km 
TO 'Autista'@'localhost';

grant execute on procedure 
select_dvr_map 
TO 'Autista'@'localhost';

flush privileges; 
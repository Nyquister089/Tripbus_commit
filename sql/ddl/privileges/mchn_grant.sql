grant select on tripdb.revisione to 'Meccanico'@'localhost';  

grant execute procedure 
insert_review 
to 'Meccanico'@'localhost';

grant execute procedure 
insert_sostitution 
to 'Meccanico'@'localhost'; 	

grant execute procedure 
select_review 
to 'Meccanico'@'localhost'; 	  

grant execute procedure 
select_sparepart 
to 'Meccanico'@'localhost';

grant execute procedure 
delete_review 
to 'Meccanico'@'localhost';

grant execute procedure 
delete_sparepart 
to 'Meccanico'@'localhost';   

grant execute procedure 
select_expired_review 
to 'Meccanico'@'localhost'; 

grant execute procedure 
select_max_idreview 
to 'Meccanico'@'localhost'; 

grant execute procedure 
update_spareparts_number 
to 'Meccanico'@'localhost'; 

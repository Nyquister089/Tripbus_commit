create procedure if not exists `tripdb`. `select_location` (
    in nml varchar (45)
 )
begin
select
	l.Regione, 
	l.Stato
from localita as l 
where l.NomeLocalita = nml; 
end
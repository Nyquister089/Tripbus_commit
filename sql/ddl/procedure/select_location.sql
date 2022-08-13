create procedure if not exists `tripdb`. `select_location` (
    in nml varchar (45),
	in rgn varchar (45)
 )
begin
select 
	l.Stato
from localita as l 
where l.NomeLocalita = nml and l.Regione = rgn; 
end
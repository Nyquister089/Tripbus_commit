create procedure if not exists `tripdb`.`delete_location`(
    in nm varchar (45),
    in rgn varchar (45)
)
begin
delete 
from localita
where NomeLocalita = nm and Regione =rgn; 
end
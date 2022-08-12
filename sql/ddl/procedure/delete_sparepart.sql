create procedure if not exists `tripdb`.`delete_sparepart`(
    in cdc varchar(45)
)
begin
delete 
from ricambio
where Codice = cdc;  
end

create procedure if not exists `tripdb`.`delete_bus`(
    in trg varchar (10)
)
begin
delete 
from mezzo
where Targa = trg;  
end

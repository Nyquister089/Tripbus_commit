create procedure if not exists `tripdb`.`delete_model`(
    in nmd varchar (45)
)
begin
delete
from modello
where NomeModello = nmd; 
end 
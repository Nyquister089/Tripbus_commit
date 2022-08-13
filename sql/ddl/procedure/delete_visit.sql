create procedure if not exists `tripdb`.`delete_visit`(
    in idv int
)
begin
delete
from visita 
where idvisita = idv; 
end
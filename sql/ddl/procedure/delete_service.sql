create procedure if not exists `tripdb`.`delete_service`(
    in ids int
)
begin
delete 
from servizio
where  IdServizio = ids; 
end
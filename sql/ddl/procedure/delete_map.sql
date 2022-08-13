create procedure if not exists `tripdb`.`delete_map`(
    in idm int
)
begin
delete 
from mappa
where IdMappa = idm ;  
end
create procedure if not exists `tripdb`.`delete_destination`(
    in idm int
)
begin
delete
from meta 
where IdMeta = idm;
end
create procedure if not exists `tripdb`.`delete_employee`(
    in idp int 
)
begin 
delete 
from dipendente
where IdDipendente = idp;  
end
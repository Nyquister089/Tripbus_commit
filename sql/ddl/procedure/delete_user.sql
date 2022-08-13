create procedure if not exists `tripdb`.`delete_user`(
    in idu int
)
begin
delete 
from utente
where IdUtente = idu;  
end
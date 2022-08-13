create procedure if not exists `tripdb`.`delete_picture`(
    in idf int
)
begin
delete 
from documentazionefotografica
where idDocumentazioneFotografica = idf ;  
end
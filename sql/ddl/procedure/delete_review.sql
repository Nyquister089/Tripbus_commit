create procedure if not exists `tripdb`.`delete_review`(
    in idr int
)
begin
delete 
from revisione
where IdRevisione = idr;  
end
create procedure if not exists `tripdb`.`delete_certify`(
    in idt int
)
begin
delete
from tagliando
where IdTagliando = idt; 
end
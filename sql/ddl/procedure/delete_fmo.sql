create procedure if not exists `tripdb`.`delete_fmo`(
    in ftm int,
    in mdr varchar (45)
)
begin
delete 
from fmo
where FotoModello = ftm and ModelloRappresentato =mdr;  
end
create procedure if not exists `tripdb`.`delete_tour`(
    in dnm varchar(45)
)
begin
delete 
from tour
where DenominazioneTour = dnm;  
end

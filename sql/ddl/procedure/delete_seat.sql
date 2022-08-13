create procedure if not exists `tripdb`.`delete_seat`(
    in vgs int, 
    in nmp int
)
begin
delete 
from postoprenotato
where ViaggioAssociato = vgs and NumeroDiPosto = nmp;  
end
create procedure if not exists `tripdb`.`delete_reservation`(
    in nmp int
)
begin
delete 
from prenotazione
where NumeroDiPrenotazione = nmp;  
end
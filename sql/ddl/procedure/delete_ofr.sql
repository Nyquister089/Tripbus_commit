create procedure if not exists `tripdb`.`delete_ofr`(
    in htl int,
    in srv int
)
begin 
delete 
from offre
where AlbergoOfferente = htl and ServizioOfferto = srv;  
end
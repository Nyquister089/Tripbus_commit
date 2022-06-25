CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_expired_review`(
 )
BEGIN
select distinct distinct m.Targa, r.DataFine
from mezzo as m
join revisione as r on m.Targa = r.MezzoRevisionato
where DATE_ADD(DataFine, INTERVAL 1 YEAR) <= CURDATE()
or (m.ValoreContaKm - r.Chilometraggio) > '40000' ; 
END
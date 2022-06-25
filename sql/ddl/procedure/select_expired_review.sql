CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_expired_review`(
 )
BEGIN
select distinct m.Targa, r.DataFine, r.Chilometraggio, m.ValoreContaKm
from mezzo as m
join revisione as r on m.Targa = r.MezzoRevisionato
where (DATE_ADD(r.DataFine, INTERVAL 1 YEAR) <= CURDATE()
or (m.ValoreContaKm - r.Chilometraggio) > '40000')
and r.DataFine not in (select distinct r1.DataFine
            from revisione as r1
            join revisione as r2 on r1.IdRevisione = r2.IdRevisione
            where r1.DataFine > r2.DataFine); 
END
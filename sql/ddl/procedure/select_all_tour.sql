CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_all_tour`(
 )
BEGIN
select distinct t.DenominazioneTour,
 t.DescrizioneTour,
 t.Minimopartecipanti, 
 t.CostoAssicurazioneMedica, 
 t.CostoBagaglio, 
 t.CostoGaranziaAnnullamento, 
 t.Accompagnatrice,
 v.DataPartenzaViaggio, 
 v.DataRitornoViaggio, 
 v.CostoDelViaggio, 
 v.PostiDisponibili,
 v.idviaggio
from tour as t
join viaggio as v on t.DenominazioneTour = v.TourAssociato
where v.DataPartenzaViaggio > curdate(); 
END
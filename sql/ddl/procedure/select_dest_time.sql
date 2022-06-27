CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_dest_time`(
in idv int)
BEGIN
select distinct
   m.NomeMeta,
   m.TipologiaMeta,
   v.DataArrivo,
   v.OraArrivo,
   v.DataPartenza,
   v.OraPartenza
from visita as v
join meta as m on v.MetaVisitata = m.IdMeta
join viaggio as vi on v.ViaggioRelativo = vi.idviaggio
where v.idviaggio = vgg ;
END
CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_dest_tour`(
in idv int)
BEGIN
select 
   m.NomeMeta,
   v.DataArrivo,
   v.OraArrivo,
   v.DataPartenza,
   v.OraPartenza,
   v.Supplemento,
   m.TipologiaMeta,
   v.Guida,
   m.OrarioDiApertura,
   v.Trattamento,
   m.CategoriaAlbergo
from visita as v
join meta as m on v.MetaVisitata = m.IdMeta
join viaggio as vi on m.ViaggioRelativo = vi.idviaggio
where m.ViaggioRelativo = idv;
END
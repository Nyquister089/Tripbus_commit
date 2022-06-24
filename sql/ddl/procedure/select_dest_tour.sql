CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_dest_tour`(
in idv int)
BEGIN
select distinct
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
   m.CategoriaAlbergo,
   d.DescrizioneFoto,
   d.Immagine, 
   m.IdMeta
   
   
from visita as v
join meta as m on v.MetaVisitata = m.IdMeta
join viaggio as vi on v.ViaggioRelativo = vi.idviaggio
join fme as f on m.IdMeta = f.MetaRappresentata
join documentazionefotografica as d on f.FotoMeta = d.idDocumentazioneFotografica
where v.ViaggioRelativo = idv;
END
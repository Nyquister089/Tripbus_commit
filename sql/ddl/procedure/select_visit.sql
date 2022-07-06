create procedure if not exists `tripdb`.`select_visit`(
    in idv int
)
begin
select 
t.DenominazioneTour,
v.ViaggioRelativo,
m.NomeMeta,
v.MetaVisitata,
v.DataArrivo,  
v.OraArrivo,
v.DataPartenza,
v.OraPartenza, 
v.Guida,
v.Supplemento, 
v.Trattamento

from visita as v
join viaggio as via on v.ViaggioRelativo = via.idviaggio
join meta as m on v.MetaVisitata = m.IdMeta
join tour as t on via.TourAssociato = t.DenominazioneTour

where v.idvisita = idv; 
end
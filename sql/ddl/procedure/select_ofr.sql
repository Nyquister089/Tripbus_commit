create procedure if not exists `tripdb`.`select_ofr` (
    in lbr int,
    in srv int 
)
begin
select 
m.NomeMeta,
s.NomeServizio,
s.DescrizioneServizio
from offre as o 
join meta as m on o.AlbergoOfferente = m.IdMeta
join servizio as s on o.ServizioOfferto = s.IdServizio
where o.AlbergoOfferente = lbr and o.ServizioOfferto = srv; 
end
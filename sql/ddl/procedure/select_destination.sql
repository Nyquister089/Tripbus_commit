create procedure if not exists `tripdb`.`select_destination`(
    in idm int
)
begin
select 
m.NomeMeta,
m.TipologiaMeta,  
m.LocalitaDiAppartenenza, 
m.Indirizzo,
m.TelefonoMeta,
m.EmailMeta, 
m.FaxMeta,
m.CategoriaAlbergo, 
m.OrarioDiApertura

from meta as m
join localita as l on m.LocalitaDiAppartenenza = l.NomeLocalita
where m.IdMeta = idm; 
end
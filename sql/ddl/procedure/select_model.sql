create procedure if not exists `tripdb`.`select_model`(
    in idm int
)
begin
select 
m.NomeModello,
m.CasaCostruttrice,
m.DatiTecnici,
m.NumeroPosti
from modello as m 
where m.IdModello = idm; 
end
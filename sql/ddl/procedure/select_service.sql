create procedure if not exists `tripdb`.`select_service` (
in ids int
)
begin
select 
s.NomeServizio,
s.DescrizioneServizio
from servizio as s
where s.IdServizio = ids; 
end
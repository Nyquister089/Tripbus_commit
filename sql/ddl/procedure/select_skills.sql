create procedure if not exists `tripdb`.`select_skills` (
in mch int, 
in mdl varchar(45)
)
begin
select
d.NomeDipendente,
d.TelefonoAziendale
from competenze as c
join dipendente as d on c.MeccanicoCompetente = d.IdDipendente
join modello as m on c.CompetenzeModello = m.NomeModello
where c.CompetenzeModello = mdl and c.MeccanicoCompetente = mch;
end

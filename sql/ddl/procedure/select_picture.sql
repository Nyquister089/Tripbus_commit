create procedure if not exists `tripdb`.`select_picture`(
in idf int
)
begin
select
d.Immagine, 
d.DescrizioneFoto
from documentazionefotografica as d
where d.idDocumentazioneFotografica = idf; 
end
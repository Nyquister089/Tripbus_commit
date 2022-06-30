create procedure if not exists `tripdb`.`select_fmo` (
    in fml int, 
    in mdl Varchar(45)
)
begin
select 
	d.DescrizioneFoto,
	d.Immagine
       

    from fmo as f
    join documentazionefotografica as d on f.FotoModello = d.idDocumentazioneFotografica
    join modello as m on f.ModelloRappresentato = m.NomeModello
    WHERE f.FotoModello = fml  and m.NomeModello = mdl;
end
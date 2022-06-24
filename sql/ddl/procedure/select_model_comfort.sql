CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_model_comfort`(
in nmd varchar(45)
)
BEGIN
select distinct
	m.CasaCostruttrice,
	m.NumeroPosti,
	c.NomeComfort, 
	c.DescrizioneComfort,
	d.Immagine, 
	d.DescrizioneFoto,
    d.idDocumentazioneFotografica
from modello as m
join presenti as p on m.NomeModello = p.ModelloAssociato
join comfort as c on  p.ComfortPresenti = c.IdComfort
join fmo as f on m.NomeModello = f.ModelloRappresentato
join documentazionefotografica as d on f.FotoModello = d.idDocumentazioneFotografica
where m.NomeModello = nmd; 
END
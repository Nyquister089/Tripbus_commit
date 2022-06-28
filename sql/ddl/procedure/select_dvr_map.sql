CREATE PROCEDURE IF NOT EXISTS `tripdb`.`select_dvr_map`(
in lcl varchar(45)
)
BEGIN
SELECT distinct 
    m.Citta,
	m.Dettaglio,
    m.Zona,
    m.ImmagineMappa	
from mappa as m
join localita as l on m.LocalitaRappresentata = l.NomeLocalita
join meta as me on l.NomeLocalita = me.LocalitaDiAppartenenza
where m.LocalitaRappresentata = lcl;
END



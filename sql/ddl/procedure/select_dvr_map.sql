CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_dvr_map`(
in nml varchar(45)
)
BEGIN
SELECT m.Citta,
	m.Dettaglio,
    m.Zona,
    m.ImmagineMappa	
from mappa as m
join localita as l on m.LocalitaRappresentata = l.NomeLocalita
join meta as me on l.NomeLocalita = me.LocalitaDiAppartenenza
where l.NomeLocalita = nml;
END



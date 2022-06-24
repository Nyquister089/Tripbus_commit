CREATE PROCEDURE `select_hotel_service` (
in idh int )
BEGIN
	select 
			s.NomeServizio,
			s.DescrizioneServizio
	from servizio as s 
    join offre as o on s.IdServizio = o.ServizioOfferto
    join meta as m on o.AlbergoOfferente = m.IdMeta
    where IdMeta = idh; 
END

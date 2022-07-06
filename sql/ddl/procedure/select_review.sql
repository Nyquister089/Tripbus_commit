create procedure if not exists `tripdb`.`select_review`(
in idr int
)
BEGIN
SELECT  
   r.MezzoRevisionato,
   r.AddettoAllaRevisione, 
   r.DataInizio,
   r.DataFine,
   r.Chilometraggio,
   r.ControlliEffettuati,
   r.TipologiaRevisione,
   r.Motivazione 
FROM revisione as r
join mezzo as m on r.MezzoRevisionato = m.Targa
join dipendente as d on r.AddettoAllaRevisione = d.IdDipendente
WHERE r.IdRevisione = idr; 
END

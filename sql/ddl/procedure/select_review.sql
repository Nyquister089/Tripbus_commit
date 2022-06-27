CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_review`(
INOUT idr int
)
BEGIN
SELECT  
   IdRevisione ,
   MezzoRevisionato,
   AddettoAllaRevisione, 
   DataInizio,
   DataFine,
   Chilometraggio,
   ControlliEffettuati,
   TipologiaRevisione,
   Motivazione 
FROM revisione
WHERE IdRevisione = idr; 
END

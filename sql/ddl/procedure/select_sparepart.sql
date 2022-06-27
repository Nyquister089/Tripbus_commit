CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_sparepart`(
INOUT cdc VARCHAR(45)
)
BEGIN
SELECT  
   Codice,
   CostoUnitario,
   QuantitaDiRiordino,
   Descrizione,
   ScortaMinima,
   QuantitaMagazzino
FROM ricambio
WHERE Codice = cdc; 
END
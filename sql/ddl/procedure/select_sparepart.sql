CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_sparepart`(
INOUT cdc VARCHAR(45)
)
BEGIN
SELECT  
   Codice,
   CostoUnitario,
   QuantitàDiRiordino,
   Descrizione,
   ScortaMinima,
   QuantitàMagazzino
FROM ricambio
WHERE Codice = cdc; 
END
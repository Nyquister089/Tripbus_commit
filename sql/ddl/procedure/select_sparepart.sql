create procedure if not exists `tripdb`.`select_sparepart`(
in cdc VARCHAR(45)
)
BEGIN
SELECT  
   r.CostoUnitario,
   r.QuantitaDiRiordino,
   r.Descrizione,
   r.ScortaMinima,
   r.QuantitaMagazzino
FROM ricambio as r
WHERE r.Codice = cdc; 
END
CREATE DEFINER=`giordano`@`localhost` PROCEDURE `update_spareparts_number`(
in cdc varchar(45),
in nmr int
)
BEGIN

update ricambio as r
set r.QuantitaMagazzino = nmr
where r.Codice = cdc; 
END
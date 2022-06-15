CREATE DEFINER=`giordano`@`localhost` 
PROCEDURE `validate_reservation`(IN ndp DATE, IN ddc DATE, IN dds DATE)
BEGIN 
UPDATE prenotazione AS p
SET p.DataDiConferma = ddc, 
    p.DataSaldo = dds
WHERE p.NumeroDiPrenotazione = ndp; 

END
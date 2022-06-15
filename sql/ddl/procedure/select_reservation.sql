CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_reservation`(IN res int)
BEGIN
SELECT *
FROM prenotazione
WHERE prenotazione.NumeroDiPrenotazione = res; 
END
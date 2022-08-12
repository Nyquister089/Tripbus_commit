CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_reservation`(
    in npr int
    )
BEGIN
SELECT
 p.ClientePrenotante, 
 p.DataDiPrenotazione,
 p.DataDiConferma, 
 p.DataSaldo
FROM prenotazione as p
JOIN cliente as c on p.ClientePrenotante = c.EmailCliente
WHERE NumeroDiPrenotazione = npr;
END
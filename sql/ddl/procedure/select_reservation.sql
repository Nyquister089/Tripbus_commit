CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_reservation`(
    in res int,
    out cli varchar(45),
    out ddp date,
    out ddc date,
    out dds date
    )
BEGIN


SELECT
 ClientePrenotante, 
 DataDiPrenotazione,
 DataDiConferma, 
 DataSaldo
INTO 
	cli, 
    ddp,
    ddc, 
    dds
FROM prenotazione as p
JOIN cliente as c on p.ClientePrenotante = c.EmailCliente
WHERE NumeroDiPrenotazione = res;
END
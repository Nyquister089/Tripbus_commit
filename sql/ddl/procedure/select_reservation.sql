CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_reservation`(
    inout res int,
    out cli varchar(45),
    out ddp date,
    out ddc date,
    out dds date
    )
BEGIN


SELECT NumeroDiprenotazione, ClientePrenotante, DataDiPrenotazione, DataDiConferma, DataSaldo
FROM prenotazione
WHERE NumeroDiPrenotazione = res;
SET  res = NumeroDiprenotazione, 
	 cli = ClientePrenotante, 
     ddp = DataDiPrenotazione, 
     ddc = DataDiConferma, 
     dds = DataSaldo; 

END
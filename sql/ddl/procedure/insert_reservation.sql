CREATE DEFINER=`giordano`@`localhost` PROCEDURE `insert_reservation`( 
IN num INTEGER, IN cli VARCHAR(45), IN dp DATE, IN dc DATE, IN ds DATE)
BEGIN
INSERT INTO prenotazione
			(NumeroDiPrenotazione,
			 ClientePrenotante,
			 DataDiPrenotazione,
			 DataDiConferma,
			 DataSaldo)
		VALUES
			(num,
             cli, 
             dp,
             dc, 
             ds);
END
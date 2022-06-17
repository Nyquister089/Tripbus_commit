CREATE DEFINER=`giordano`@`localhost` PROCEDURE `insert_reservation`( 
 IN cli VARCHAR(45), 
 IN dp DATE
 )
BEGIN
INSERT INTO prenotazione
			(ClientePrenotante,
			 DataDiPrenotazione
             )
		VALUES
			(cli, 
             dp
             );
END
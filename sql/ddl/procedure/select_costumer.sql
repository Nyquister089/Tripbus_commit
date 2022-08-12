CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_costumer`(
IN eml VARCHAR(45)
)

BEGIN
SELECT	
	c.NomeCliente, 
    c.CognomeCliente, 
    c.IndirizzoCliente, 
    c.CodiceFiscale, 
    c.DataDocumentazione, 
    c.RecapitoTelefonico, 
	c.Fax
FROM cliente as c
WHERE c.EmailCliente = eml;

END
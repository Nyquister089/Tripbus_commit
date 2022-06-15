CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_costumer`(
INOUT eml VARCHAR(45),
OUT nmc VARCHAR (45),
OUT cgn VARCHAR (45), 
OUT inc VARCHAR (45), 
OUT cdf VARCHAR(45), 
OUT ddc DATE, 
OUT tel VARCHAR(45), 
OUT fax VARCHAR(45))
BEGIN
SELECT c.EmailCliente, 	
	c.NomeCliente, 
    c.CognomeCliente, 
    c.IndirizzoCliente, 
    c.CodiceFiscale, 
    c.DataDocumentazione, 
    c.RecapitoTelefonico, 
	c.Fax
FROM cliente as c
WHERE c.EmailCliente = eml;

SET eml = c.EmailCliente, 	
	nmc = c.NomeCliente, 
    cgn = c.CognomeCliente, 
    inc = c.IndirizzoCliente, 
    cdf = c.CodiceFiscale, 
    ddc = c.DataDocumentazione, 
    tel = c.RecapitoTelefonico, 
    fax = c.Fax;
/*SELECT CONVERT (select_costumer USING utf8) COLLATE utf8_general_ci; */

END
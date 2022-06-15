CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_costumer`(
INOUT eml VARCHAR(45),
OUT nmc NVARCHAR (45),
OUT cgn NVARCHAR (45), 
OUT inc NVARCHAR (45), 
OUT cdf NVARCHAR(45), 
OUT ddc DATE, 
OUT tel NVARCHAR(45), 
OUT fax NVARCHAR(45))
BEGIN
SELECT *
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
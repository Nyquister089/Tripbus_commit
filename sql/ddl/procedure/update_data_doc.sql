CREATE DEFINER=`giordano`@`localhost` PROCEDURE `update_data_doc`(IN cli NVARCHAR (45), IN dat DATE )
BEGIN
UPDATE cliente AS c
SET c.DataDocumentazione = dat
WHERE c.EmailCliente = cli; 
END
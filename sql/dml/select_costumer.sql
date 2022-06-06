CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_costumer`(IN cli Nvarchar(45))
BEGIN
SELECT *
FROM cliente 
WHERE cliente.EmailCliente = cli; 
END
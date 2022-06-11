CREATE DEFINER=`giordano`@`localhost` PROCEDURE `insert_costumer`(
in em varchar(45), in nom varchar(45), in cog varchar(45), in ind varchar(45), 
in cod varchar(45), in dat date, in rec int, in fa int)
BEGIN
insert into cliente 
			(EmailCLiente, 
             NomeCliente, 
             CognomeCLiente, 
             IndirizzoCliente, 
             CodiceFiscale, 
             DataDocumentazione, 
             RecapitoTelefonico, 
             Fax)
values
			(em, 
             nom, 
             cog,
             ind, 
             cod, 
             dat, 
             rec,
             fa); 
END
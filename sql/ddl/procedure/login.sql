CREATE DEFINER=`giordano`@`localhost` PROCEDURE `login`(
	IN usrn VARCHAR(45), 
    IN pass VARCHAR(8),
    OUT tip INT
)
BEGIN
	SELECT u.TipoUtente
    FROM utente as u
    WHERE u.EmailUtente = usrn AND u.Pswrd = pass;
    SET tip = u.TipoUtente; 
END
CREATE PROCEDURE `login`(
	IN usrn VARCHAR(45), 
    IN pass VARCHAR(8),
    OUT tip INT
)
BEGIN
    SET tip = -1;

	SELECT u.TipoUtente
    INTO tip
    FROM utente as u
    WHERE u.EmailUtente = usrn AND u.Pswrd = pass;
END
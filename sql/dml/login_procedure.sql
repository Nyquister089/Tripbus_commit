CREATE DEFINER=`giordano`@`localhost` PROCEDURE `login`(
	IN usrn NVARCHAR(45), IN pass VARCHAR(8), OUT tip VARCHAR (45)
)
BEGIN 
DECLARE msg VARCHAR(45);

			SELECT u.TipoUtente 
			FROM utente AS u 
            WHERE u.EmailUtente = usrn AND u.Pswrd = pass;
            SET tip = u.TipoUtente; 
            SELECT @tip; 
END
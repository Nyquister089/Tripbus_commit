CREATE DEFINER=`giordano`@`localhost` PROCEDURE `login`(
	IN usrn NVARCHAR(45), IN pass VARCHAR(8), OUT tip VARCHAR (45)
)
BEGIN 
DECLARE msg VARCHAR(45);
IF EXISTS(SELECT u.IdUtente, u.TipoUtente 
			FROM utente AS u 
            WHERE u.EmailUtente = usrn AND u.Pswrd = pass) THEN
			SELECT @u.TipoUtente 
			FROM utente AS u 
            WHERE u.EmailUtente = usrn AND u.Pswrd = pass;          
	
	ELSE
			SET msg = 'Credenziali errate';
            select @msg; 
	END IF;
END
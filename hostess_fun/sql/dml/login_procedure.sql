CREATE DEFINER=`giordano`@`localhost` PROCEDURE `login_procedure`(
	IN usrn NVARCHAR(45), IN pass NVARCHAR(8)
)
BEGIN
IF EXISTS(SELECT u.Idutente, u.TipoUtente FROM utente AS u WHERE u.EmailUtente = usrn AND u.Password = pass) THEN
		SET @msg = u.TipologiaUtente; 
	ELSE
		SET @msg = 'Credenziali errate';
	END IF;
END
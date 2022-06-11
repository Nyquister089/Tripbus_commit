
DROP PROCEDURE IF EXISTS `tripdb`.`login`;

CREATE PROCEDURE IF NOT EXISTS `tripdb`.`login`(
	IN usrn VARCHAR(45), IN pass VARCHAR(8),OUT tip INT
)
BEGIN
	SELECT u.role 
    INTO tip
    FROM utente
    WHERE u.utente = usrn AND u.pass = pass;
END

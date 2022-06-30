CREATE PROCEDURE IF NOT EXISTS `tripdb`.`select_employee`(
    IN id int
    )
BEGIN
     SELECT  
    NomeDipendente, 
    CognomeDipendente,
    TipologiaDipendente, 
    TelefonoAziendale
FROM dipendente
    WHERE IdDipendente = id;
END;
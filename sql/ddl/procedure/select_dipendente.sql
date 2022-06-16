CREATE PROCEDURE IF NOT EXISTS `tripdb`.`select_dipendente`(IN id int)
BEGIN
    SELECT IdDipendente, TipologiaDipendente, TelefonoAziendale, NomeDipendente, CognomeDipendente
    FROM tripdb.dipendente
    WHERE IdDipendente = id;
END;
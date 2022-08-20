CREATE 
    ALGORITHM = UNDEFINED 

    SQL SECURITY DEFINER
VIEW `Meccanico_pianifica_revisione` AS
    SELECT 
        `m`.`Targa` AS `Targa`
    FROM
        (`mezzo` `m`
        JOIN `revisione` `r` ON ((`m`.`Targa` = `r`.`MezzoRevisionato`)))
    WHERE
        ((`m`.`ValoreContaKm` - `r`.`Chilometraggio`) >= '50000')
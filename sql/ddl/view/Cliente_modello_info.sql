CREATE 
    ALGORITHM = UNDEFINED 

    SQL SECURITY DEFINER
VIEW `Cliente_modello_info` AS
    SELECT 
        `m`.`NomeModello` AS `NomeModello`,
        `c`.`NomeComfort` AS `NomeComfort`,
        `c`.`DescrizioneComfort` AS `DescrizioneComfort`,
        `d`.`Immagine` AS `Immagine`
    FROM
        ((((`modello` `m`
        JOIN `presenti` `p` ON ((`m`.`NomeModello` = `p`.`ModelloAssociato`)))
        JOIN `comfort` `c` ON ((`p`.`ComfortPresenti` = `c`.`IdComfort`)))
        JOIN `fmo` ON ((`m`.`NomeModello` = `fmo`.`ModelloRappresentato`)))
        JOIN `documentazionefotografica` `d` ON ((`fmo`.`FotoModello` = `d`.`Immagine`)))
    WHERE
        (`m`.`NomeModello` = 'mod')
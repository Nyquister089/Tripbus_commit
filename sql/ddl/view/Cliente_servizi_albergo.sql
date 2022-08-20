
CREATE 
    ALGORITHM = UNDEFINED 

    SQL SECURITY DEFINER
VIEW `Cliente_servizi_albergo` AS
    SELECT 
        `m`.`NomeMeta` AS `NomeMeta`,
        `s`.`NomeServizio` AS `NomeServizio`,
        `s`.`DescrizioneServizio` AS `DescrizioneServizio`
    FROM
        ((`meta` `m`
        JOIN `offre` `o` ON ((`m`.`IdMeta` = `o`.`IdAlbergo`)))
        JOIN `servizio` `s` ON ((`o`.`IdServizio` = `s`.`IdServizio`)))
    WHERE
        (`m`.`NomeMeta` = 'nom')
        
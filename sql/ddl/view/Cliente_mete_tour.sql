CREATE 
    ALGORITHM = UNDEFINED 

    SQL SECURITY DEFINER
VIEW `Cliente_mete_tour` AS
    SELECT 
        `t`.`DenominazioneTour` AS `DenominazioneTour`,
        `m`.`NomeMeta` AS `NomeMeta`,
        `d`.`Immagine` AS `Immagine`
    FROM
        ((((`meta` `m`
        JOIN `fme` ON ((`m`.`IdMeta` = `fme`.`MetaRappresentata`)))
        JOIN `documentazionefotografica` `d` ON ((`fme`.`FotoMeta` = `d`.`Immagine`)))
        JOIN `tome` ON ((`m`.`IdMeta` = `tome`.`MetaInclusa`)))
        JOIN `tour` `t` ON ((`tome`.`TourRelativo` = `t`.`DenominazioneTour`)))
    WHERE
        (`t`.`DenominazioneTour` = 'Den')
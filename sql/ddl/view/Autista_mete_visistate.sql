USE `tripdb`; 
CREATE
    ALGORITHM = UNDEFINED
    SQL SECURITY DEFINER
VIEW `tripdb`.`Autista_mete_visitate` AS
    SELECT 
        `m`.`IdMeta` AS `IdMeta`,
        `m`.`NomeMeta` AS `NomeMeta`,
        `m`.`TipologiaMeta` AS `TipologiaMeta`,
        `m`.`LocalitaDiAppartenenza` AS `LocalitaDiAppartenenza`,
        `m`.`Indirizzo` AS `Indirizzo`,
        `v`.`DataArrivo` AS `DataArrivo`,
        `v`.`OraArrivo` AS `OraArrivo`,
        `v`.`DataPartenza` AS `DataPartenza`,
        `v`.`OraPartenza` AS `OraPartenza`
    FROM
        ((`meta` `m`
        JOIN `visita` `v` ON ((`m`.`IdMeta` = `v`.`MetaVisitata`)))
        JOIN `viaggio` `via` ON ((`v`.`ViaggioRelativo` = `via`.`idviaggio`)))
    WHERE
        ((`via`.`IdConducente` = '1')
            AND (`via`.`DataPartenzaViaggio` = '30/04/1989'))
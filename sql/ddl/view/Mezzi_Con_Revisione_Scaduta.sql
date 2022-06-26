CREATE VIEW `tripdb`.`Mezzi_Con_Revisione_Scaduta` AS
SELECT 
`ur`.`Targa`,
`ur`.`DataFine` as `DataFineUltimaRevisione`,
date_add(`ur`.`DataFine`, INTERVAL 1 YEAR) as `ScadenzaUltimaRevisione`,
`m`.`ValoreContaKm` as `AttualeChilometraggioMezzo`,
`r`.`Chilometraggio` as `ChilometraggioMezzoInUltimaRevisione`
FROM
(SELECT 
`r`.`MezzoRevisionato` as `Targa`, 
MAX(`r`.`DataFine`) as `DataFine`
FROM `tripdb`.`revisione` `r`
GROUP BY `r`.`MezzoRevisionato`) as `ur`
JOIN `tripdb`.`mezzo` as `m` ON `ur`.`Targa` = `m`.`Targa`
JOIN `tripdb`.`revisione` as `r` ON `ur`.`DataFine` = `r`.`DataFine`
WHERE date_add(`ur`.`DataFine`, INTERVAL 1 YEAR) <= CURDATE()
OR `m`.`ValoreContaKm` - `r`.`Chilometraggio` >= 38000
;
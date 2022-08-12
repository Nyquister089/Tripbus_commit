CREATE TABLE IF NOT EXISTS `tripdb`.`prenotazione` (
  `NumeroDiPrenotazione` int unsigned NOT NULL AUTO_INCREMENT,
  `ClientePrenotante` varchar(45) NOT NULL,
  `DataDiPrenotazione` DATE NOT NULL,
  `DataDiConferma` DATE DEFAULT NULL,
  `DataSaldo` DATE DEFAULT NULL,
  PRIMARY KEY (`NumeroDiPrenotazione`),
  UNIQUE KEY `NumeroDiPrenotazione_UNIQUE` (`NumeroDiPrenotazione`),
  CONSTRAINT `ClientePrenotatne` FOREIGN KEY (`ClientePrenotante`) REFERENCES `cliente` (`EmailCliente`) on delete cascade,
  CONSTRAINT `DataDiConfermaCannotBeLesserThanDataDiPrenotazione` CHECK (`DataDiConferma` IS NULL OR `DataDiConferma` >= `DataDiPrenotazione`),
  CONSTRAINT `DataSaldoCannotBeLesserThanDataDiConferma` CHECK (`DataSaldo` IS NULL OR (`DataDiConferma` IS NOT NULL AND `DataSaldo` >= `DataDiConferma`))
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
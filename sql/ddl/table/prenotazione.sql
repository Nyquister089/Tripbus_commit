CREATE TABLE IF NOT EXISTS `tripdb`.`prenotazione` (
  `NumeroDiPrenotazione` int unsigned NOT NULL AUTO_INCREMENT,
  `ClientePrenotante` int unsigned NOT NULL,
  `DataDiPrenotazione` datetime NOT NULL,
  `DataDiConferma` datetime DEFAULT NULL,
  `DataSaldo` datetime DEFAULT NULL,
  PRIMARY KEY (`NumeroDiPrenotazione`),
  UNIQUE KEY `NumeroDiPrenotazione_UNIQUE` (`NumeroDiPrenotazione`),
  UNIQUE KEY `ClientePrenotante_UNIQUE` (`ClientePrenotante`),
  CONSTRAINT `ClientePrenotatne` FOREIGN KEY (`ClientePrenotante`) REFERENCES `cliente` (`IdUtente`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

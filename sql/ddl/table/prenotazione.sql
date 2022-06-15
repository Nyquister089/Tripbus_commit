CREATE TABLE IF NOT EXISTS `tripdb`.`prenotazione` (
  `NumeroDiPrenotazione` int unsigned NOT NULL AUTO_INCREMENT,
  `ClientePrenotante` varchar(45) NOT NULL,
  `DataDiPrenotazione` datetime NOT NULL,
  `DataDiConferma` datetime DEFAULT NULL,
  `DataSaldo` datetime DEFAULT NULL,
  PRIMARY KEY (`NumeroDiPrenotazione`),
  UNIQUE KEY `NumeroDiPrenotazione_UNIQUE` (`NumeroDiPrenotazione`),
  UNIQUE KEY `ClientePrenotante_UNIQUE` (`ClientePrenotante`),
  CONSTRAINT `ClientePrenotatne` FOREIGN KEY (`ClientePrenotante`) REFERENCES `cliente` (`EmailCliente`)
) ENGINE=InnoDB CHARSET=utf8 COLLATE = utf8_general_ci;

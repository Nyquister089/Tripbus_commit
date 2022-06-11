CREATE TABLE IF NOT EXISTS `tripdb`.`mezzo` (
  `Targa` varchar(10) NOT NULL,
  `ModelloMezzo` varchar(45) NOT NULL,
  `DataRevisioneMotorizzazione` varchar(45) NOT NULL,
  `Autonomia` int unsigned NOT NULL,
  `ValoreContaKm` int unsigned NOT NULL,
  `Ingombri` varchar(45) NOT NULL,
  `DataImmatricolazione` date NOT NULL,
  `Mezzocol` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`Targa`),
  UNIQUE KEY `Targa_UNIQUE` (`Targa`),
  KEY `ModelloMezzo_idx` (`ModelloMezzo`),
  CONSTRAINT `ModelloMezzo` FOREIGN KEY (`ModelloMezzo`) REFERENCES `modello` (`NomeModello`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

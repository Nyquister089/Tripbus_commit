CREATE TABLE IF NOT EXISTS `tripdb`.`viaggio` (
  `idviaggio` int NOT NULL AUTO_INCREMENT,
  `TourAssociato` varchar(45) NOT NULL,
  `IdConducente` int unsigned NOT NULL,
  `IdAccompagnatrice` int unsigned DEFAULT NULL,
  `TargaMezzoImpiegato` varchar(10) NOT NULL,
  `DataPartenzaViaggio` date DEFAULT NULL,
  `DataRitornoViaggio` date DEFAULT NULL, 
  `CostoDelViaggio` decimal(18,2) NOT NULL,
  `NumeroKm` int NOT NULL,
  `PostiDisponibili` int NOT NULL,
  `DataCancellazione` datetime DEFAULT NULL,
  PRIMARY KEY (`idviaggio`),
  UNIQUE KEY `idviaggio_UNIQUE` (`idviaggio`),
  KEY `FK_TourAssocciato_idx` (`TourAssociato`),
  KEY `FK_IdConducente_idx` (`IdConducente`),
  KEY `FK_Mezzoimpiegato_idx` (`TargaMezzoImpiegato`),
  CONSTRAINT `FK_IdAccompagnatrice` FOREIGN KEY (`IdConducente`) REFERENCES `dipendente` (`IdDipendente`),
  CONSTRAINT `FK_IdConducente` FOREIGN KEY (`IdConducente`) REFERENCES `dipendente` (`IdDipendente`),
  CONSTRAINT `FK_Mezzoimpiegato` FOREIGN KEY (`TargaMezzoImpiegato`) REFERENCES `mezzo` (`Targa`),
  CONSTRAINT `FK_TourAssocciato` FOREIGN KEY (`TourAssociato`) REFERENCES `tour` (`DenominazioneTour`),
  CONSTRAINT `DataRitornoViaggioCannotBeLesserThanDataPartenzaViaggio` CHECK ((`DataRitornoViaggio` IS NULL) OR (`DataPartenzaViaggio` IS NULL AND `DataRitornoViaggio` IS NULL) OR (`DataRitornoViaggio` >= `DataPartenzaViaggio`))
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

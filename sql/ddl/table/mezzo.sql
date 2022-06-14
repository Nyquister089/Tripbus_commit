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
  KEY `FK_modello_idx` (`ModelloMezzo`),
  CONSTRAINT `FK_ModelloMezzo` FOREIGN KEY (`ModelloMezzo`) REFERENCES `modello` (`NomeModello`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

/*
PRIMARY KEY (`MetaRappresentata`,`FotoMeta`),
  KEY `FK_documentazioneFotografica_idx` (`FotoMeta`),
  CONSTRAINT `FK_documentazioneFotografica` FOREIGN KEY (`FotoMeta`) REFERENCES `documentazionefotografica` (`idDocumentazioneFotografica`),
  CONSTRAINT `FK_Meta` FOREIGN KEY (`MetaRappresentata`) REFERENCES `meta` (`IdMeta`)*/


CREATE TABLE IF NOT EXISTS `tripdb`.`associata` (
  `CameraPrenotata` int NOT NULL,
  `Ospite` int unsigned NOT NULL,
  `AlbergoInQuestione` int unsigned NOT NULL,
  `DataInizioSoggiorno` DATE NOT NULL, 
  `DataFineSoggiorno` DATE NOT NULL,
  PRIMARY KEY (`CameraPrenotata`,`Ospite`,`AlbergoInQuestione`),
  KEY `AlbergoInQuestione_idx` (`AlbergoInQuestione`),
  KEY `Ospite_idx` (`Ospite`),
  CONSTRAINT `FK_AlbergoInQuestione` FOREIGN KEY (`AlbergoInQuestione`) REFERENCES `camera` (`IdAlbergo`),
  CONSTRAINT `FK_Camera` FOREIGN KEY (`CameraPrenotata`) REFERENCES `camera` (`NumeroCamera`),
  CONSTRAINT `FK_Ospite` FOREIGN KEY (`Ospite`) REFERENCES `postoprenotato` (`NumeroDiPosto`),
  CONSTRAINT `DataFineSoggiornoCannotBeLesserThanDataDiInizioSoggiorno` CHECK (`DataInizioSoggiorno` <= `DataFineSoggiorno`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

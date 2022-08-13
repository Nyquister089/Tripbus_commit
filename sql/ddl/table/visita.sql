CREATE TABLE IF NOT EXISTS `tripdb`.`visita` (
  `idvisita` int NOT NULL AUTO_INCREMENT,
  `ViaggioRelativo` int NOT NULL,
  `MetaVisitata` int unsigned,
  `DataArrivo` date NOT NULL,
  `OraArrivo` time NOT NULL,
  `DataPartenza` date NOT NULL,
  `OraPartenza` time NOT NULL,
  `Guida` tinyint DEFAULT NULL,
  `Supplemento` decimal(8,2) DEFAULT NULL,
  `Trattamento` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idvisita`),
  KEY `FK_ViaggioRelativo_idx` (`ViaggioRelativo`),
  KEY `FK_MetaVisitata_idx` (`MetaVisitata`),
  CONSTRAINT `FK_MetaVisitata` FOREIGN KEY (`MetaVisitata`) REFERENCES `meta` (`IdMeta`)on delete set null,
  CONSTRAINT `FK_ViaggioRelativo` FOREIGN KEY (`ViaggioRelativo`) REFERENCES `viaggio` (`idviaggio`) on delete cascade,
  CONSTRAINT `DataArrivoCannotBeLesserThanDataPartenza` CHECK (`DataArrivo` >= `DataPartenza`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci COMMENT='    ';

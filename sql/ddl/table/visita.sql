CREATE TABLE IF NOT EXISTS `tripdb`.`visita` (
  `idvisita` int NOT NULL AUTO_INCREMENT,
  `ViaggioRelativo` int NOT NULL,
  `MetaVisitata` int unsigned NOT NULL,
  `DataArrivo` date NOT NULL,
  `OraArrivo` time NOT NULL,
  `DataPartenza` date NOT NULL,
  `OraPartenza` time NOT NULL,
  `Guida` tinyint DEFAULT NULL,
  `Supplemento` decimal(18,2) DEFAULT NULL,
  `Trattamento` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idvisita`),
  KEY `FK_ViaggioRelativo_idx` (`ViaggioRelativo`),
  KEY `FK_MetaVisitata_idx` (`MetaVisitata`),
  CONSTRAINT `FK_MetaVisitata` FOREIGN KEY (`MetaVisitata`) REFERENCES `meta` (`IdMeta`),
  CONSTRAINT `FK_ViaggioRelativo` FOREIGN KEY (`ViaggioRelativo`) REFERENCES `viaggio` (`idviaggio`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci COMMENT='    ';

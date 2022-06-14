CREATE TABLE IF NOT EXISTS `tripdb`.`revisione` (
  `IdRevisione` int unsigned NOT NULL AUTO_INCREMENT,
  `MezzoRevisionato` varchar(10) NOT NULL,
  `DataInizio` datetime NOT NULL,
  `DataFine` datetime NOT NULL,
  `Chilometraggio` int unsigned NOT NULL,
  `ControlliEffettuati` varchar(1000) NOT NULL,
  `TipologiaRevisione` varchar(45) NOT NULL,
  `Motivazione` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`IdRevisione`),
  UNIQUE KEY `IdRevisione_UNIQUE` (`IdRevisione`),
  KEY `FK_revisione_mezzo_idx` (`MezzoRevisionato`),
  CONSTRAINT `FK_revisione_mezzo` FOREIGN KEY (`MezzoRevisionato`) REFERENCES `mezzo` (`Targa`)
) ENGINE=InnoDB DEFAULT DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

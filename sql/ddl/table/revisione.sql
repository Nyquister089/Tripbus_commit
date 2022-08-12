CREATE TABLE IF NOT EXISTS `tripdb`.`revisione` (
  `IdRevisione` int unsigned NOT NULL AUTO_INCREMENT,
  `MezzoRevisionato` varchar(45),
  `AddettoAllaRevisione` int unsigned, 
  `DataInizio` datetime NOT NULL,
  `DataFine` datetime NOT NULL,
  `Chilometraggio` int unsigned NOT NULL,
  `ControlliEffettuati` varchar(5000) NOT NULL,
  `TipologiaRevisione` varchar(45) NOT NULL,
  `Motivazione` varchar(5000) DEFAULT NULL,
  PRIMARY KEY (`IdRevisione`),
  UNIQUE KEY `IdRevisione_UNIQUE` (`IdRevisione`),
  KEY `FK_revisione_mezzo_idx` (`MezzoRevisionato`),
  KEY `Fk_revisione_dipendente_idx`(`AddettoAllaRevisione`),
  CONSTRAINT `FK_revisione_mezzo` FOREIGN KEY (`MezzoRevisionato`) REFERENCES `mezzo` (`Targa`) on delete set null,
  CONSTRAINT `FK_revisione_dipendente` FOREIGN KEY (`AddettoAllaRevisione`) REFERENCES `dipendente` (`IdDipendente`)on delete set null,
  CONSTRAINT `DataFineCannotBeLesserThanDataInizio` CHECK (`DataFine` >= `DataInizio`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
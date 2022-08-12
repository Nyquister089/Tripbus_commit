

CREATE TABLE IF NOT EXISTS `tripdb`.`sostituito` (
  `RevisioneAssociata` int unsigned NOT NULL,
  `CodiceRicambioSostituito` varchar(45) NOT NULL,
  `QuantitàSostituita` int unsigned default '1',
  PRIMARY KEY (`RevisioneAssociata`,`CodiceRicambioSostituito`),
  KEY `sostituito_ricambio_idx` (`CodiceRicambioSostituito`),
  KEY `sostituito_revisione_idx`(`RevisioneAssociata`),
  CONSTRAINT `FK_revisione` FOREIGN KEY (`RevisioneAssociata`) REFERENCES `revisione` (`IdRevisione`)on delete cascade,
  CONSTRAINT `FK_tagliando` FOREIGN KEY (`CodiceRicambioSostituito`) REFERENCES `ricambio` (`Codice`)on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
CREATE TABLE IF NOT EXISTS `tripdb`.`offre` (
  `ServizioOfferto` int NOT NULL,
  `AlbergoOfferente` int unsigned NOT NULL,
  PRIMARY KEY (`ServizioOfferto`,`AlbergoOfferente`),
  KEY `FK_IdServizio_idx` (`ServizioOfferto`),
  KEY `FK_IdAlbergo_idx` (`AlbergoOfferente`),
  CONSTRAINT `FK_IdAlbergo` FOREIGN KEY (`AlbergoOfferente`) REFERENCES `meta` (`IdMeta`)on delete cascade,
  CONSTRAINT `FK_IdServizio` FOREIGN KEY (`ServizioOfferto`) REFERENCES `servizio` (`IdServizio`)on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

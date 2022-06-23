CREATE TABLE IF NOT EXISTS `tripdb`.`offre` (
  `IdServizio` int NOT NULL,
  `IdAlbergo` int unsigned NOT NULL,
  PRIMARY KEY (`IdServizio`,`IdAlbergo`),
  KEY `FK_IdServizio_idx` (`IdServizio`),
  KEY `FK_IdAlbergo_idx` (`IdAlbergo`),
  CONSTRAINT `FK_IdAlbergo` FOREIGN KEY (`IdAlbergo`) REFERENCES `meta` (`IdMeta`),
  CONSTRAINT `FK_IdServizio` FOREIGN KEY (`IdServizio`) REFERENCES `servizio` (`IdServizio`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

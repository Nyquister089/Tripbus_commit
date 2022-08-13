CREATE TABLE IF NOT EXISTS `tripdb`.`fmo` (
  `FotoModello` int unsigned NOT NULL,
  `ModelloRappresentato` varchar(45) NOT NULL,
  PRIMARY KEY (`FotoModello`,`ModelloRappresentato`),
  KEY `FK_Modello_idx` (`ModelloRappresentato`),
  CONSTRAINT `FK_Foto` FOREIGN KEY (`FotoModello`) REFERENCES `documentazionefotografica` (`idDocumentazioneFotografica`)on delete cascade,
  CONSTRAINT `FK_Modello` FOREIGN KEY (`ModelloRappresentato`) REFERENCES `modello` (`NomeModello`)on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
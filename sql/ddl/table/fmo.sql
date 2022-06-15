CREATE TABLE IF NOT EXISTS `tripdb`.`fmo` (
  `FotoModello` int unsigned NOT NULL,
  `ModelloRappresentato` varchar(45) NOT NULL,
  PRIMARY KEY (`FotoModello`,`ModelloRappresentato`),
  KEY `FK_Modello_idx` (`ModelloRappresentato`),
  CONSTRAINT `FK_Foto` FOREIGN KEY (`FotoModello`) REFERENCES `documentazionefotografica` (`idDocumentazioneFotografica`),
  CONSTRAINT `FK_Modello` FOREIGN KEY (`ModelloRappresentato`) REFERENCES `modello` (`NomeModello`)
) ENGINE=InnoDB CHARSET=utf8 COLLATE= utf8_general_ci; 

CREATE TABLE IF NOT EXISTS `tripdb`.`documentazionefotografica` (
  `idDocumentazioneFotografica` int unsigned NOT NULL AUTO_INCREMENT,
  `Immagine` blob NOT NULL,
  `DocumentazioneFotograficacol` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idDocumentazioneFotografica`),
  UNIQUE KEY `idDocumentazioneFotografica_UNIQUE` (`idDocumentazioneFotografica`)
) ENGINE=InnoDB CHARSET=utf8 COLLATE= utf8_general_ci;

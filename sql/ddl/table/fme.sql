CREATE TABLE IF NOT EXISTS `tripdb`.`fme` (
  `MetaRappresentata` int unsigned NOT NULL,
  `FotoMeta` int unsigned NOT NULL,
  PRIMARY KEY (`MetaRappresentata`,`FotoMeta`),
  KEY `FK_documentazioneFotografica_idx` (`FotoMeta`),
  CONSTRAINT `FK_documentazioneFotografica` FOREIGN KEY (`FotoMeta`) REFERENCES `documentazionefotografica` (`idDocumentazioneFotografica`),
  CONSTRAINT `FK_Meta` FOREIGN KEY (`MetaRappresentata`) REFERENCES `meta` (`IdMeta`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

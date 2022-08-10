CREATE TABLE IF NOT EXISTS `tripdb`.`competenze` (
  `CompetenzeModello` int unsigned NOT NULL,
  `MeccanicoCompetente` int unsigned not null,
  PRIMARY KEY (`CompetenzeModello`, `MeccanicoCompetente`),
  KEY `CompetenzeModello_idx` (`CompetenzeModello`),
  KEY `MeccanicoCompetente_idx` (`MeccanicoCompetente`),
  CONSTRAINT `FK_CompetenzeModello` FOREIGN KEY (`CompetenzeModello`) REFERENCES `modello` (`IdModello`),
  CONSTRAINT `FK_MeccanicoCompetente` FOREIGN KEY (`MeccanicoCompetente`) REFERENCES `dipendente` (`IdDipendente`)


) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
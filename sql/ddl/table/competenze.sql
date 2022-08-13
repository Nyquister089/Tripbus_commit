CREATE TABLE IF NOT EXISTS `tripdb`.`competenze` (
  `CompetenzeModello` varchar(45) NOT NULL,
  `MeccanicoCompetente` int unsigned not null,
  PRIMARY KEY (`CompetenzeModello`, `MeccanicoCompetente`),
  KEY `CompetenzeModello_idx` (`CompetenzeModello`),
  KEY `MeccanicoCompetente_idx` (`MeccanicoCompetente`),
  CONSTRAINT `FK_CompetenzeModello` FOREIGN KEY (`CompetenzeModello`) REFERENCES `modello` (`NomeModello`)on delete cascade,
  CONSTRAINT `FK_MeccanicoCompetente` FOREIGN KEY (`MeccanicoCompetente`) REFERENCES `dipendente` (`IdDipendente`)on delete cascade


) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
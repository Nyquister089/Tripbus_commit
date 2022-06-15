CREATE TABLE IF NOT EXISTS `tripdb`.`meta` (
  `IdMeta` int unsigned NOT NULL AUTO_INCREMENT,
  `LocalitaDiAppartenenza` varchar(45) NOT NULL, 
  `NomeMeta` varchar(45) NOT NULL,
  `TelefonoMeta` int NOT NULL,
  `E-mailMeta` varchar(45) NOT NULL,
  `FaxMeta` varchar(45) NOT NULL,
  `Indirizzo` varchar(45) NOT NULL,
  `TipologiaMeta` varchar(45) NOT NULL,
  `CategoriaAlbergo` varchar(45) DEFAULT NULL,
  `OrarioDiApertura` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`IdMeta`),
  UNIQUE KEY `IdMeta_UNIQUE` (`IdMeta`),
  KEY `LocalitaDiappartenenza_idx` (`LocalitadiAppartenenza`),
  CONSTRAINT `FK_LocalitaDiAppartenenza` FOREIGN KEY (`LocalitaDiAppartenenza`) REFERENCES `localita` (`NomeLocalita`) 
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

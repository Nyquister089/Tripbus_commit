CREATE TABLE IF NOT EXISTS `tripdb`.`modello` (
  `IdModello` int unsigned not null AUTO_INCREMENT, 
  `NomeModello` varchar(45) NOT NULL,
  `DatiTecnici` varchar(5000) NOT NULL,
  `CasaCostruttrice` varchar(45) NOT NULL,
  `NumeroPosti` int unsigned NOT NULL,
  PRIMARY KEY (`IdModello`),
  UNIQUE KEY `IdModello_UNIQUE` (`IdModello`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
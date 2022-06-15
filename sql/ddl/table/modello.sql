CREATE TABLE IF NOT EXISTS `tripdb`.`modello` (
  `NomeModello` varchar(45) NOT NULL,
  `Tipologia` varchar(45) NOT NULL,
  `DatiTecnici` varchar(45) NOT NULL,
  `CasaCostruttrice` varchar(45) NOT NULL,
  `Numero posti` int NOT NULL,
  PRIMARY KEY (`NomeModello`),
  UNIQUE KEY `NomeModello_UNIQUE` (`NomeModello`)
) ENGINE=InnoDB CHARSET=utf8 COLLATE = utf8_general_ci;

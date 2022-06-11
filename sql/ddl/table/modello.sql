CREATE TABLE IF NOT EXISTS `tripdb`.`modello` (
  `NomeModello` varchar(45) NOT NULL,
  `Tipologia` varchar(45) NOT NULL,
  `DatiTecnici` varchar(45) NOT NULL,
  `CasaCostruttrice` varchar(45) NOT NULL,
  `Numero posti` int NOT NULL,
  PRIMARY KEY (`NomeModello`),
  UNIQUE KEY `targa_UNIQUE` (`NomeModello`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

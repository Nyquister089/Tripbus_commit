CREATE TABLE IF NOT EXISTS `tripdb`.`dipendente` (
  `IdDipendente` int unsigned NOT NULL AUTO_INCREMENT,
  `TipologiaDipendente` varchar(45) NOT NULL,
  `TelefonoAziendale` int NOT NULL,
  `NomeDipendente` varchar(45) NOT NULL,
  `CogrnomeDipendente` varchar(45) NOT NULL,
  PRIMARY KEY (`IdDipendente`),
  UNIQUE KEY `IdDipendente_UNIQUE` (`IdDipendente`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

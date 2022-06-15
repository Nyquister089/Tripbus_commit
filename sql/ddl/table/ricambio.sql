CREATE TABLE IF NOT EXISTS `tripdb`.`ricambio` (
  `Codice` varchar(45) NOT NULL,
  `CostoUnitario` int unsigned NOT NULL,
  `QuantitàDiRiordino` int unsigned NOT NULL,
  `Descrizione` varchar(1000) NOT NULL,
  `ScortaMinima` int unsigned NOT NULL,
  `QuantitàMagazzino` int unsigned NOT NULL,
  PRIMARY KEY (`Codice`),
  UNIQUE KEY `Codice_UNIQUE` (`Codice`)
) ENGINE=InnoDB CHARSET=utf8 COLLATE = utf8_general_ci;

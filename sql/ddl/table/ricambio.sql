CREATE TABLE IF NOT EXISTS `tripdb`.`ricambio` (
  `Codice` varchar(45) NOT NULL,
  `CostoUnitario` decimal(8,2) NOT NULL,
  `QuantitàDiRiordino` int unsigned NOT NULL,
  `Descrizione` varchar(5000) NOT NULL,
  `ScortaMinima` int unsigned NOT NULL,
  `QuantitàMagazzino` int unsigned NOT NULL,
  PRIMARY KEY (`Codice`),
  UNIQUE KEY `Codice_UNIQUE` (`Codice`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

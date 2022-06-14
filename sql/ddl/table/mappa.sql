CREATE TABLE IF NOT EXISTS `tripdb`.`mappa` (
  `IdMappa` int NOT NULL AUTO_INCREMENT,
  `Città` varchar(45) NOT NULL,
  `Livello di dettaglio` varchar(45) NOT NULL,
  `Zona` varchar(45) NOT NULL,
  PRIMARY KEY (`IdMappa`),
  UNIQUE KEY `IdMappa_UNIQUE` (`IdMappa`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

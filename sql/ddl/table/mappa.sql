CREATE TABLE IF NOT EXISTS `tripdb`.`mappa` (
  `IdMappa` int NOT NULL AUTO_INCREMENT,
  `Città` varchar(45) NOT NULL,
  `Livello di dettaglio` varchar(45) NOT NULL,
  `Zona` varchar(45) NOT NULL,
  PRIMARY KEY (`IdMappa`),
  UNIQUE KEY `IdMappa_UNIQUE` (`IdMappa`)
) ENGINE=InnoDB CHARSET=utf8 COLLATE = utf8_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`mappa` (
  `IdMappa` int NOT NULL AUTO_INCREMENT,
  `Citta` varchar(45) NOT NULL,
  `LocalitaRappresentata` varchar (45),
  `Dettaglio` varchar(45) NOT NULL,
  `Zona` varchar(45) NOT NULL,
  `ImmagineMappa` blob DEFAULT NULL,
  PRIMARY KEY (`IdMappa`),
  UNIQUE KEY `IdMappa_UNIQUE` (`IdMappa`),
  KEY `Fk_LocalitaRappresentata_idx` (`LocalitaRappresentata`),
  CONSTRAINT `Fk_LocalitaRappresentata`FOREIGN KEY(`LocalitaRappresentata`) REFERENCES `localita` (`NomeLocalita`) on delete set null
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

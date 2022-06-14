CREATE TABLE IF NOT EXISTS `tripdb`.`localita` (
  `Nome localita` varchar(45) NOT NULL,
  `Regione` varchar(45) NOT NULL,
  `Stato` varchar(45) NOT NULL,
  PRIMARY KEY (`Nome localita`,`Regione`)
) ENGINE=InnoDB DEFAULT DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

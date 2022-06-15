CREATE TABLE IF NOT EXISTS `tripdb`.`localita` (
  `NomeLocalita` varchar(45) NOT NULL,
  `Regione` varchar(45) NOT NULL,
  `Stato` varchar(45) NOT NULL,
  PRIMARY KEY (`NomeLocalita`,`Regione`)
) ENGINE=InnoDB CHARSET=utf8 COLLATE = utf8_general_ci;

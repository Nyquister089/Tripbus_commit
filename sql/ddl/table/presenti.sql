CREATE TABLE IF NOT EXISTS `tripdb`.`presenti` (
  `ComfortPresenti` int unsigned NOT NULL,
  `ModelloAssociato` varchar(45) NOT NULL,
  PRIMARY KEY (`ComfortPresenti`,`ModelloAssociato`),
  KEY `FK_Modello_associato_idx` (`ModelloAssociato`),
  CONSTRAINT `FK_Comfort` FOREIGN KEY (`ComfortPresenti`) REFERENCES `comfort` (`IdComfort`)on delete cascade,
  CONSTRAINT `FK_Modello_associato` FOREIGN KEY (`ModelloAssociato`) REFERENCES `modello` (`NomeModello`)on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
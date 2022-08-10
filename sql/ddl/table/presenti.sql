CREATE TABLE IF NOT EXISTS `tripdb`.`presenti` (
  `ComfortPresenti` int unsigned NOT NULL,
  `ModelloAssociato` int unsigned NOT NULL,
  PRIMARY KEY (`ComfortPresenti`,`ModelloAssociato`),
  KEY `FK_Modello_associato_idx` (`ModelloAssociato`),
  CONSTRAINT `FK_Comfort` FOREIGN KEY (`ComfortPresenti`) REFERENCES `comfort` (`IdComfort`),
  CONSTRAINT `FK_Modello_associato` FOREIGN KEY (`ModelloAssociato`) REFERENCES `modello` (`IdModello`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;
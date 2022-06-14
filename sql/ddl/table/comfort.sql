
CREATE TABLE IF NOT EXISTS `tripdb`.`comfort` (
  `IdComfort` int unsigned NOT NULL AUTO_INCREMENT,
  `Nome Comfort` varchar(45) NOT NULL,
  `DescrizioneComfort` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`IdComfort`),
  UNIQUE KEY `IdComfort_UNIQUE` (`IdComfort`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

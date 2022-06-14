CREATE TABLE IF NOT EXISTS `tripdb`.`servizio` (
  `IdServizio` int NOT NULL,
  `NomeServizio` varchar(45) NOT NULL,
  `DescrizioneServizio` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`IdServizio`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

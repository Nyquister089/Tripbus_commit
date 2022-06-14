CREATE TABLE IF NOT EXISTS `tripdb`.`camera` (
  `NumeroCamera` int NOT NULL,
  `IdAlbergo` int unsigned NOT NULL,
  `Tipologia` varchar(45) NOT NULL,
  `Costo` decimal(18,2) NOT NULL,
  PRIMARY KEY (`NumeroCamera`,`IdAlbergo`),
  KEY `FK_IdAlbergo_idx` (`IdAlbergo`),
  CONSTRAINT `FK_idAlbergoCamera` FOREIGN KEY (`IdAlbergo`) REFERENCES `meta` (`IdMeta`)
) ENGINE=InnoDB     CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

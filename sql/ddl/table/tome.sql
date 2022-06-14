CREATE TABLE IF NOT EXISTS `tripdb`.`tome` (
  `Meta` int unsigned NOT NULL,
  `Tour` varchar(45) NOT NULL,
  PRIMARY KEY (`Meta`,`Tour`),
  KEY `Tour_idx` (`Tour`),
  CONSTRAINT `Meta` FOREIGN KEY (`Meta`) REFERENCES `meta` (`IdMeta`),
  CONSTRAINT `Tour` FOREIGN KEY (`Tour`) REFERENCES `tour` (`DenominazioneTour`)
) ENGINE=InnoDB DEFAULT DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

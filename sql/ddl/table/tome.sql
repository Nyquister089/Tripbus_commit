CREATE TABLE IF NOT EXISTS `tripdb`.`tome` (
  `MetaInclusa` int unsigned NOT NULL,
  `TourRelativo` varchar(45) NOT NULL,
  PRIMARY KEY (`MetaInclusa`,`TourRelativo`),
  KEY `TourRelativo_idx` (`TourRelativo`),
  CONSTRAINT `MetaInclusa` FOREIGN KEY (`MetaInclusa`) REFERENCES `meta` (`IdMeta`),
  CONSTRAINT `TourRelativo` FOREIGN KEY (`TourRelativo`) REFERENCES `tour` (`DenominazioneTour`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

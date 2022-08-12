CREATE TABLE IF NOT EXISTS `tripdb`.`tome` (
  `MetaInclusa` int unsigned not null,
  `TourRelativo` varchar(45) not null,
  PRIMARY KEY (`MetaInclusa`,`TourRelativo`),
  KEY `TourRelativo_idx` (`TourRelativo`),
  CONSTRAINT `MetaInclusa` FOREIGN KEY (`MetaInclusa`) REFERENCES `meta` (`IdMeta`)on delete cascade,
  CONSTRAINT `TourRelativo` FOREIGN KEY (`TourRelativo`) REFERENCES `tour` (`DenominazioneTour`) on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

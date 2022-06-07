CREATE TABLE IF NOT EXISTS `tripdb`.`to-me` (
  `Meta` int unsigned NOT NULL,
  `Tour` varchar(45) NOT NULL,
  PRIMARY KEY (`Meta`,`Tour`),
  KEY `Tour_idx` (`Tour`),
  CONSTRAINT `Meta` FOREIGN KEY (`Meta`) REFERENCES `meta` (`IdMeta`),
  CONSTRAINT `Tour` FOREIGN KEY (`Tour`) REFERENCES `tour` (`DenominazioneTour`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

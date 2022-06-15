CREATE TABLE IF NOT EXISTS `tripdb`.`tagliando` (
  `IdTagliando` int unsigned NOT NULL AUTO_INCREMENT,
  `TipologiaTagliando` varchar(45) NOT NULL,
  `Validità superate` varchar(1000) NOT NULL,
  PRIMARY KEY (`IdTagliando`),
  UNIQUE KEY `IdTagliando_UNIQUE` (`IdTagliando`)
) ENGINE=InnoDB CHARSET=utf8 COLLATE = utf8_general_ci;

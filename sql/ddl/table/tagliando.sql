CREATE TABLE IF NOT EXISTS `tripdb`.`tagliando` (
  `IdTagliando` int unsigned NOT NULL AUTO_INCREMENT,
  `TipologiaTagliando` varchar(45) NOT NULL,
  `Validità superate` varchar(1000) NOT NULL,
  PRIMARY KEY (`IdTagliando`),
  UNIQUE KEY `IdTagliando_UNIQUE` (`IdTagliando`)
) ENGINE=InnoDB DEFAULT DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

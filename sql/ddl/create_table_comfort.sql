CREATE TABLE IF NOT EXISTS `tripdb`.`comfort` (
  `IdComfort` int unsigned NOT NULL AUTO_INCREMENT,
  `Nome Comfort` varchar(45) NOT NULL,
  `DescrizioneComfort` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`IdComfort`),
  UNIQUE KEY `IdComfort_UNIQUE` (`IdComfort`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

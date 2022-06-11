CREATE TABLE IF NOT EXISTS `tripdb`.`tour` (
  `DenominazioneTour` varchar(50) NOT NULL,
  `DescrizioneTour` varchar(5000) NOT NULL,
  `Minimopartecipanti` int unsigned NOT NULL,
  `CostoAssicurazioneMedica` decimal(18,2) unsigned DEFAULT NULL,
  `CostoBagaglio` decimal(18,2) unsigned DEFAULT NULL,
  `CostoGaranziaAnnullamento` decimal(18,2) unsigned DEFAULT NULL,
  `Accompagnatrice` tinyint DEFAULT NULL,
  PRIMARY KEY (`DenominazioneTour`),
  UNIQUE KEY `DenominazioneTour_UNIQUE` (`DenominazioneTour`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Programma di viaggio consultabile da clienti ed impiegati dell’azienda.';

CREATE TABLE  IF NOT EXISTS `tripdb`.`postoprenotato` (
  `NumeroDiPosto` int unsigned NOT NULL,
  `ViaggioAssociato` int NOT NULL,
  `PrenotazioneAssociata` int unsigned NOT NULL,
  `EtàPasseggero` int NOT NULL,
  `NomePasseggero` varchar(45) NOT NULL,
  PRIMARY KEY (`NumeroDiPosto`,`ViaggioAssociato`),
  UNIQUE KEY `NumeroDiPosto_UNIQUE` (`NumeroDiPosto`),
  KEY `viaggioAssociato_idx` (`ViaggioAssociato`),
  KEY `prenotazioneAssociata_idx` (`PrenotazioneAssociata`),
  CONSTRAINT `prenotazioneAssociata` FOREIGN KEY (`PrenotazioneAssociata`) REFERENCES `prenotazione` (`NumeroDiPrenotazione`),
  CONSTRAINT `viaggioAssociato` FOREIGN KEY (`ViaggioAssociato`) REFERENCES `viaggi` (`idviaggio`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
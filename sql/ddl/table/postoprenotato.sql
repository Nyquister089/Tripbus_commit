CREATE TABLE IF NOT EXISTS `tripdb`.`postoprenotato` (
  `NumeroDiPosto` int unsigned NOT NULL,
  `ViaggioAssociato` int NOT NULL,
  `PrenotazioneAssociata` int unsigned NOT NULL,
  `EtaPasseggero` int unsigned NOT NULL,
  `NomePasseggero` varchar(45) NOT NULL,
  `CognomePasseggero` varchar(45) NOT NULL,
  PRIMARY KEY (`NumeroDiPosto`,`ViaggioAssociato`),
  KEY `viaggioAssociato_idx` (`ViaggioAssociato`),
  KEY `prenotazioneAssociata_idx` (`PrenotazioneAssociata`),
  CONSTRAINT `prenotazioneAssociata` FOREIGN KEY (`PrenotazioneAssociata`) REFERENCES `prenotazione` (`NumeroDiPrenotazione`)on delete cascade,
  CONSTRAINT `viaggioAssociato` FOREIGN KEY (`ViaggioAssociato`) REFERENCES `viaggio` (`idviaggio`) on delete cascade
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

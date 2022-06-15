
CREATE TABLE IF NOT EXISTS `tripdb`.`associata` (
  `CameraPrenotata` int unsigned NOT NULL,
  `Ospite` int unsigned NOT NULL,
  `AlbergoInQuestione` int unsigned NOT NULL,
  PRIMARY KEY (`CameraPrenotata`,`Ospite`,`AlbergoInQuestione`),
  KEY `AlbergoInQuestione_idx` (`AlbergoInQuestione`),
  KEY `Ospite_idx` (`Ospite`),
  CONSTRAINT `FK_AlbergoInQuestione` FOREIGN KEY (`AlbergoInQuestione`) REFERENCES `meta` (`IdMeta`),
  CONSTRAINT `FK_Camera` FOREIGN KEY (`CameraPrenotata`) REFERENCES `camera` (`IdAlbergo`),
  CONSTRAINT `FK_Ospite` FOREIGN KEY (`Ospite`) REFERENCES `postoprenotato` (`NumeroDiPosto`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`camera` (
  `NumeroCamera` int NOT NULL,
  `IdAlbergo` int unsigned NOT NULL,
  `Tipologia` varchar(45) NOT NULL,
  `Costo` decimal(18,2) NOT NULL,
  PRIMARY KEY (`NumeroCamera`,`IdAlbergo`),
  KEY `FK_IdAlbergo_idx` (`IdAlbergo`),
  CONSTRAINT `FK_idAlbergoCamera` FOREIGN KEY (`IdAlbergo`) REFERENCES `meta` (`IdMeta`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`cliente` (
  `E-mailCliente` varchar(45) NOT NULL,
  `NomeCliente` varchar(45) NOT NULL,
  `CognomeCliente` varchar(45) NOT NULL,
  `IndirizzoCliente` varchar(45) NOT NULL,
  `CodiceFiscale` varchar(45) NOT NULL,
  `DataDocumentazione` datetime NOT NULL,
  `RecapitoTelefonico` int NOT NULL,
  `Fax` int NOT NULL,
  `IdUtente` int unsigned NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`E-mailCliente`),
  UNIQUE KEY `E-mailCliente_UNIQUE` (`E-mailCliente`),
  UNIQUE KEY `id utente_UNIQUE` (`IdUtente`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`comfort` (
  `IdComfort` int unsigned NOT NULL AUTO_INCREMENT,
  `Nome Comfort` varchar(45) NOT NULL,
  `DescrizioneComfort` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`IdComfort`),
  UNIQUE KEY `IdComfort_UNIQUE` (`IdComfort`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`dipendente` (
  `IdDipendente` int unsigned NOT NULL AUTO_INCREMENT,
  `TipologiaDipendente` varchar(45) NOT NULL,
  `TelefonoAziendale` int NOT NULL,
  `NomeDipendente` varchar(45) NOT NULL,
  `CogrnomeDipendente` varchar(45) NOT NULL,
  PRIMARY KEY (`IdDipendente`),
  UNIQUE KEY `IdDipendente_UNIQUE` (`IdDipendente`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`documentazionefotografica` (
  `idDocumentazioneFotografica` int unsigned NOT NULL AUTO_INCREMENT,
  `Immagine` blob NOT NULL,
  `DocumentazioneFotograficacol` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idDocumentazioneFotografica`),
  UNIQUE KEY `idDocumentazioneFotografica_UNIQUE` (`idDocumentazioneFotografica`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`f-me` (
  `MetaRappresentata` int unsigned NOT NULL,
  `FotoMeta` int unsigned NOT NULL,
  PRIMARY KEY (`MetaRappresentata`,`FotoMeta`),
  KEY `FK_documentazioneFotografica_idx` (`FotoMeta`),
  CONSTRAINT `FK_documentazioneFotografica` FOREIGN KEY (`FotoMeta`) REFERENCES `documentazionefotografica` (`idDocumentazioneFotografica`),
  CONSTRAINT `FK_Meta` FOREIGN KEY (`MetaRappresentata`) REFERENCES `meta` (`IdMeta`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`f-mo` (
  `FotoModello` int unsigned NOT NULL,
  `ModelloRappresentato` varchar(45) NOT NULL,
  PRIMARY KEY (`FotoModello`,`ModelloRappresentato`),
  KEY `FK_Modello_idx` (`ModelloRappresentato`),
  CONSTRAINT `FK_Foto` FOREIGN KEY (`FotoModello`) REFERENCES `documentazionefotografica` (`idDocumentazioneFotografica`),
  CONSTRAINT `FK_Modello` FOREIGN KEY (`ModelloRappresentato`) REFERENCES `modello` (`NomeModello`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`localita` (
  `Nome localita` varchar(45) NOT NULL,
  `Regione` varchar(45) NOT NULL,
  `Stato` varchar(45) NOT NULL,
  PRIMARY KEY (`Nome localita`,`Regione`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`mappa` (
  `IdMappa` int NOT NULL AUTO_INCREMENT,
  `Città` varchar(45) NOT NULL,
  `Livello di dettaglio` varchar(45) NOT NULL,
  `Zona` varchar(45) NOT NULL,
  PRIMARY KEY (`IdMappa`),
  UNIQUE KEY `IdMappa_UNIQUE` (`IdMappa`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`meta` (
  `IdMeta` int unsigned NOT NULL AUTO_INCREMENT,
  `NomeMeta` varchar(45) NOT NULL,
  `TelefonoMeta` int NOT NULL,
  `E-mailMeta` varchar(45) NOT NULL,
  `FaxMeta` varchar(45) NOT NULL,
  `Indirizzo` varchar(45) NOT NULL,
  `TipologiaMeta` varchar(45) NOT NULL,
  `CategoriaAlbergo` varchar(45) DEFAULT NULL,
  `OrarioDiApertura` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`IdMeta`),
  UNIQUE KEY `IdMeta_UNIQUE` (`IdMeta`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`mezzo` (
  `Targa` varchar(10) NOT NULL,
  `ModelloMezzo` varchar(45) NOT NULL,
  `DataRevisioneMotorizzazione` varchar(45) NOT NULL,
  `Autonomia` int unsigned NOT NULL,
  `ValoreContaKm` int unsigned NOT NULL,
  `Ingombri` varchar(45) NOT NULL,
  `DataImmatricolazione` date NOT NULL,
  `Mezzocol` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`Targa`),
  UNIQUE KEY `Targa_UNIQUE` (`Targa`),
  KEY `ModelloMezzo_idx` (`ModelloMezzo`),
  CONSTRAINT `ModelloMezzo` FOREIGN KEY (`ModelloMezzo`) REFERENCES `modello` (`NomeModello`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`modello` (
  `NomeModello` varchar(45) NOT NULL,
  `Tipologia` varchar(45) NOT NULL,
  `DatiTecnici` varchar(45) NOT NULL,
  `CasaCostruttrice` varchar(45) NOT NULL,
  `Numero posti` int NOT NULL,
  PRIMARY KEY (`NomeModello`),
  UNIQUE KEY `targa_UNIQUE` (`NomeModello`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`offre` (
  `idOfferta` int NOT NULL,
  `IdServizio` int NOT NULL,
  `IdAlbergo` int unsigned NOT NULL,
  PRIMARY KEY (`idOfferta`),
  KEY `FK_IdServizio_idx` (`IdServizio`),
  KEY `FK_IdAlbergo_idx` (`IdAlbergo`),
  CONSTRAINT `FK_IdAlbergo` FOREIGN KEY (`IdAlbergo`) REFERENCES `meta` (`IdMeta`),
  CONSTRAINT `FK_IdServizio` FOREIGN KEY (`IdServizio`) REFERENCES `servizio` (`IdServizio`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`postoprenotato` (
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
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`prenotazione` (
  `NumeroDiPrenotazione` int unsigned NOT NULL AUTO_INCREMENT,
  `ClientePrenotante` int unsigned NOT NULL,
  `DataDiPrenotazione` datetime NOT NULL,
  `DataDiConferma` datetime DEFAULT NULL,
  `DataSaldo` datetime DEFAULT NULL,
  PRIMARY KEY (`NumeroDiPrenotazione`),
  UNIQUE KEY `NumeroDiPrenotazione_UNIQUE` (`NumeroDiPrenotazione`),
  UNIQUE KEY `ClientePrenotante_UNIQUE` (`ClientePrenotante`),
  CONSTRAINT `ClientePrenotatne` FOREIGN KEY (`ClientePrenotante`) REFERENCES `cliente` (`IdUtente`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`presenti` (
  `ComfortPresenti` int unsigned NOT NULL,
  `ModelloAssociato` varchar(45) NOT NULL,
  PRIMARY KEY (`ComfortPresenti`,`ModelloAssociato`),
  KEY `FK_Modello_associato_idx` (`ModelloAssociato`),
  CONSTRAINT `FK_Comfort` FOREIGN KEY (`ComfortPresenti`) REFERENCES `comfort` (`IdComfort`),
  CONSTRAINT `FK_Modello_associato` FOREIGN KEY (`ModelloAssociato`) REFERENCES `modello` (`NomeModello`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`revisione` (
  `IdRevisione` int unsigned NOT NULL AUTO_INCREMENT,
  `MezzoRevisionato` varchar(10) NOT NULL,
  `DataInizio` datetime NOT NULL,
  `DataFine` datetime NOT NULL,
  `Chilometraggio` int unsigned NOT NULL,
  `ControlliEffettuati` varchar(1000) NOT NULL,
  `TipologiaRevisione` varchar(45) NOT NULL,
  `Motivazione` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`IdRevisione`),
  UNIQUE KEY `IdRevisione_UNIQUE` (`IdRevisione`),
  KEY `FK_revisione_mezzo_idx` (`MezzoRevisionato`),
  CONSTRAINT `FK_revisione_mezzo` FOREIGN KEY (`MezzoRevisionato`) REFERENCES `mezzo` (`Targa`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`ricambio` (
  `Codice` varchar(45) NOT NULL,
  `CostoUnitario` int unsigned NOT NULL,
  `QuantitàDiRiordino` int unsigned NOT NULL,
  `Descrizione` varchar(1000) NOT NULL,
  `ScortaMinima` int unsigned NOT NULL,
  `QuantitàMagazzino` int unsigned NOT NULL,
  PRIMARY KEY (`Codice`),
  UNIQUE KEY `Codice_UNIQUE` (`Codice`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`r-t` (
  `RevisioneRelativa` int unsigned NOT NULL,
  `TagliandoAssociato` int unsigned NOT NULL,
  PRIMARY KEY (`RevisioneRelativa`,`TagliandoAssociato`),
  KEY `FK_tagliando_idx` (`TagliandoAssociato`),
  CONSTRAINT `FK_revisione` FOREIGN KEY (`RevisioneRelativa`) REFERENCES `revisione` (`IdRevisione`),
  CONSTRAINT `FK_tagliando` FOREIGN KEY (`TagliandoAssociato`) REFERENCES `tagliando` (`IdTagliando`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`servizio` (
  `IdServizio` int NOT NULL,
  `NomeServizio` varchar(45) NOT NULL,
  `DescrizioneServizio` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`IdServizio`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



CREATE TABLE IF NOT EXISTS `tripdb`.`tagliando` (
  `IdTagliando` int unsigned NOT NULL AUTO_INCREMENT,
  `TipologiaTagliando` varchar(45) NOT NULL,
  `Validità superate` varchar(1000) NOT NULL,
  PRIMARY KEY (`IdTagliando`),
  UNIQUE KEY `IdTagliando_UNIQUE` (`IdTagliando`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`to-me` (
  `Meta` int unsigned NOT NULL,
  `Tour` varchar(45) NOT NULL,
  PRIMARY KEY (`Meta`,`Tour`),
  KEY `Tour_idx` (`Tour`),
  CONSTRAINT `Meta` FOREIGN KEY (`Meta`) REFERENCES `meta` (`IdMeta`),
  CONSTRAINT `Tour` FOREIGN KEY (`Tour`) REFERENCES `tour` (`DenominazioneTour`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;



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
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci COMMENT='Programma di viaggio consultabile da clienti ed impiegati dell’azienda.';



CREATE TABLE IF NOT EXISTS `tripdb`.`viaggi` (
  `idviaggio` int NOT NULL AUTO_INCREMENT,
  `TourAssociato` varchar(50) NOT NULL,
  `IdConducente` int unsigned NOT NULL,
  `IdAccompagnatrice` int unsigned DEFAULT NULL,
  `TargaMezzoImpiegato` varchar(10) NOT NULL,
  `DataPartenzaViaggio` datetime DEFAULT NULL,
  `CostoDelViaggio` decimal(18,2) NOT NULL,
  `NumeroKm` int NOT NULL,
  `PostiDisponibili` int NOT NULL,
  `Cancellato` tinyint NOT NULL DEFAULT '0',
  `DataCancellazione` datetime DEFAULT NULL,
  PRIMARY KEY (`idviaggio`),
  UNIQUE KEY `idviaggio_UNIQUE` (`idviaggio`),
  KEY `FK_TourAssocciato_idx` (`TourAssociato`),
  KEY `FK_IdConducente_idx` (`IdConducente`),
  KEY `FK_Mezzoimpiegato_idx` (`TargaMezzoImpiegato`),
  CONSTRAINT `FK_IdAccompagnatrice` FOREIGN KEY (`IdConducente`) REFERENCES `dipendente` (`IdDipendente`),
  CONSTRAINT `FK_IdConducente` FOREIGN KEY (`IdConducente`) REFERENCES `dipendente` (`IdDipendente`),
  CONSTRAINT `FK_Mezzoimpiegato` FOREIGN KEY (`TargaMezzoImpiegato`) REFERENCES `mezzo` (`Targa`),
  CONSTRAINT `FK_TourAssocciato` FOREIGN KEY (`TourAssociato`) REFERENCES `tour` (`DenominazioneTour`)
) ENGINE=InnoDB  CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `tripdb`.`visita` (
  `idvisita` int NOT NULL AUTO_INCREMENT,
  `ViaggioRelativo` int NOT NULL,
  `MetaVisitata` int unsigned NOT NULL,
  `DataArrivo` date NOT NULL,
  `OraArrivo` time NOT NULL,
  `DataPartenza` date NOT NULL,
  `OraPartenza` time NOT NULL,
  `Guida` tinyint DEFAULT NULL,
  `Supplemento` decimal(18,2) DEFAULT NULL,
  `Trattamento` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idvisita`),
  KEY `FK_ViaggioRelativo_idx` (`ViaggioRelativo`),
  KEY `FK_MetaVisitata_idx` (`MetaVisitata`),
  CONSTRAINT `FK_MetaVisitata` FOREIGN KEY (`MetaVisitata`) REFERENCES `meta` (`IdMeta`),
  CONSTRAINT `FK_ViaggioRelativo` FOREIGN KEY (`ViaggioRelativo`) REFERENCES `viaggi` (`idviaggio`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci COMMENT='    ';

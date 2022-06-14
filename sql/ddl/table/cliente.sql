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
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

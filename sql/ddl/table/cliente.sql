CREATE TABLE IF NOT EXISTS `tripdb`.`cliente` (
  `EmailCliente` varchar(45) NOT NULL,
  `NomeCliente` varchar(45) NOT NULL,
  `CognomeCliente` varchar(45) NOT NULL,
  `IndirizzoCliente` varchar(45) NOT NULL,
  `CodiceFiscale` varchar(45) NOT NULL,
  `DataDocumentazione` datetime NOT NULL,
  `RecapitoTelefonico` int NOT NULL,
  `Fax` int NOT NULL,
  PRIMARY KEY (`EmailCliente`),
  UNIQUE KEY `E-mailCliente_UNIQUE` (`EmailCliente`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE= utf8mb4_general_ci;

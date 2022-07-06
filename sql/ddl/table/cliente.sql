CREATE TABLE IF NOT EXISTS `tripdb`.`cliente` (
  `EmailCliente` varchar(45) NOT NULL,
  `NomeCliente` varchar(45) NOT NULL,
  `CognomeCliente` varchar(45) NOT NULL,
  `IndirizzoCliente` varchar(45) NOT NULL,
  `CodiceFiscale` varchar(45) NOT NULL,
  `DataDocumentazione` date NOT NULL,
  `RecapitoTelefonico` varchar(15) NOT NULL,
  `Fax` varchar(15) NOT NULL,
  PRIMARY KEY (`EmailCliente`),
  UNIQUE KEY `E-mailCliente_UNIQUE` (`EmailCliente`)
) ENGINE=InnoDB CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

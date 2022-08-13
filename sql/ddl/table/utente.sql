CREATE TABLE IF NOT EXISTS `tripdb`.`utente` (
  `IdUtente` int unsigned NOT NULL AUTO_INCREMENT,
  `EmailUtente` varchar(45),
  `Pswrd` varchar(8) NOT NULL,
  `TipoUtente` int unsigned NOT NULL,
  PRIMARY KEY (`IdUtente`),
  KEY `fk_utenti_dipendente_idx` (`EmailUtente`)
) ENGINE=InnoDB AUTO_INCREMENT=16 CHARSET=utf8mb4 COLLATE = utf8mb4_general_ci;

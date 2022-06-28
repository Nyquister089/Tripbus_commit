DELETE FROM `tripdb`.`mappa`;
INSERT INTO `tripdb`.`mappa` 
(
  `Citta`,
  `LocalitaRappresentata`,
  `Dettaglio`,
  `Zona`)
   VALUES ('Roma','Roma', 'Medio', 'Roma Sud');
INSERT INTO `tripdb`.`mappa` (
  `Citta`,
  `LocalitaRappresentata`,
  `Dettaglio`,
  `Zona`) 
  VALUES ('Milano', 'Milano', 'Basso', 'Navigli');
INSERT INTO `tripdb`.`mappa` (
  `Citta`,
  `LocalitaRappresentata`,
  `Dettaglio`,
  `Zona`) 
  VALUES ('Graz', 'Graz', 'Alto', 'Graz');

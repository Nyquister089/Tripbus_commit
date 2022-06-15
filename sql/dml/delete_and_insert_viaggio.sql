DELETE FROM `tripdb`.`viaggio`;
INSERT INTO `tripdb`.`viaggio` 
(`TourAssociato`,
  `IdConducente`,
  `IdAccompagnatrice`,
  `TargaMezzoImpiegato`,
  `DataPartenzaViaggio`,
  `CostoDelViaggio`,
  `NumeroKm`,
  `PostiDisponibili`,
  `Cancellato`)
VALUES
('1',
  '1',
  '2',
  'DS1029RM',
  '2022-07-09',
  '300',
  '750',
  '58',
  'false');
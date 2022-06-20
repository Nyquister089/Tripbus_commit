DELETE FROM `tripdb`.`viaggio`;
INSERT INTO `tripdb`.`viaggio` 
(`TourAssociato`,
  `IdConducente`,
  `IdAccompagnatrice`,
  `TargaMezzoImpiegato`,
  `DataPartenzaViaggio`,
  `DataRitornoViaggio`, 
  `CostoDelViaggio`,
  `NumeroKm`,
  `PostiDisponibili`)
VALUES
('1',
  '1',
  '2',
  'DS1029RM',
  '2022-07-09',
  '2022-07-12',
  '300',
  '750',
  '58'
  );
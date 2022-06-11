CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_trip`(
IN trip INT,
OUT tou VARCHAR(45),
OUT idc INT,
OUT ida INT, 
OUT trg VARCHAR(45), 
OUT dpv DATE, 
OUT drv DATE,
OUT cdv DECIMAL(8,2), 
OUT nkm INT, 
OUT npd INT, 
OUT dcn DATE
  )
BEGIN
SELECT *
FROM viaggio as v
WHERE v.IdViaggio = trip; 

SET tou = v.TourAssociato,
	idc = v.IdConducente,
    ida = v.IdAccompagnatrice, 
	trg = v.TargaMezzoImpiegato, 
	dpv = v.DataPartenzaViaggio,
    drv = v.DataDiRitornoViaggio, 
	cdv = v.CostoDelViaggio,
	nkm = v.NumeroKm, 
	npd = v.PostiDisponibili, 
	dcn = v.DataCancellazione;
END
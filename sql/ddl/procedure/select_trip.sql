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


SELECT 
	TourAssociato,
	IdConducente,
    IdAccompagnatrice, 
	TargaMezzoImpiegato, 
	DataPartenzaViaggio,
    DataRitornoViaggio, 
	CostoDelViaggio,
	NumeroKm, 
	PostiDisponibili, 
	DataCancellazione
into
	tou,
	idc,
	ida, 
	trg, 
	dpv, 
	drv,
	cdv, 
	nkm, 
	npd,
	dcn
FROM viaggio as v
JOIN dipendente as d on v.IdConducente = d.IdDipendente 
JOIN dipendente as d1 on v.IdAccompagnatrice = d1.IdDipendente
JOIN mezzo as m on v.TargaMezzoImpiegato = m.Targa
JOIN tour as t on v.TourAssociato = t.DenominazioneTour
WHERE v.IdViaggio = trip; 

END
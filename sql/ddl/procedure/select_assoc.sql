create PROCEDURE if not exists `tripdb`.`select_assoc`(
in htl int, 
in cmp int, 
in spt int
)
begin
select
a.DataInizioSoggiorno,
a.DataFineSoggiorno
from associata as a 
join meta as m on a.AlbergoInQuestione = m.IdMeta
join postoprenotato as p on a.Ospite = p.NumeroDiPosto
join camera as c on a.CameraPrenotata = c.NumeroCamera
where a.AlbergoInQuestione = htl and a.CameraPrenotata = cmp and a.Ospite =spt;  
END
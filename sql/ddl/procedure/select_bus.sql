Create procedure if not exists `tripdb`.`select_bus`(
in trg varchar (10)
 )
BEGIN
select distinct 
  m.ModelloMezzo,
  m.DataRevisioneMotorizzazione,
  m.Autonomia,
  m.ValoreContaKm,
  m.Ingombri,
  m.DataImmatricolazione
from mezzo as m
join modello as mo on m.ModelloMezzo = mo.NomeModello
where m.Targa = trg; 
END
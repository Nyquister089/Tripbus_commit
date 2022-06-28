Create procedure if not exists `tripdb`.`select_bus`(
in trg varchar (45)
 )
BEGIN
select *
from mezzo as m
join modello as mo on m.ModelloMezzo = mo.NomeModello
where m.Targa = trg; 
END
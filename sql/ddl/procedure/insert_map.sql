create procedure if not exists `tripdb`.`insert_map`(
    in ctt varchar(45), 
    in lct varchar(45),
    in dtg varchar(45),
    in zna varchar(45), 
    in mgn blob
)
begin
INSERT INTO mappa  
(
   Citta ,
   LocalitaRappresentata ,
   Dettaglio ,
   Zona,
   ImmagineMappa)
   VALUES (
    ctt,
    lct, 
    dtg,
    zna,
    mgn);
end; 
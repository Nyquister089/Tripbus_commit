create procedure if not exists `tripdb`.`insert_sparepart`(
    in cdc varchar (45),
    in cst int, 
    in qtr int,
    in dsc varchar (5000),
    in scm int, 
    in qtm int
)
begin
insert into ricambio (
   Codice ,
   CostoUnitario ,
   QuantitaDiRiordino ,
   Descrizione ,
   ScortaMinima ,
   QuantitaMagazzino )
  values(
    dsc,
    cst,
    qtr,
    dsc,
    scm,
    qtm); 
  end

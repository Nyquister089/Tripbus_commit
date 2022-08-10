create procedure if not exists `tripdb`.`insert_bus`(
    in trg varchar (45),
    in mdm varchar (45),
    in ngb varchar (45),
    in tnm int,
    in ckm int, 
    in dtr date,
    in dtm date
)

INSERT INTO mezzo(
   Targa  ,
   ModelloMezzo ,
   DataRevisioneMotorizzazione ,
   Autonomia ,
   ValoreContaKm ,
   Ingombri ,
   DataImmatricolazione ) 
VALUES(
    trg,
    mdm,
    dtr,
    tnm,
    ckm,
    ngb,
    dtm)
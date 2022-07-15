create procedure if not exists `tripdb`.`insert_visit`(
    in vgg int, 
    in mtv int, 
    in drr date, 
    in dpr date, 
    in orr time,
    in orp time, 
    in gui tinyint,
    in spl decimal(8,2),
    in trt varchar(45))
begin
INSERT INTO visita (
   ViaggioRelativo ,
   MetaVisitata ,
   DataArrivo ,
   DataPartenza ,
   OraArrivo ,
   OraPartenza ,
   Guida ,
   Supplemento ,
   Trattamento )
VALUES(
    vgg, 
    mtv, 
    drr, 
    dpr, 
    orr, 
    orp, 
    gui,
    spl,
    trt);
  end
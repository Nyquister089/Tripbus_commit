create procedure if not exists `tripdb`.`insert_room`(
    in nmc int, 
    in htl int, 
    in tpl varchar(45),
    in cst decimal(8,2)
)  
begin
INSERT INTO camera(
    NumeroCamera , 
    IdAlbergo ,
    Tipologia ,
    Costo)
VALUES(
    nmc, 
    htl, 
    tpl,
    cst);
  end
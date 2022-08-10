create procedure if not exists `tripdb`.`insert_model`(
    in nmd varchar(45),
    in dtt varchar(5000),
    in csc varchar(45),
    in nmp int
)
begin
INSERT INTO  modello  ( 
    NomeModello ,
    DatiTecnici ,  
    CasaCostruttrice ,  
    NumeroPosti ) 
VALUES (
    nmd, 
    dtt,
    csc,
    nmp
    );
end

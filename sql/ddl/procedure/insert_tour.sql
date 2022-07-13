create procedure if not exists`tripdb`.`insert_tour`(
    in dnt varchar(45), 
    in dst varchar(5000), 
    in mnm int, 
    in mdc decimal(8,2),
    in bgl decimal(8,2),
    in gnl decimal(8,2),
    in hst tinyint
) 
begin
insert into tour(
    DenominazioneTour ,
    DescrizioneTour,
    Minimopartecipanti ,
    CostoAssicurazioneMedica ,
    CostoBagaglio ,
    CostoGaranziaAnnullamento ,
    Accompagnatrice)
values(
    dnt,
    dst,
    mnm,
    mdc,
    bgl,
    gnl,
    hst);
end
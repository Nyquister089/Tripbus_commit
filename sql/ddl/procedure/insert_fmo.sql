create procedure if not exists `tripdb`.`insert_fmo`(
    in fmd int, 
    in mdl int
)
begin

INSERT INTO fmo(
    FotoModello,
    ModelloRappresentato)
VALUES(
    fmd,
    mdl);
end
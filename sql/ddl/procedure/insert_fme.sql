create procedure if not exists `tripdb`.`insert_fme`(
    in mtr int, 
    in ftm int
)
begin

INSERT INTO  fme ( 
    MetaRappresentata, 
    FotoMeta )
VALUES(
    mtr,
    ftm);
end
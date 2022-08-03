create procedure if not exists `tripdb`.`insert_picture` (
    in dsf varchar(5000),
    in pct blob
)
begin
INSERT INTO documentazionefotografica (
    DescrizioneFoto,
    Immagine
    )
VALUES(
    dsf,
    pct
);
end
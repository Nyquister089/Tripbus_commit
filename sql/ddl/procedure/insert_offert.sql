create procedure if not exists `tripdb`.`insert_offert`(
    in srv int,
    in htl int
)
begin
INSERT INTO  offre  ( 
    ServizioOfferto, 
    AlbergoOfferente )
VALUES(
    srv,
    htl
);
end; 
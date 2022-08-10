create procedure if not exists `tripdb`.`insert_tome`(
    in mnc int, 
    in trr varchar(45)
)
begin
INSERT INTO tome  (  
    TourRelativo,
    MetaInclusa) 
VALUES (
    trr,
    mnc); 
end
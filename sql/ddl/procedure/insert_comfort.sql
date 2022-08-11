create procedure if not exists `tripdb`.`insert_comfort`(
    in nmc varchar (45),
    in dsc varchar (45)
)
begin
INSERT INTO comfort  ( 
    NomeComfort ,  
    DescrizioneComfort ) 
VALUES (
    nmc,
    dsc
);
end

create procedure if not exists `tripdb`.`insert_service`(
    in nms varchar (45),
    in dss varchar(5000)
)
begin
INSERT INTO servizio  (  
NomeServizio ,  
DescrizioneServizio )
 VALUES (
    nms,
    dss );
end

create procedure if not exists `tripdb`.`insert_certify`(
    in tpl varchar (45),
    in vld varchar (5000)
)
begin
INSERT INTO tagliando ( 
    TipologiaTagliando ,  
    ValiditaSuperate )
VALUES(
    tpl,
    vld);
end
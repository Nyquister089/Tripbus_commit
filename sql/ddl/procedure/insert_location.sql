create procedure if not exists `tripdb`.`insert_location`(
    in nml varchar (45), 
    in rgn varchar (45),
    in stt varchar (45)
)
begin
INSERT INTO localita(  
    NomeLocalita , 
    Regione ,
    Stato ) 
 VALUES (
    nml, 
    rgn, 
    stt
 );
 end;

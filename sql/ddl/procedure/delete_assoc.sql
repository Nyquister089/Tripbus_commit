create procedure if not exists `tripdb`.`delete_assoc`(
    in htl int,
    in cmp int,
    in spt int
    
)
begin
delete 
from associata
where CameraPrenotata = cmp and Ospite = spt and AlbergoInQuestione = htl; 
end
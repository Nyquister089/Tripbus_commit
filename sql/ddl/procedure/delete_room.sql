create procedure if not exists `tripdb`.`delete_room`(
    in nmc int,
    in htl int
)
begin
delete 
from camera
where NumeroCamera = nmc and IdAlbergo = htl; 
end
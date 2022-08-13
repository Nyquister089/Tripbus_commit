create procedure if not exists `tripdb`.`delete_comfort`(
    in idc int
)
begin
delete 
from comfort
where  IdComfort = idc; 
end
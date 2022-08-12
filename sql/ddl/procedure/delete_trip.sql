create procedure if not exists `tripdb`.`delete_trip`(
    in idv int
)
begin
delete 
from viaggio
where idviaggio =idv; 
end

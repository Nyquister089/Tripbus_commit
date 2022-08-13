create procedure if not exists `tripdb`.`delete_tome`(
    in trr varchar(45),
    in mtn int
)
begin
delete 
from tome
where TourRelativo = trr and MetaInclusa = mtn;  
end
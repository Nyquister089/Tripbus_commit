create procedure if not exists `tripdb`.`delete_skills`(
    in mcc int, 
    in cmp varchar (45)
)
begin
delete 
from competenze
where MeccanicoCompetente = mcc and CompetenzeModello = cmp; 
end
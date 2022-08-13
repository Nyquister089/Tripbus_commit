create procedure if not exists `tripdb`.`delete_fme`(
    in ftm int, 
    in mtr int
)
begin
delete 
from fme
where FotoMeta= ftm and MetaRappresentata =mtr;  
end
create procedure if not exists `tripdb`.`select_comfort`(
in idc int
)
begin
select
c.NomeComfort,
c.DescrizioneComfort
from comfort as c
where c.IdComfort = idc; 
end
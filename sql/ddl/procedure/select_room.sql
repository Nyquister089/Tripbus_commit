create procedure if not exists `tripdb`.`select_room`(
in nmc int, 
in htl int
)
begin
select
c.Tipologia, 
c.Costo
from camera as c
where c.NumeroCamera = nmc and c.IdAlbergo = htl;
end

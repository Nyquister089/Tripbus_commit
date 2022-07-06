create procedure if not exists `tripdb`.`select_certify`(
    in idt int
)
begin
select 
t.TipologiaTagliando,
t.ValiditaSuperate
from tagliando as t
where t.IdTagliando = idt; 
end
create procedure if not exists `tripdb`.`select_tome`(
    in trr varchar (45),
    in mtn int
)
begin
select 
t1.DescrizioneTour,
m.NomeMeta
from tome as t
join tour as t1 on t.TourRelativo = t1.DenominazioneTour
join meta as m on t.MetaInclusa = m.IdMeta
where t.TourRelativo = trr and t.MetaInclusa = mtn; 
end
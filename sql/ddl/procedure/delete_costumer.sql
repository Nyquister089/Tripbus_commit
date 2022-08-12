create procedure if not exists `tripdb`.`delete_costumer`(
    in mlc varchar(45)
)
begin
delete 
from cliente
where EmailCliente= mlc;  
end
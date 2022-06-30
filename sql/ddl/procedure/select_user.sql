create procedure if not exists `tripdb`.`select_user`(
    in idu int
)
begin
select 
u.EmailUtente,
u.Pswrd, 
u.TipoUtente
from  utente as u
Where u.IdUtente = idu; 
end
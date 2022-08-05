create procedure if not exists  `tripdb`.`insert_user`(
    in eml varchar(45),
    in psw varchar(8),
    in tpt varchar(45)
)
begin
INSERT INTO utente 
( EmailUtente ,
   Pswrd ,
   TipoUtente )
 VALUES 
 (eml,
  psw, 
  tpt);
  end; 
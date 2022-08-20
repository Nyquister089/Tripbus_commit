drop user if exists 'Login'@'localhost'; 
drop user if exists 'Autista'@'localhost'; 
drop user if exists 'Cliente'@'localhost'; 
drop user if exists 'Hostess'@'localhost'; 
drop user if exists 'Manager'@'localhost'; 

create user if not exists 'Login'@'localhost' identified by 'lgn'; 
grant usage on tripdb.* to 'Login'@'localhost'; 

create user if not exists 'Autista'@'localhost' identified by 'drvr'; 
grant usage on tripdb.* to 'Autista'@'localhost'; 

create user  if not exists 'Cliente'@'localhost' identified by 'cstmr'; 
grant usage on tripdb.* to 'Cliente'@'localhost'; 

create user  if not exists 'Hostess'@'localhost' identified by 'hstss'; 
grant usage on tripdb.* to 'Hostess'@'localhost'; 

create user  if not exists 'Meccanico'@'localhost' identified by 'mchn'; 
grant usage on tripdb.* to 'Meccanico'@'localhost'; 

create user  if not exists'Manager'@'localhost' identified by 'mngr'; 
grant usage on tripdb.* to 'Manager'@'localhost'; 
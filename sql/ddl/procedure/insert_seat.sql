CREATE DEFINER=`giordano`@`localhost` PROCEDURE `insert_seat`(
in num int, 
in via int, 
in pre int, 
in eta int , 
in nom varchar(45),
in cgn varchar(45)
)
BEGIN
insert into postoprenotato 
			(NumeroDiPosto, 
             ViaggioAssociato, 
             PrenotazioneAssociata, 
             EtaPasseggero, 
             NomePasseggero,
             CognomePasseggero)
values
			(num, 
             via, 
             pre,
             eta, 
             nom,
             cgn
             ); 
END
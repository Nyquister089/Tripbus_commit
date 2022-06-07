CREATE DEFINER=`giordano`@`localhost` PROCEDURE `insert_seat`(
in num int, in via int, in pre int, in eta int , 
in nom varchar(45))
BEGIN
insert into postoprenotato 
			(NumeroDiPosto, 
             ViaggioAssociato, 
             PrenotazioneAssociata, 
             EtaPasseggero, 
             NomePasseggero)
values
			(num, 
             via, 
             pre,
             eta, 
             nom); 
END
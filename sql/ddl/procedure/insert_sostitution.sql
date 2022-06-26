CREATE DEFINER=`giordano`@`localhost` PROCEDURE `insert_seat`(
in rvs int, 
in rcm varchar(45), 
in qnt int
)
BEGIN
insert into postoprenotato 
			( RevisioneAssociata,
             CodiceRicambioSostituito,
             QuantitàSostituita,)
values
			(rvs, 
             rcm,
             qnt
             ); 
END
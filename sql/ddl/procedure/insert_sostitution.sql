CREATE DEFINER=`giordano`@`localhost` PROCEDURE `insert_sostitution`(
in rvs int, 
in rcm varchar(45), 
in qnt int
)
BEGIN
insert into sostituito 
			(RevisioneAssociata,
             CodiceRicambioSostituito,
             QuantitàSostituita)
values
			(rvs, 
             rcm,
             qnt
             ); 
END
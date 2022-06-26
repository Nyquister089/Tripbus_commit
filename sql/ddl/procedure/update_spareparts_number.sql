CREATE DEFINER=`giordano`@`localhost` PROCEDURE ` update_spareparts_number`(
in nmr int
)
BEGIN
insert into revisione (
    QuantitàMagazzino
  )
values(
	nmr
); 
END
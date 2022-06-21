CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_all_tour`(
 )
BEGIN
select distinct DenominazioneTour
from tour; 

/*declare done int default false;
declare cur cursor for select distinct DenominazioneTour from tour;
declare continue handler for not found set done = true;
open cur; 
read_loop: loop
	fetch cur into den;
	if done then
		leave read_loop;
	end if;
end loop;
close cur;*/
end
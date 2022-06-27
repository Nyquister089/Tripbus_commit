CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_max_idreview`(

 )
BEGIN
select max(IdRevisione)
from revisione; 
END
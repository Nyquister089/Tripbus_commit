CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_trip`(IN trip INT)
BEGIN
SELECT *
FROM viaggio as v
WHERE v.IdViaggio = trip;
END
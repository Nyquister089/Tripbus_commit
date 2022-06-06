CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_trip`(IN trip INT)
BEGIN
SELECT v.IdViaggio, v.PostiDisponibili, v.DataCancellazione
FROM viaggio as v
WHERE v.IdViaggio = trip;
END
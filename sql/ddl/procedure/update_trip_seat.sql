CREATE DEFINER=`giordano`@`localhost` PROCEDURE `update_trip_seat`(IN trip INT, IN pos INT)
BEGIN 

UPDATE viaggio as v
SET v.PostiDispobili = pos
WHERE v.IdViaggio = trip; 

END
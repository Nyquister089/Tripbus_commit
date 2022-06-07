CREATE DEFINER=`giordano`@`localhost` PROCEDURE `insert_assoc`(
in cam int, in osp int, in alb int )
BEGIN
insert into associata 
			(CameraPrenotata, 
			 Ospite, 
             AlbergoInQuestione)
values
			(cam,
             osp,
             alb); 
END
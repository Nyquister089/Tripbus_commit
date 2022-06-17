CREATE DEFINER=`giordano`@`localhost` PROCEDURE `insert_assoc`(
in cam int, 
in osp int, 
in alb int, 
in dis date,
in dfs date
 )
BEGIN
insert into associata 
			(CameraPrenotata, 
			 Ospite, 
             AlbergoInQuestione,
             DataInizioSoggiorno, 
             DataFineSoggiorno)
values
			(cam,
             osp,
             alb,
             dis,
             dfs); 
END
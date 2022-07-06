CREATE DEFINER=`giordano`@`localhost` PROCEDURE `select_tour`(
INOUT den VARCHAR(45),
OUT dsc VARCHAR (5000),
OUT mnp INT, 
OUT mdc DECIMAL(8,2), 
OUT bgl DECIMAL(8,2), 
OUT gnl	DECIMAL(8,2), 
OUT acc TINYINT )
BEGIN
SELECT DenominazioneTour ,
    DescrizioneTour,
    Minimopartecipanti,
    CostoAssicurazioneMedica,
    CostoBagaglio,
    CostoGaranziaAnnullamento,
    Accompagnatrice  
INTO den, dsc, mnp, mdc, bgl, gnl, acc
FROM tour as t
WHERE t.DenominazioneTour = den;
END
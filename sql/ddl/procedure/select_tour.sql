create procedure if not exists `tripdb`.`select_tour`(
IN dnm VARCHAR(45)
)
BEGIN
SELECT 
    t.DescrizioneTour,
    t.Minimopartecipanti,
    t.CostoAssicurazioneMedica,
    t.CostoBagaglio,
    t.CostoGaranziaAnnullamento,
    t.Accompagnatrice  
FROM tour as t
WHERE t.DenominazioneTour = dnm;
END
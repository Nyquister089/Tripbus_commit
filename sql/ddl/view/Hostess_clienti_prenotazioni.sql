CREATE 
    ALGORITHM = UNDEFINED 

    SQL SECURITY DEFINER
VIEW `Hostess_cliente_prenotazioni` AS
    SELECT 
        `p`.`NumeroDiPrenotazione` AS `NumeroDiPrenotazione`,
        `c`.`NomeCliente` AS `NomeCliente`,
        `c`.`CognomeCliente` AS `CognomeCliente`,
        `p`.`DataDiConferma` AS `DataDiConferma`,
        `p`.`DataSaldo` AS `DataSaldo`
    FROM
        (`prenotazione` `p`
        JOIN `cliente` `c` ON ((`p`.`ClientePrenotante` = `c`.`EmailCliente`)))
    WHERE
        (`c`.`NomeCliente` = 'nom')
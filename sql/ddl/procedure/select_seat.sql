create procedure if not exists `tripdb`.`select_seat`(
    in nmp int,
    in vsc int
)
begin
select
p.NomePasseggero,
p.CognomePasseggero,
p.EtaPasseggero,
p.PrenotazioneAssociata
from postoprenotato as p
join viaggio as v on p.ViaggioAssociato = v.idviaggio
join prenotazione as r on p.PrenotazioneAssociata = r.NumeroDiPrenotazione
where p.NumeroDiPosto = nmp and p.ViaggioAssociato = vsc; 
end
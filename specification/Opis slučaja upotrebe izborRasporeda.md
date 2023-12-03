### Opis slučaja upotrebe "Izbor rasporeda stolova":
- __Kratak opis__: Konobar bira postojeće rasporede stolova, po potrebi ih menja i potom koristi raspored.
-  __Akter__: Konobar - bira raspored
- __Preduslovi__: Aplikacija je pokrenuta i prikazuje glavni meni. 
- __Postuslovi__: Informacija o izboru rasporeda je sačuvana.
-  __Osnovni tok__:
    1. Konobar bira dugme "Choose the arrangement" iz glavnog menija.
    2. Aplikacija prikazuje meni postojećih rasporeda.
    3. Konobar može da izmeni postojeći raspored.

        3.1. Prelazi se na slučaj upotrebe "Izmeni postojeći raspored stolova".
	4. Sve dok konobar ne sačuva izabrani šablon klikom na dugme "Save":
    
        4.1. Aplikacija čuva infomaciju o trenutno izabranom raspored.
        
        4.2. Aplikaciju prikazuje dati raspored. 
	5. Konobar je finalno sačuvao raspored, prelazi se na slučaj upotrebe "Dodaj porudžbinu" i korak 6..
    6. Aplikacija prikazuje prozor za dodavanje porudžbina.

- __Alternativni tokovi:__
	-A1: __Neočekivan izlazak iz aplikacije__. Ukoliko konobar u bilo kojem koraku isključi aplikaciju, sve informacije vezane za izbor stolova se brišu.
- __Podtokovi:__ /
- __Specijalni zahtevi:__ Neophodno je postojanje već unapred napravljenih rasporeda. 
- __Dodatne infomacije:__ / 
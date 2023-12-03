### Opis slučaja upotrebe:  "Dodavanje porudžbine"


- __Kratak opis__:
                
    Konobar započinje jednu porudžbinu odabirom odgovarajućeg stola iz rasporeda. Aplikacija učitava meni odakle se biraju odgovarajući artikli. Na kraju porudžbine, izdaje se račun i završava se porudžbina.


- __Akteri__:

    Konobar

- __Preduslovi__:

    Aplikacija je pokrenuta, odabran je raspored stolova i prikazuje se. 

- __Postuslovi__:

    Informacija o ukupnoj ceni artikala u porudžbini je sačuvana.


- __Osnovni tok__:

    1. Konobar bira sto za koji se pravi porudžbina.
    2. Aplikacija prikazuje meni (artikle na raspolaganju).
    3. Aplikacija kreira novu porudžbinu.
    4. Sve dok konobar ne odabere opciju "Potvrdi", ponavljaju se naredni koraci:

        4.1. Konobar bira artikl iz menija klikom na ikonicu željenog artikla.

        4.2. Odabrani artikl se dodaje u porudžbinu.

        4.3. Prikazuje se trenutno stanje porudžbine.

    5. Sve dok konobar ne zatraži račun, ponavljaju se naredni koraci:
    
        5.1. Aplikacija prikazuje opciju "Izmeni".
    
        5.2. Ako je konobar odabrao opciju "Izmeni":

        &emsp;5.2.1. Prelazi se na slučaj upotrebe "Izmena porudžbine". 


    6. Nakon što je konobar zatražio račun, prelazi se na slučaj upotrebe "Izdavanje računa". Po završetku, prelazi se na korak 7.
    7. Aplikacija prikazuje račun kkonobaru.
    8. Aplikacija prikazuje glavni meni.



- __Alternativni tokovi__:/



- __Podtokovi__:/


- __Specijalni zahtevi__:/

- __Dodatne informacije__:/
### Opis slučaja upotrebe:  "Izmena porudžbine"


- __Kratak opis__:
                
    Konobar dodaje/briše artikle iz već kreirane porudžbine. Ovaj slučaj upotrebe je opcioni, porudžbina se može kreirati i završiti bez izmena u međuvremenu.


- __Akteri__:

    Konobar

- __Preduslovi__:

    Aplikacija je pokrenuta, odabran je raspored stolova, odabran je sto i kreirana porudžbina za isti. 

- __Postuslovi__:

    Informacije o izmenama su sačuvane u tekućoj porudžbini.


- __Osnovni tok__:

    1. Konobar bira opciju "Izmeni" u tekućoj porudžbini.
    2. Kreira se nova izmena porudžbine.
    3. Aplikacija prikazuje meni (spisak artikala koje je moguće odabrati).
    4. Sve dok konobar ne potvrdi izmenu, ponavljaju se sledeći koraci:

        4.1. Konobaru se prikazuju artikli koji su trenutno u porudžbini i opcije "Dodaj" i "Ukloni".

        4.2. Ako je konobar odabrao opciju "Dodaj", potrebno je odabrati artikl koji želi da doda.

        &emsp;  4.2.1. Konobar bira artikl.

        &emsp;  4.2.2. Artikl se dodaje.


        4.3. Ako je konobar odabrao opciju "Ukloni", potrebno je odabrati artikl koji želi da ukloni.

        &emsp;  4.3.1. Konobar bira artikl.

        &emsp;  4.3.2. Artikl se uklanja.

    5. Nakon sto je konobar potvrdio izmenu, čuvaju se promene u tekućoj porudžbini.
    6. Aplikacija prikazuje poruku o sačuvanim izmenama.



- __Alternativni tokovi__:/



- __Podtokovi__:/


- __Specijalni zahtevi__:/

- __Dodatne informacije__:/
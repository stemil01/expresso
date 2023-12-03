### Opis slučaja upotrebe "Podešavanje menija":
- **Kratak opis:** Korisnik iz glavnog menija aplikacije bira podešavanje menija.
Aplikacija daje izmenu postojećeg menija i nudi mogućnost dodavanja novog menija.
Nakon podešavanja, meni se trajno čuva.

- **Akteri:** Konobar - menja meni

- **Preduslovi:** Aplikacija je pokrenuta i prikazuje glavni meni.

- **Postuslovi:** Sadržan menija je trajno sačuvan.

- **Osnovni tok:**
    1. Konobar bira dugme "Podešavanje menija" iz glavnog menija.
    2. Aplikacija prikazuje izbor za dodavanje u postojeći meni ili pravjljenje novog.

        2.1. Ako konobar odabere da doda u postojeći meni:

            2.1.1. Aplikacija nudi listu postojećih menija.
            2.1.2. Konobar bira jedan od ponudjenih menija.
            2.1.3. Aplikacija lista artikle iz izabranog menija.

                2.1.3.1 Ako konobar izabere neki od artikala:

                    2.1.3.1.1. Aplikacija nudi opciju za izmenu informacija o artiklu ili njegovo brisanje.
                    2.1.3.1.1. Korisnik izvršava željenu radnju.
                    2.1.3.1.1. Aplikacija trajno čuva novo stanje menija i vraća se na korak 2.1.3.
                2.1.3.2. Ako konobar izabere "Dodaj artikl":
                    2.1.3.2.1. Aplikacija nudi formu za dodavanje novog artikla.
                    2.1.3.2.2. Korisnik unosi informacije.
                    2.1.3.2.3. Aplikacija čuva trajno podatke i vraća se na korak 2.1.3.

        2.2. Ako konobar odabere da napravi novi meni:
            2.2.1. Prelazi se na slučaj upotrebe "Dodavanej novog menija".
            Po završetku se aplikacija vraća na korak 2.

        2.3. Ako konobar odabere dugme "Nazad" ide se ne glavni meni.

- **Alternativni tokovi:** Ukoliko u nekom od koraka korisnik izabere da izadje iz aplikacije, aplikacije se zatvara i unete promene se ne čuvaju.

- **Podtokovi:** /

- **Specijalni zahtevi:** /

- **Dodatne informacije:** /

### Opis slučaja upotrebe "Izdavanje računa": 
- **Kratak opis:** Konobar koristi aplikaciju kako bi odabrao sto i izdao račun za njega, uz mogućnost izbora između plaćanja gotovinom ili karticom. U slučaju plaćanja gotovinom, automatski se generiše iznos kusura. Na kraju plaćanja, transakcija se čuva radi generisanja dnevnih/mesečnih izveštaja.
- **Akter:** Konobar.
- **Preduslov:** Aplikacija je uspešno pokrenuta prikazujući meni sa stolovima i njihovim narudžbinama.
- **Postuslov:** Račun je uspesno plaćen i informacije o plaćanju su uspešno sačuvane u izveštajima.
- **Osnovni tok:**
    1. Konobar klikom odabira sto za koji želi da naplati račun.
    2. Prikazuju se sadržaj tog stola.
    3. Konobar odabira opciju da se naplati račun za taj sto.
    4. Aplikacija prikazuje račun i nudi izbor za plaćanje gotovinom ili karticom:
        4.1 Konobar bira plaćanje gotovinom:
            4.1.1 Konobar unosi iznos koji je dobio od gosta.
                4.1.1.1 Aplikacija provera unos konobara.
                    4.1.1.1.1 Ako je uneti iznos manji od računa, aplikacija obaveštava konobara o grešci.
                        4.1.1.1.1.1 Aplikacija vraća konobara na korak 4.1.1 da bi ispravio dobijeni iznos.
                    4.1.1.1.2 Uneti iznos je ispravan.
                        4.1.1.1.2.1 Generiše se iznos kusura.
                            4.1.1.1.2.1.2 Konobar potvrđuje plaćanje.
        4.2 Konobar bira plaćanje karticom:
            4.2.1 Konobar potvrđuje
    5. Aplikacija sto se postavlja na početno stanje, bez nardudžbina i troškova.
    6. Izveštaj o plaćanju se čuva zbog dnevnih/mesečnih izveštaja.
    7. Potvrda da je plaćanje uspešno.
    
- **Alternativni tokovi:**
      *A1:*  Neočekivana greška u konekciji sa aplikacijom, konobar se opet povezuje na mrežu i proverava da li je plaćanje sačuvano ili nije, ukoliko nije ponavlja postupak.
- **Podtokovi:**  /
- **Specijalni zahtevi:** /
- **Dodatne informacije:** /
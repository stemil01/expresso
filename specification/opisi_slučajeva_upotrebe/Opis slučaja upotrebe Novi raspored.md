### Opis slučaja upotrebe "Novi raspored stolova":
- __Kratak opis:__ Konobar započinje kreiranje novog rasporeda stolova iz glavnog menija. Bira mesto gde želi da pozicionira stolove uz mogućnost            		da aplikacija sačuva urađeno. Nakon završetka konobar može da koristi dati raspored.
- __Akter:__ Konobar - pravi novi raspored
- __Preduslovi:__ Aplikacija je pokrenuta i prikazuje glavni meni.
- __Postuslovi:__ Informacije o rasporedu stolova su sačuvani.
- __Osnovni tok:__
	1. Konobar bira dugme "Design a table arrangement" iz glavnom menija i započinje pravljenje rasporeda.
	2. Aplikacija konstruiše praznu tablu.
	3. Sve dok se prozor ne zatvoru ponavlja se sledeće:

        3.1. Konobar dodaje novi sto.
        
        &emsp;3.1.1. Aplikacija proverava da li ima dovoljno prostora.

	    &emsp;&emsp;3.1.1.1 Ukoliko ima prostora, dodaje se novi sto.

	    &emsp;&emsp;&emsp;3.1.1.1.1. Aplikacija pravi novi sto.

	    &emsp;&emsp;&emsp;3.1.1.1.2. Konobar bira mesto stola.

	    &emsp;&emsp;3.1.1.2. Ukoliko nema prostora obaveštava se konobar.

        &emsp;&emsp;&emsp;3.1.1.2.1. Aplikacija ispisuje datu poruku.

  	    3.2 Sve dok postoje stolovi se ponavlja sledece:

	    &emsp;3.2.1. Konobar može da izmeni sto.

	    &emsp;&emsp;3.2.1.1 Aplikacija menja sto.

        &emsp;3.2.2. Konobar može da obriše sto.

        &emsp;&emsp;3.2.2.1 Aplikacija briše sto.

	    &emsp;3.2.3. Konobar može da obriše sve stolove.

	    &emsp;&emsp;3.2.3.1 Aplikacija briše sve stolove.

        3.3. Ukoliko ne postoje stolovi, konobar dobija poruku.
        
        &emsp;3.3.1 Aplikacija ispisuje datu poruku.

   4. Nakon što konobar finalno sačuva raspored, prelazi se na slučaj upotrebe "Dodaj porudžbinu" i korak 5..
   5. Aplikacija prikazuje prozor za dodavanje porudžbina.

- __Alternativni tokovi:__
	-A1: __Neočekivan izlazak iz aplikacije__. Ukoliko konobar u bilo kojem koraku isključi aplikaciju, sve infomacije koje su urađene do klika na dugme "Save" biće sačuvane, ostale infomacije se brišu.
- __Podtokovi:__ /
- __Specijalni zahtevi:__ /
- __Dodatne infomacije:__ Konobar može u bilo kom trenutku da sačuva sve što je urađeno do tog momenta, klikom na dugme "Save".
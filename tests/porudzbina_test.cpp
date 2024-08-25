#include "../src/artikl.h"
#include "../src/porudzbina.h"
#include <catch.hpp>

TEST_CASE("Porudzbina", "[class]") {

  SECTION("Vrati vektor artikala iz porudzbine") {

    // Arrange
    Porudzbina *p = new Porudzbina();

    Artikl *a1 = new Artikl("Artikl1", 120.50, "Kategorija1");
    Artikl *a2 = new Artikl("Artikl2", 120.50, "Kategorija2");
    p->dodajArtikl(a1);
    p->dodajArtikl(a2);

    // Act
    QVector<Artikl *> artikli = p->getArtikli();

    // Assert
    REQUIRE_FALSE(artikli.empty());

    delete p;
  }

  SECTION("Dodaj artikl") {

    // Arrange
    Porudzbina *p = new Porudzbina();

    Artikl *a1 = new Artikl("Artikl1", 120.50, "Kategorija1");
    Artikl *a2 = new Artikl("Artikl1", 120.50, "Kategorija1");
    int ocekivaniRezultat1 = 0;
    int ocekivaniRezultat2 = 1;
    int ocekivanaDuzina = 1;
    int ocekivanaKolicina = 2;

    // Act
    int rezultat1 = p->dodajArtikl(a1);
    int rezultat2 = p->dodajArtikl(a2);
    QVector<Artikl *> artikli = p->getArtikli();

    int duzina = artikli.size();
    int kolicina = artikli[0]->getKolicina();

    // Assert
    REQUIRE(ocekivaniRezultat1 == rezultat1);
    REQUIRE(ocekivaniRezultat2 == rezultat2);
    REQUIRE(ocekivanaDuzina == duzina);
    REQUIRE(ocekivanaKolicina == kolicina);

    delete p;
  }

  SECTION("Obrisi po nazivu") {

    // Arrange
    Artikl *a1 = new Artikl("cocacola", 250, "sokovi");
    Artikl *a2 = new Artikl("fanta", 200, "sokovi");
    Porudzbina *p = new Porudzbina();
    p->dodajArtikl(a1);
    p->dodajArtikl(a2);
    int ocekivanaDuzina = 1;
    QString ocekivanNaziv = "fanta";

    // Act
    p->obrisiPoNazivu("cocacola");
    QVector<Artikl *> artikli = p->getArtikli();

    int duzina = artikli.size();
    QString naziv = (artikli[0])->getNaziv();

    // Assert
    REQUIRE(ocekivanaDuzina == duzina);
    REQUIRE(ocekivanNaziv == naziv);
  }

  SECTION("Brisanje svih artikala iz porudzbine") {

    // Arrange
    Artikl *a1 = new Artikl("CocaCola", 250, "SOFTDRINKS");
    Artikl *a2 = new Artikl("FANTA", 200, "SOFTDRINKS");
    Porudzbina *p = new Porudzbina();

    p->dodajArtikl(a1);
    p->dodajArtikl(a2);

    // Act

    p->obrisiArtikle();

    // Assert
    REQUIRE(p->getArtikli().empty());

    delete p;
  }

  SECTION("Racun u slucaju da je porudzbina prazna") {

    // Arrange
    Porudzbina *p = new Porudzbina();
    QString ocekivanIzlaz =
        "\nTotal....................................................0\n";

    // Act
    QString opis = p->ispisiCeoRacun();

    // Assert
    REQUIRE(ocekivanIzlaz == opis);

    delete p;
  }

  SECTION("Racun u slucaju da porudzbina nije prazna") {

    // Arrange
    Porudzbina *p = new Porudzbina();

    Artikl *a1 = new Artikl("CocaCola", 250, "SOFTDRINKS");
    Artikl *a2 = new Artikl("FANTA", 200, "SOFTDRINKS");

    p->dodajArtikl(a1);
    p->dodajArtikl(a2);
    p->dodajArtikl(a2);

    QString ocekivanIzlaz = "CocaCola.........................................."
                            "........250x1\nFANTA.............................."
                            "....................200x2\n\nTotal................"
                            "....................................650\n";

    // Act
    QString izlaz = p->ispisiCeoRacun();

    // Assert
    REQUIRE(ocekivanIzlaz == izlaz);

    delete p;
  }
}

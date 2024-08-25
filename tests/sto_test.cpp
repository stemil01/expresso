#include "../src/artikl.h"
#include "../src/porudzbina.h"
#include "../src/sto.h"
#include <catch.hpp>

TEST_CASE("Testing Sto", "[class]") {
  SECTION("Testing id") {

    Sto *sto = new Sto(1);
    qint32 expected = 1;

    qint32 result = sto->getId();

    REQUIRE(result == expected);

    delete sto;
  }
  SECTION("Testing porudzbina in sto") {

    Sto *sto = new Sto(1);
    Artikl *artikl = new Artikl("Fanta", 80.0, "Sokovi", 10);
    Porudzbina *p = new Porudzbina();

    p->dodajArtikl(artikl);
    sto->setPorudzbina(p);

    Porudzbina *result = sto->getPorudzbina();

    REQUIRE(result != nullptr);

    delete sto;
  }
  SECTION("Testing broj mesta") {

    Sto *sto = new Sto(1);
    Artikl *artikl = new Artikl("Fanta", 80.0, "Sokovi", 10);
    Porudzbina *p = new Porudzbina();

    p->dodajArtikl(artikl);
    sto->setPorudzbina(p);

    Porudzbina *result = sto->getPorudzbina();

    REQUIRE(result != nullptr);

    delete sto;
  }
}

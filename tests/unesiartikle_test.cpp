#include "../src/artikl.h"
#include "../src/unesiartikle.h"
#include <catch.hpp>
TEST_CASE("Testing Sto", "[class]") {
  SECTION("Testing unesi artikle") {
    unesiartikle *ua = new unesiartikle();
    Artikl *a = new Artikl("cocacola", 250, "sokovi");
    ua->dodajArtikal(*a);
    REQUIRE_FALSE(ua->getSkladisteArtikala().empty());
  }

  SECTION("Testing citanje iz txt") {
    unesiartikle *ua = new unesiartikle();
    ua->ucitajPodatkeIzTxt();
    REQUIRE(ua->getSkladisteArtikala().size() > 0);
  }
  SECTION("Test azuriranja postojećeg artikla") {
    unesiartikle *ua = new unesiartikle();
    Artikl *a = new Artikl("cocacola", 250, "sokovi");
    ua->dodajArtikal(*a);
    REQUIRE_FALSE(ua->getSkladisteArtikala().empty());
    REQUIRE(ua->getSkladisteArtikala().size() == 1);

    Artikl *postojeci = new Artikl("cocacola", 230, "sokovi");
    ua->dodajArtikal(*postojeci);
    std::vector<Artikl> rezultat = ua->getSkladisteArtikala();
    REQUIRE(ua->getSkladisteArtikala().size() == 1);
    REQUIRE(rezultat[0].getCena() == 230);
  }
}

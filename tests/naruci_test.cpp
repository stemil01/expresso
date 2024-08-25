#include <catch.hpp>

#include "../src/artikl.h"
#include "../src/naruci.h"
#include "../src/porudzbina.h"

#include <vector>

TEST_CASE("Naruci", "[class]") {

  SECTION("Za prosledjeni artikl, dodati njegov naziv, kolicinu i cenu u novi "
          "red prosledjenog qtablewidget-a") {

    // Arrange
    unesiartikle *ua = new unesiartikle();
    Porudzbina *p = new Porudzbina();
    Naruci *naruci = new Naruci(nullptr, p, ua);
    Artikl *artikl = new Artikl("CocaCola", 150, "SOFTDRINKS");

    QTableWidget *tw = new QTableWidget();
    tw->setColumnCount(3);

    int ocekivanBrojRedova = 1;
    QString ocekivanNaziv = "CocaCola";
    QString ocekivanaKolicina = "1";
    QString ocekivanaCena = "150";

    // Act
    naruci->addItemInTW(tw, artikl);
    int brRedova = tw->rowCount() - 1;
    QString naziv = (tw->item(brRedova, 0))->text();
    QString kolicina = (tw->item(brRedova, 1))->text();
    QString cena = (tw->item(brRedova, 2))->text();

    // Assert
    REQUIRE(ocekivanBrojRedova == brRedova + 1);
    REQUIRE(ocekivanNaziv == naziv);
    REQUIRE(ocekivanaKolicina == kolicina);
    REQUIRE(ocekivanaCena == cena);

    delete tw;
    delete naruci;
  }

  SECTION(
      "U prosledjenom qtablewidget-u trazi dati naziv u prvoj koloni i u redu "
      "u kom je pronadjeni item, povecava vrijednost druge kolone za jedan") {

    // Arrange
    unesiartikle *ua = new unesiartikle();
    Porudzbina *p = new Porudzbina();
    Naruci *naruci = new Naruci(nullptr, p, ua);

    QTableWidget *tw = new QTableWidget();
    tw->setColumnCount(3);
    tw->setRowCount(2);
    tw->setItem(1, 0, new QTableWidgetItem("CocaCola"));
    tw->setItem(1, 1, new QTableWidgetItem("3"));
    tw->setItem(1, 2, new QTableWidgetItem("150"));
    tw->setItem(0, 0, new QTableWidgetItem("Coffee"));
    tw->setItem(0, 1, new QTableWidgetItem("5"));
    tw->setItem(0, 2, new QTableWidgetItem("120"));

    QString naziv = "CocaCola";

    QString ocekivanaKolicina = "4";

    // Act
    naruci->updateItemInTW(tw, naziv);
    QString kolicina = (tw->item(1, 1))->text();

    // Assert
    REQUIRE(ocekivanaKolicina == kolicina);

    delete tw;
    delete naruci;
  }
}

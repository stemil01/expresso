#include <catch.hpp>
#include "../src/sto.h"
#include "../src/porudzbina.h"
#include "../src/artikl.h"
#include "../src/glavnimeni.h"
//#include "../src/raspored.h"
#include <QGraphicsScene>

class GlavniMeniTest : public GlavniMeni
{
public:
    using GlavniMeni::dodajNovSto;
    using GlavniMeni::obrisiSto;
    using GlavniMeni::obrisiSve;
    using GlavniMeni::tabla;
    using GlavniMeni::m_currentRaspored;
};

TEST_CASE("Testing sto in glavnimeni","[class]"){
    SECTION("Testing add table"){

        GlavniMeniTest gl;


        qint32 expected = 1;
        auto scene = gl.tabla;
        Raspored* novi = new Raspored("novi");
        gl.m_currentRaspored = novi;
        gl.dodajNovSto();
        qint32 result = (scene->items()).size();

        REQUIRE(expected == result);

        delete novi;

    }
    SECTION("Testing select table"){

        GlavniMeniTest gl;


        bool expected = true;
        auto scene = gl.tabla;
        Raspored* novi = new Raspored("novi");
        gl.m_currentRaspored = novi;
        gl.dodajNovSto();
        auto sto = (scene->items())[0];
        sto->setSelected(true);
        bool result = sto->isSelected();

        REQUIRE(expected == result);

        delete novi;

    }
    SECTION("Testing remove table"){

        GlavniMeniTest gl;


        qint32 expected = 0;
        auto scene = gl.tabla;
        Raspored* novi = new Raspored("novi");
        gl.m_currentRaspored = novi;
        gl.dodajNovSto();
        auto sto = (scene->items())[0];
        sto->setSelected(true);
        gl.obrisiSto();
        qint32 result = (scene->items()).size();

        REQUIRE(expected == result);

        delete novi;

    }
    SECTION("Testing clear all"){

        GlavniMeniTest gl;


        qint32 expected = 0;
        auto scene = gl.tabla;
        Raspored* novi = new Raspored("novi");
        gl.m_currentRaspored = novi;
        gl.dodajNovSto();
        gl.dodajNovSto();
        gl.dodajNovSto();
        gl.obrisiSve();
        qint32 result = (scene->items()).size();

        REQUIRE(expected == result);

        delete novi;

    }
}

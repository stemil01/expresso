#include "mainwindow.h"
#include "unesiartikle.h"
#include <QApplication>
#include "krenisaradom.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*unesiartikle ua;
    ua.show();
    krenisaradom kr;
    kr.show();*/
    return a.exec();
}

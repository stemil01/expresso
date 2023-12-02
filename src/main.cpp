#include "mainwindow.h"
#include "unesiartikle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*unesiartikle ua;
    ua.show();*/
    return a.exec();
}

#include "mainwindow.h"
#include "unesiartikle.h"
#include <QApplication>
#include "krenisaradom.h"
#include "glavnimeni.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   /* MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();*/
    /*unesiartikle ua;
    ua.show();
    krenisaradom kr;
    kr.show()*/
    GlavniMeni gl;
    //gl.setWindowState(Qt::WindowFullScreen);
    gl.show();
    return a.exec();
}

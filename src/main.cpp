#include "unesiartikle.h"
#include <QApplication>
#include "glavnimeni.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlavniMeni gl;
    gl.setWindowState(Qt::WindowMaximized);
    gl.show();
    return a.exec();
}

#include "glavnimeni.h"
#include "meni.h"
#include "unesiartikle.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  GlavniMeni gl;
  gl.setWindowState(Qt::WindowMaximized);
  gl.show();
  return a.exec();
}

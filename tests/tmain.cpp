#define CATCH_CONFIG_RUNNER
#include <QApplication>
#include <catch.hpp>

int tmain(int argc, char **argv) {
  QApplication app(argc, argv);
  return Catch::Session().run(argc, argv);
}

#include "mainwindow.h"
#include <QApplication>

#include "src/Factory.hpp"

int main(int argc, char *argv[])
{
    Factory::Config(Factory::frameTransparent, Factory::mediumUIRS, Factory::mendiumEmpty, Factory::logicUiEmpty, "dupa");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

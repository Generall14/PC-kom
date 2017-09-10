#include "mainwindow.h"
#include <QApplication>

#include "src/Factory.hpp"

int main(int argc, char *argv[])
{
    Factory::Config(Factory::frameSG1, Factory::mediumUIRS, Factory::mendiumFakeGS1, Factory::logicUiSG1, Factory::frameBuilderSG1, Factory::logUITerm);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

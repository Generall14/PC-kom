#include "mainwindow.h"
#include <QApplication>

#include "src/Factory.hpp"

int main(int argc, char *argv[])
{
    Factory::Config(Factory::frameSG1, Factory::mediumUIRS, Factory::mendiumEmpty, "dupa");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

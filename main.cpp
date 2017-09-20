#include "mainwindow.h"
#include <QApplication>

#include "src/Factory.hpp"


int main(int argc, char *argv[])
{
#include "init.hpp"

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

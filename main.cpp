#include "mainwindow.h"
#include <QApplication>
#include <QSharedPointer>
#include "src/Frame.hpp"

#include "src/Factory.hpp"

#include "devices.hpp"

int main(int argc, char *argv[])
{
    qRegisterMetaType<QSharedPointer<Frame> >("QSharedPointer<Frame>");

    #include "init.hpp"

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

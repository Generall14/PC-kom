#include "mainwindow.h"
#include <QApplication>
#include <QSharedPointer>
#include <exception>
#include <QMessageBox>
#include "src/Frame.hpp"
#include "src/Factory.hpp"

int main(int argc, char *argv[])
{
    Factory::CreateExampleXML();

    qRegisterMetaType<QSharedPointer<Frame> >("QSharedPointer<Frame>");

    QApplication a(argc, argv);

    bool fake = false;
    QString set;
    for(QString arg:QApplication::arguments())
    {
        if(arg=="-f")
            fake = true;
        if(arg.lastIndexOf("-s")==0)
            set = arg.mid(2);
    }
    Factory::setFake(fake);

    try
    {
        Factory::LoadConfig(set);
    }
    catch (std::runtime_error ex)
    {
        QMessageBox::critical(nullptr, "FATAL ERROR!", ex.what(), QMessageBox::Abort);
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}


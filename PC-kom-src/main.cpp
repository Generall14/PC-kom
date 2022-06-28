#include "mainwindow.h"
#include <QApplication>
#include <QSharedPointer>
#include <exception>
#include <QMessageBox>

#include <Frame.hpp>
#include <Factory.hpp>
#include "Utils/GlobalXmlFile.hpp"
#include <QInputDialog>

int main(int argc, char *argv[])
{
//    Factory::CreateExampleXML();

    qRegisterMetaType<QSharedPointer<Frame> >("QSharedPointer<Frame>");

    QApplication a(argc, argv);

    bool fake = false, transparent = false;
    QString set;
    for(QString arg:QApplication::arguments())
    {
        if(arg=="-f")
            fake = true;
        if(arg.lastIndexOf("-s")==0)
            set = arg.mid(2);
        if(arg=="-tr")
            transparent = true;
    }
    Factory::setFake(fake);

    try
    {
//        QStringList ttt = {"sdfs", "fdsfgg"};
//        bool ok;
//        QInputDialog::getItem(0, "fdsfds", "Podaj nową nazwę", ttt, 0, false, &ok);
//        if(!ok)
//        {
//            return 0;
//        }//TODO
        Factory::LoadConfig(set);
    }
    catch (std::runtime_error ex)
    {
        QMessageBox::critical(nullptr, "FATAL ERROR!", ex.what(), QMessageBox::Abort);
        return -1;
    }

    Factory::setTransparent(transparent);

    MainWindow w;
    w.show();

    return a.exec();
}


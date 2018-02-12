#include "mainwindow.h"
#include <QApplication>
#include <QSharedPointer>
#include <exception>
#include <QMessageBox>
#include "src/Frame.hpp"
#include "src/LogicUI_imp/utils_ZR3/transactionDesc.hpp"

#include "src/Factory.hpp"

#include "devices.hpp"

int main(int argc, char *argv[])
{
    Factory::CreateExampleXML();

    qRegisterMetaType<QSharedPointer<Frame> >("QSharedPointer<Frame>");
    qRegisterMetaType<TransactionDesc>("TransactionDesc");

    QApplication a(argc, argv);

    bool fake = false;
    for(QString arg:QApplication::arguments())
    {
        if(arg=="-f"){
            fake = true;
            break;
        }
    }
    Factory::setFake(fake);

    try
    {
        Factory::LoadConfig();
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

#include "mainwindow.h"
#include <QApplication>
#include <QSharedPointer>
#include "src/Frame.hpp"
#include "src/LogicUI_imp/utils_ZR3/transactionDesc.hpp"

#include "src/Factory.hpp"

#include "devices.hpp"

int main(int argc, char *argv[])
{
    qRegisterMetaType<QSharedPointer<Frame> >("QSharedPointer<Frame>");
    qRegisterMetaType<TransactionDesc>("TransactionDesc");

    QApplication a(argc, argv);

    bool fake = false;
    qDebug() << QApplication::arguments();
    for(QString arg:QApplication::arguments())
    {
        if(arg=="-f"){
            fake = true;
            break;
        }
    }

    #include "init.hpp"

    MainWindow w;
    w.show();

    return a.exec();
}

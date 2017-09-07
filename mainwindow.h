#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QDebug>
#include <QTime>
#include "qtrswrapper.h"
#include "sg1frame.h"
#include <iostream>
#include <QSerialPortInfo>
#include <QMessageBox>
#include "src/MediumUI.hpp"
#include "src/Mendium.hpp"
#include "src/LogicUI.hpp"
#include "src/FrameBuilder.hpp"
#include "src/LogUI.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QtRSWrapper* RS;

    MediumUI* mediumUI = NULL; // ok
    Mendium* mendium = NULL; // ok
    LogicUI* logicUI = NULL; // ok
    FrameBuilder* frameBuilder = NULL; // ok
    LogUI* logUI = NULL; // ok

public slots:
    void Connected();
    void Disconnected();
    void DataReaded(QByteArray qb);
    void ErrorMessage(QString er);

signals:
    void HALT();
    void OpenRequest(QString);
    void CloseRequest();

private slots:
    void on_pushButton_disconnect_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_refresh_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_zapisz_clicked();
};

#endif // MAINWINDOW_H

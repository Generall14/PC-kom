#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Factory.hpp"
#include <QIcon>

#include "src/Factory.hpp"
#include <QSharedPointer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(Factory::WindowName());
    this->setWindowIcon(QIcon("ikona.ico"));

    RS = new QtRSWrapper();
    connect(this, SIGNAL(HALT()), RS, SLOT(Stop()));
    connect(RS, SIGNAL(Closed()), this, SLOT(Disconnected()));
    connect(RS, SIGNAL(Opened()), this, SLOT(Connected()));
    connect(this, SIGNAL(OpenRequest(QString)), RS, SLOT(Open(QString)));
    connect(this, SIGNAL(CloseRequest()), RS, SLOT(Close()));
    connect(RS, SIGNAL(Readed(QByteArray)), this, SLOT(DataReaded(QByteArray)));
    connect(RS, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));
    RS->start(QThread::HighPriority);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setVisible(false);

    on_pushButton_refresh_clicked();
    Disconnected();

    mediumUI = Factory::newMediumUI(ui->frame_medium);
    mendium = Factory::newMendium();

    connect(mediumUI, SIGNAL(ConnectRequest(QString)), mendium, SLOT(Open(QString)));
    connect(mediumUI, SIGNAL(DisconnectRequest()), mendium, SLOT(Close()));
    connect(mediumUI, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    connect(mendium, SIGNAL(Opened()), mediumUI, SLOT(Connected()));
    connect(mendium, SIGNAL(Closed()), mediumUI, SLOT(Disconnected()));
    connect(mendium, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    mendium->start(QThread::HighPriority);

    //....connects
    mediumUI->Init();

    QByteArray btemp = "dupa";
    btemp.append(QChar(0x0A));
    //Frame* asd = Factory::newFrame(btemp);
    QSharedPointer<Frame> asd = QSharedPointer<Frame>(Factory::newFrame(btemp));
    qDebug() << asd->toQString();
    //delete asd;
}

MainWindow::~MainWindow()
{
    if(RS)                                                             //Oczekiwanie na zakończenie działania zewnętrznego wątku
    {
        RS->terminate();
        delete RS;
        RS = 0;
    }

    if(mendium)                                                             //Oczekiwanie na zakończenie działania zewnętrznego wątku
    {
        mendium->terminate();
        delete mendium;
        mendium = 0;
    }

    delete mediumUI;

    delete ui;
}

void MainWindow::Connected()
{
    ui->pushButton_connect->setEnabled(false);
    ui->pushButton_disconnect->setEnabled(true);
    ui->pushButton_refresh->setEnabled(false);
    ui->comboBox->setEnabled(false);
}

void MainWindow::Disconnected()
{
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
    ui->pushButton_refresh->setEnabled(true);
    ui->comboBox->setEnabled(true);
}

void MainWindow::on_pushButton_disconnect_clicked()
{
    emit CloseRequest();
}

void MainWindow::on_pushButton_connect_clicked()
{
    emit OpenRequest(ui->comboBox->currentText());
}

void MainWindow::DataReaded(QByteArray qb)
{
    qDebug() << SG1Frame(qb).toQString();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem("DEV--->PC", QTableWidgetItem::UserType));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss"), QTableWidgetItem::UserType));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(SG1Frame(qb).toQString(), QTableWidgetItem::UserType));
    ui->tableWidget->setCurrentCell(ui->tableWidget->rowCount()-1, 0);
}

void MainWindow::on_pushButton_refresh_clicked()
{
    ui->comboBox->clear();
    for(QSerialPortInfo pi: QSerialPortInfo::availablePorts())
        ui->comboBox->addItem(pi.portName());
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::ErrorMessage(QString er)
{
    QMessageBox::critical(this, "NEIN! NEIN! NEIN! NEIN! NEIN!", er);
}

void MainWindow::on_pushButton_zapisz_clicked()
{
}

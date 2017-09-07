#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Factory.hpp"
#include <QIcon>
#include <QSharedPointer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(Factory::WindowName());
    this->setWindowIcon(QIcon(Factory::IcoPath()));

    mediumUI = Factory::newMediumUI(ui->frame_medium);
    mendium = Factory::newMendium();
    logicUI = Factory::newLogicUI(ui->frame_logicUI);
    frameBuilder = Factory::newFrameBuilder();
    logUI = Factory::newLogUI(ui->frame_log);

    connect(mediumUI, SIGNAL(ConnectRequest(QString)), mendium, SLOT(Open(QString)));
    connect(mediumUI, SIGNAL(DisconnectRequest()), mendium, SLOT(Close()));
    connect(mediumUI, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    connect(mendium, SIGNAL(Opened()), mediumUI, SLOT(Connected()));
    connect(mendium, SIGNAL(Opened()), logicUI, SLOT(Connected()));
    connect(mendium, SIGNAL(Closed()), mediumUI, SLOT(Disconnected()));
    connect(mendium, SIGNAL(Closed()), logicUI, SLOT(Disconnected()));
    connect(mendium, SIGNAL(Readed(QByteArray)), frameBuilder, SLOT(ByteReaded(QByteArray)));
    connect(mendium, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    connect(logicUI, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));
    connect(logicUI, SIGNAL(WriteFrame(QSharedPointer<Frame>)), frameBuilder, SLOT(FrameWrite(QSharedPointer<Frame>)));
    connect(logicUI, SIGNAL(WritePureData(QByteArray)), frameBuilder, SLOT(PureDataWrite(QByteArray)));

    connect(frameBuilder, SIGNAL(Write(QByteArray)), mendium, SLOT(Write(QByteArray)));
    connect(frameBuilder, SIGNAL(Write(QByteArray)), logUI, SLOT(FrameWrite(QByteArray)));
    connect(frameBuilder, SIGNAL(FrameReaded(QSharedPointer<Frame>)), logicUI, SLOT(FrameReaded(QSharedPointer<Frame>)));
    connect(frameBuilder, SIGNAL(FrameReaded(QSharedPointer<Frame>)), logUI, SLOT(FrameReaded(QSharedPointer<Frame>)));
    connect(frameBuilder, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    connect(logUI, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    mendium->start(QThread::HighPriority);
    frameBuilder->start(QThread::HighPriority);

    mediumUI->Init();
    logicUI->Init();
    logUI->Init();
}

MainWindow::~MainWindow()
{
    if(mendium)
    {
        mendium->terminate();
        delete mendium;
        mendium = 0;
    }

    if(frameBuilder)
    {
        frameBuilder->terminate();
        delete frameBuilder;
        frameBuilder = 0;
    }

    delete mediumUI;
    delete mendium;
    delete logicUI;
    delete logUI;

    delete ui;
}

void MainWindow::ErrorMessage(QString er)
{
    QMessageBox::critical(this, "NEIN! NEIN! NEIN! NEIN! NEIN!", er);
}

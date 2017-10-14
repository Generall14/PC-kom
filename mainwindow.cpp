#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Factory.hpp"
#include <QIcon>
#include <QSharedPointer>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDir cdir("./configs/");
    if (!cdir.exists())
        cdir.mkpath(".");

    ui->setupUi(this);

    this->setWindowTitle(Factory::WindowName());
    this->setWindowIcon(QIcon(Factory::IcoPath()));

    mediumUI = Factory::newMediumUI(ui->frame_medium);
    mendium = Factory::newMendium();
    logicUI = Factory::newLogicUI(ui->frame_logicUI);
    frameBuilder = Factory::newFrameBuilder();
    logUI = Factory::newLogUI(ui->frame_log);
    logFile = Factory::newLogFile();

    connect(this, SIGNAL(HALT()), mendium, SLOT(Stop()));
    connect(this, SIGNAL(HALT()), frameBuilder, SLOT(Stop()));

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

    connect(frameBuilder, SIGNAL(Write(QSharedPointer<Frame>)), mendium, SLOT(Write(QSharedPointer<Frame>)));
    connect(frameBuilder, SIGNAL(Write(QSharedPointer<Frame>)), logUI, SLOT(FrameWrite(QSharedPointer<Frame>)));
    connect(frameBuilder, SIGNAL(FrameReaded(QSharedPointer<Frame>)), logicUI, SLOT(FrameReaded(QSharedPointer<Frame>)));
    connect(frameBuilder, SIGNAL(FrameReaded(QSharedPointer<Frame>)), logUI, SLOT(FrameReaded(QSharedPointer<Frame>)));
    connect(frameBuilder, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    connect(logUI, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));
    connect(logUI, SIGNAL(LogString(QString)), logFile, SLOT(LogString(QString)));

    mendium->start(QThread::HighPriority);
    frameBuilder->start(QThread::HighPriority);

    mediumUI->Init();
    logicUI->Init();
    logUI->Init();

    connect(this, SIGNAL(FakeDiscinnect()), mendium, SLOT(Close()));
    emit FakeDiscinnect();
}

MainWindow::~MainWindow()
{
    emit HALT();
    while(mendium->isRunning()){}
    while(frameBuilder->isRunning()){}

    delete mediumUI;
    delete mendium;
    delete logicUI;
    delete logUI;
    delete logFile;

    delete ui;
}

void MainWindow::ErrorMessage(QString er)
{
    QMessageBox::critical(this, "NEIN! NEIN! NEIN! NEIN! NEIN!", er);
}

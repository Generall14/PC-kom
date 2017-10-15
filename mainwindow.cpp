#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Factory.hpp"
#include <QIcon>
#include <QSharedPointer>
#include <QDir>
#include <QLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QDir cdir("./configs/");
    if (!cdir.exists())
        cdir.mkpath(".");

    this->InitGUI();
    this->InitStructure();

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
    delete logFormater;
}

void MainWindow::InitStructure()
{
    mediumUI = Factory::newMediumUI(frameMedium);
    mendium = Factory::newMendium();
    logicUI = Factory::newLogicUI(frameLogicUI);
    frameBuilder = Factory::newFrameBuilder();
    logUI = Factory::newLogUI(frameLogUI);
    logFile = Factory::newLogFile();
    logFormater = Factory::newLogFormater();

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
    connect(frameBuilder, SIGNAL(Write(QSharedPointer<Frame>)), logFormater, SLOT(FrameWrite(QSharedPointer<Frame>)));
    connect(frameBuilder, SIGNAL(FrameReaded(QSharedPointer<Frame>)), logicUI, SLOT(FrameReaded(QSharedPointer<Frame>)));
    connect(frameBuilder, SIGNAL(FrameReaded(QSharedPointer<Frame>)), logFormater, SLOT(FrameReaded(QSharedPointer<Frame>)));
    connect(frameBuilder, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    connect(logUI, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    connect(logFile, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));

    connect(logFormater, SIGNAL(Error(QString)), this, SLOT(ErrorMessage(QString)));
    connect(logFormater, SIGNAL(LogFileString(QString)), logFile, SLOT(LogString(QString)));
    connect(logFormater, SIGNAL(LogUIString(QString,bool)), logUI, SLOT(LogString(QString,bool)));

    mendium->start(QThread::HighPriority);
    frameBuilder->start(QThread::HighPriority);

    mediumUI->Init();
    logicUI->Init();
    logUI->Init();
}

void MainWindow::InitGUI()
{
    this->setWindowTitle(Factory::WindowName());
    this->setWindowIcon(QIcon(Factory::IcoPath()));

    this->setGeometry(QRect(this->pos(), QPoint(1100, 690)));

    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QHBoxLayout* mainLay = new QHBoxLayout();
    mainLay->setMargin(6);
    this->centralWidget()->setLayout(mainLay);

    frameLogUI = new QFrame(this);
    mainLay->addWidget(frameLogUI);

    QFrame* rightFrame = new QFrame(this);
    rightFrame->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    mainLay->addWidget(rightFrame);

    QVBoxLayout* rightLay = new QVBoxLayout();
    rightLay->setMargin(0);
    rightFrame->setLayout(rightLay);

    frameMedium = new QFrame(this);
    rightLay->addWidget(frameMedium);

    frameLogicUI = new QFrame(this);
    rightLay->addWidget(frameLogicUI);
}

void MainWindow::ErrorMessage(QString er)
{
    QMessageBox::critical(this, "NEIN! NEIN! NEIN! NEIN! NEIN!", er);
}

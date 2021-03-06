#include "mainwindow.h"
#include "src/Factory.hpp"
#include "src/Utils/About.hpp"
#include <QIcon>
#include <QSharedPointer>
#include <QDir>
#include <QLayout>
#include <QDebug>
#include <QScrollArea>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->InitGUI();

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
    connect(frameBuilder, SIGNAL(IgnoredFrame(QSharedPointer<Frame>)), logFormater, SLOT(FrameIgnored(QSharedPointer<Frame>)));

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
    this->setWindowIcon(QIcon(Factory::IcoPath()));
    if(Factory::IsFake())
        this->setWindowTitle(Factory::WindowName() + " <Fake>");
    else
        this->setWindowTitle(Factory::WindowName());

    this->resize(1100, 750);

    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QHBoxLayout* mainLay = new QHBoxLayout();
    mainLay->setContentsMargins(2, 6, 2, 2);
    mainLay->setSpacing(3);
    this->centralWidget()->setLayout(mainLay);

    frameLogUI = new QFrame(this);
    frameLogUI->setFrameShape(QFrame::StyledPanel);
    frameLogUI->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    auto sp = frameLogUI->sizePolicy();
    sp.setHorizontalStretch(17);
    frameLogUI->setSizePolicy(sp);
    mainLay->addWidget(frameLogUI);

    QFrame* rightFrame = new QFrame(this);
    rightFrame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    auto sp2 = rightFrame->sizePolicy();
    sp2.setHorizontalStretch(13);
    rightFrame->setSizePolicy(sp2);
    mainLay->addWidget(rightFrame);

    QVBoxLayout* rightLay = new QVBoxLayout();
    rightLay->setMargin(0);
    rightFrame->setLayout(rightLay);

    frameMedium = new QFrame(this);
    frameMedium->setFrameShape(QFrame::StyledPanel);
    frameMedium->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    rightLay->addWidget(frameMedium);

    frameLogicUI = new QFrame(this);
    frameLogicUI->setFrameShape(QFrame::StyledPanel);

    this->InitStructure();

    QScrollArea* sa = new QScrollArea();
    sa->setWidget(frameLogicUI);
    sa->setWidgetResizable(true);
    rightLay->addWidget(sa);
}

void MainWindow::ErrorMessage(QString er)
{
    QMessageBox::critical(this, "NEIN! NEIN! NEIN! NEIN! NEIN!", er);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_F1)
    {
        About* about = new About(mediumUI->Description(), logicUI->Description(), logUI->Description(), this);
        about->exec();
        about->deleteLater();
    }
    else
        QMainWindow::keyPressEvent(event);
}

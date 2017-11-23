#include "LogicUIZR3.hpp"
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QInputDialog>
#include <QFile>

LogicUIZR3::LogicUIZR3(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUIZR3";
}

LogicUIZR3::~LogicUIZR3()
{
    for(ZR3UIFrame* fr:devsList)
        delete fr;
}

void LogicUIZR3::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(1);

    qtw = new QTabWidget();
    qtw->setMinimumWidth(400);
    qtw->setMinimumHeight(800);
    mainLay->addWidget(qtw);

    dbgFrame = new QFrame();
    qtw->addTab(dbgFrame, "Debug");
    QVBoxLayout* mainDbgLay = new QVBoxLayout(dbgFrame);


    QHBoxLayout* littleLay = new QHBoxLayout();
    mainDbgLay->addLayout(littleLay);
    adrLw = new QListWidget();
    adrLw->setMaximumWidth(120);
    adrLw->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(adrLw, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(AdrOpen()));
    littleLay->addWidget(adrLw);

    QVBoxLayout* rrLay = new QVBoxLayout();
    littleLay->addLayout(rrLay);
    QPushButton* btnrun = new QPushButton("Otwórz");
    btnrun->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnrun, SIGNAL(clicked(bool)), this, SLOT(AdrOpen()));
    rrLay->addWidget(btnrun);

    btnrun = new QPushButton("Open all");
    btnrun->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnrun, SIGNAL(clicked(bool)), this, SLOT(AdrOpenAll()));
    rrLay->addWidget(btnrun);

    btnrun = new QPushButton("Dodaj");
    btnrun->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnrun, SIGNAL(clicked(bool)), this, SLOT(AdrAdd()));
    rrLay->addWidget(btnrun);

    btnrun = new QPushButton("Usuń");
    btnrun->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnrun, SIGNAL(clicked(bool)), this, SLOT(AdrDelete()));
    rrLay->addWidget(btnrun);

    btnrun = new QPushButton("Z pliku");
    btnrun->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnrun, SIGNAL(clicked(bool)), this, SLOT(AdrFromFile()));
    rrLay->addWidget(btnrun);

    littleLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));



    mainDbgLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QLabel* tempLabel = new QLabel("Tu będzie coś do ZR-3");
    mainDbgLay->addWidget(tempLabel);

    btn = new QPushButton("Wyślij coś");
    mainDbgLay->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(makeStupidMessage()));

    btnE = new QPushButton("Wygeneruj bezsensowny błąd");
    mainDbgLay->addWidget(btnE);
    connect(btnE, SIGNAL(clicked(bool)), this, SLOT(makeStupidError()));
}

void LogicUIZR3::ZR3UIFrameAdrChanged(uchar adr)
{
    ZR3UIFrame* zr = qobject_cast<ZR3UIFrame*>(sender());
    int idx = devsList.indexOf(zr);
    if(idx>=0)
    {
        QString nadr = QString::number(adr, 16).toUpper();
        while(nadr.length()<2)
            nadr.insert(0, '0');
        nadr.insert(0, "0x");
        qtw->setTabText(idx+1, nadr);
    }
}

void LogicUIZR3::AdrAdd()
{
    bool ok;
    QString text = QInputDialog::getText(cParent, "Podaj adres", "Adres:", QLineEdit::Normal, "1a", &ok);

    if(!ok)
        return;

    text = text.left(2);
    text.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane adresu \""+text+"\".");
        return;
    }

    text = "0x"+text.toUpper();
    if(adrLw->findItems(text, Qt::MatchFixedString).isEmpty())
        adrLw->addItem(text);
    else
        emit Error("Adres już istnieje");
}

void LogicUIZR3::AdrDelete()
{
    delete adrLw->takeItem(adrLw->currentIndex().row());
}

void LogicUIZR3::AdrOpen()
{
    if(adrLw->currentIndex().row()<0)
        return;

    AddZR3Dev(adrLw->currentItem()->text());
}

void LogicUIZR3::AdrOpenAll()
{
    QListWidgetItem* item;
    int row = 0;
    while(item = adrLw->item(row++))
        AddZR3Dev(item->text());
}

void LogicUIZR3::AddZR3Dev(QString str)
{
    bool ok;
    uchar nadr = str.toInt(&ok, 16);
    if(!ok)
        return;

    for(ZR3UIFrame* fr:devsList)
    {
        if(nadr==fr->Adr())
            return;
    }

    QFrame* newFrame = new QFrame();
    qtw->addTab(newFrame, str);
    ZR3UIFrame* newzr3 = new ZR3UIFrame(newFrame, nadr);
    if(!connected)
        newFrame->setEnabled(false);
    connect(newzr3, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)), Qt::QueuedConnection);
    connect(newzr3, SIGNAL(FrameToMendium(QSharedPointer<Frame>)), this, SIGNAL(WriteFrame(QSharedPointer<Frame>)), Qt::QueuedConnection);
    connect(newzr3, SIGNAL(PureDataToMedium(QByteArray)), this, SIGNAL(WritePureData(QByteArray)), Qt::QueuedConnection);
    connect(newzr3, SIGNAL(AdresChanged(uchar)), this,SLOT(ZR3UIFrameAdrChanged(uchar)), Qt::QueuedConnection);
    connect(this, SIGNAL(InternalFrame(QSharedPointer<Frame>)), newzr3, SLOT(FrameToUI(QSharedPointer<Frame>)), Qt::QueuedConnection);
    devsList.push_back(newzr3);
    tabsList.append(newFrame);
    newzr3->Init();
}

void LogicUIZR3::AdrFromFile()
{
    QFile config1File("inputs/MendiumBusConnectorIn.cfg");
    if(!config1File.open(QIODevice::Text | QIODevice::ReadOnly))
        emit Error("Nie można odczytać pliku konfiguracyjnego \"inputs/MendiumBusConnectorIn.cfg\"");
    else
    {
        adrLw->clear();
        QTextStream in(&config1File);
        QFile littleFiles;
        while(!in.atEnd())
        {
            QString temoAdr = in.readLine();
            littleFiles.setFileName(temoAdr);
            if(!littleFiles.open(QIODevice::Text | QIODevice::ReadOnly))
                emit Error("Nie można odczytać pliku konfiguracyjnego \"" + temoAdr + "\"");
            else
            {
                char val = littleFiles.readAll().at(0);
                QString ttt = QString::number((int)val, 16).toUpper();
                while(ttt.length()<2)
                    ttt.insert(0, '0');
                adrLw->addItem("0x"+ttt);
                littleFiles.close();
            }
        }
        config1File.close();
    }
}

void LogicUIZR3::Connected()
{
    btn->setEnabled(true);
    connected = true;

    for(QFrame* fr: tabsList)
        fr->setEnabled(true);
}

void LogicUIZR3::Disconnected()
{
    btn->setEnabled(false);
    connected = false;

    for(QFrame* fr: tabsList)
        fr->setEnabled(false);
}

void LogicUIZR3::FrameReaded(QSharedPointer<Frame> frame)
{
    emit InternalFrame(frame);
}

void LogicUIZR3::makeStupidMessage()
{
    QByteArray temp;
    temp.append(QChar(0x01));
    temp.append(QChar(0x0a));
    temp.append(QChar(0x00));
    temp.append(QChar(0x00));
    temp.append(QChar(0x04));
    qDebug() << temp;
    emit WritePureData(temp);
}

void LogicUIZR3::makeStupidError()
{
    emit Error("Bezsensowny błąd.");
}

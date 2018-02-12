#include "About.hpp"
#include <QDebug>
#include <QLayout>
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include "../Factory.hpp"
#include "../Mendium.hpp"
#include "../Frame.hpp"
#include "../FrameBuilder.hpp"
#include "../LogFormater.hpp"
#include "../LogFile.hpp"
#include "../BusDevice.hpp"

About::About(QString mediumUI, QString logicUI, QString logUI, QWidget* parent):
    QDialog(parent),
    _mediumUI(mediumUI),
    _logicUI(logicUI),
    _logUI(logUI)
{
    this->setWindowTitle("About");

    InitWidgets();
}

About::~About()
{
}

void About::InitWidgets()
{
    QHBoxLayout* mainHLay = new QHBoxLayout(this);

    QVBoxLayout* icoLay = new QVBoxLayout();
    mainHLay->addLayout(icoLay);

    QLabel* icoLabel = new QLabel(this);
    icoLay->addWidget(icoLabel);
    pic.load(Factory::IcoPath());
    icoLabel->setPixmap(pic);
    icoLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Maximum, QSizePolicy::Expanding));

    QVBoxLayout* txtLay = new QVBoxLayout();
    mainHLay->addLayout(txtLay);

    QLabel* l1 = new QLabel("PC-Kom", this);
    l1->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l1);

    QLabel* l2 = new QLabel("Autor: mgr inż. Wojciech Kogut", this);
    l2->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l2);

    QLabel* l3 = new QLabel("Build z dnia " + QString(__DATE__) + " - " + QString(__TIME__), this);
    l3->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l3);

    QLabel* l4 = new QLabel("Numer wersji w Git: " + QString(GIT_VERSION), this);
    l4->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l4);

    if(Factory::IsFake())
    {
        l4 = new QLabel(this);
        txtLay->addWidget(l4);
        l4 = new QLabel("< Wersja udawana >", this);
        l4->setAlignment(Qt::AlignCenter);
        txtLay->addWidget(l4);
        l4 = new QLabel(this);
        txtLay->addWidget(l4);
    }

    QTextBrowser* te = new QTextBrowser(this);
    te->setText(Factory::ConfigDescription());
    te->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    txtLay->addWidget(te);

    QLabel* l5 = new QLabel("Zestawienie implementacji:", this);
    l5->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l5);

    Mendium* temp = Factory::newMendium();
    l5 = new QLabel("Mendium -> " + temp->Description(), this);
    l5->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l5);
    delete temp;

    l5 = new QLabel("MediumUI -> " + _mediumUI, this);
    l5->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l5);

    Frame* temp2 = Factory::newFrame(QByteArray());
    l5 = new QLabel("Frame -> " + temp2->Description(), this);
    l5->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l5);
    delete temp2;

    FrameBuilder* temp3 = Factory::newFrameBuilder();
    l5 = new QLabel("FrameBuilder -> " + temp3->Description(), this);
    l5->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l5);
    delete temp3;

    l5 = new QLabel("LogicUI -> " + _logicUI, this);
    l5->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l5);

    LogFormater* temp4 = Factory::newLogFormater();
    l5 = new QLabel("LogFormater -> " + temp4->Description(), this);
    l5->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l5);
    delete temp4;

    LogFile* temp5 = Factory::newLogFile();
    l5 = new QLabel("LogFile -> " + temp5->Description(), this);
    l5->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l5);
    delete temp5;

    l5 = new QLabel("LogUI -> " + _logUI, this);
    l5->setAlignment(Qt::AlignCenter);
    txtLay->addWidget(l5);

    QHBoxLayout* btnLay = new QHBoxLayout();
    txtLay->addLayout(btnLay);
    QPushButton* btn = new QPushButton("Wyślij litanie dziękczynne do autora");
    btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(btn, &QPushButton::clicked, [=](){QDesktopServices::openUrl(QUrl("mailto:wojciech_kogut@o2.pl?subject=O najwspanialszy z wspaniałych&body=...", QUrl::TolerantMode));});
    btnLay->addWidget(btn);
}

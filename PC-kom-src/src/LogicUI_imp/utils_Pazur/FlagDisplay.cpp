#include "FlagDisplay.hpp"
#include <QGroupBox>
#include <QLayout>
#include <QToolButton>
#include <qdebug.h>

FlagsDisplay::FlagsDisplay(QLayout* parent, QString name, QStringList flags):
    cParent(parent),
    _name(name),
    _flags(flags)
{
    Init();
    Clear();
}

FlagsDisplay::~FlagsDisplay()
{
    delete timer;
    delete timer2;
}

void FlagsDisplay::Init()
{
    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(Clear()));

    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(UpdTimer()));
    //timer2->start(1000);

    QGroupBox *gb = new QGroupBox(_name);
    cParent->addWidget(gb);
    mlay = new QVBoxLayout();
    gb->setLayout(mlay);

    QHBoxLayout* tlay = new QHBoxLayout();
    QToolButton* tb = new QToolButton();
    connect(tb, SIGNAL(clicked()), this, SLOT(Clear()));
    tlay->addWidget(tb);
    tlay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labTimer = new QLabel("Last update: ?? s");
    tlay->addWidget(labTimer);
    mlay->addLayout(tlay);

    for(auto flag: _flags)
    {
        QLabel* lab = new QLabel(flag);
        mlay->addWidget(lab);
        labs.append(lab);
    }

    mlay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void FlagsDisplay::Clear()
{
    for(QLabel* lab: labs)
        lab->setStyleSheet("font-weight: normal; color: gray");
}

void FlagsDisplay::UpdTimer()
{
    labTimer->setText("Last update: "+QString::number(intTimer++)+" s");
}

void FlagsDisplay::UpdateFlags(QByteArray flags)
{
    if(!timer2->isActive())
        timer2->start(1000);
    intTimer = 0;
    UpdTimer();
    timer->start(180000);
    Clear();
    for(int byte = 0;byte<flags.size();byte++)
    {
        for(int bit = 0;bit<8;bit++)
        {
            if((flags.at(byte)>>bit)&0x01)
                SetFlag((byte*8)+bit);
        }
    }
}

void FlagsDisplay::SetFlag(int nr)
{
    while(nr>=labs.size())
    {
        QLabel* unknown = new QLabel("Nieznana flaga");
        mlay->insertWidget(mlay->count()-1, unknown);
        labs.push_back(unknown);
    }
    labs.at(nr)->setStyleSheet("font-weight: bold; color: red");
}

#include "FlagDisplay.hpp"
#include <QGroupBox>
#include <QLayout>
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

}

void FlagsDisplay::Init()
{
    QGroupBox *gb = new QGroupBox(_name);
    cParent->addWidget(gb);
    mlay = new QVBoxLayout();
    gb->setLayout(mlay);

    for(auto flag: _flags)
    {
        QLabel* lab = new QLabel(flag);
        mlay->addWidget(lab);
        labs.append(lab);
    }
}

void FlagsDisplay::Clear()
{
    for(QLabel* lab: labs)
        lab->setStyleSheet("font-weight: normal; color: gray");
    if(unknown)
        unknown->setStyleSheet("font-weight: normal; color: gray");
}

void FlagsDisplay::UpdateFlags(QByteArray flags)
{
    Clear();
    for(int byte = 0;byte<flags.size();byte++)
    {
        for(int bit = 0;bit<8;bit++)
        {
            if((flags.at(byte)>>bit)&0x01)
            {
                int num = (byte*8)+bit;
                if(num>=labs.size())
                {
                    if(!unknown)
                    {
                        unknown = new QLabel("Nieznana flaga");
                        mlay->addWidget(unknown);

                    }
                    unknown->setStyleSheet("font-weight: bold; color: red");
                }
                else
                    labs.at(num)->setStyleSheet("font-weight: bold; color: red");
            }
        }
    }
}

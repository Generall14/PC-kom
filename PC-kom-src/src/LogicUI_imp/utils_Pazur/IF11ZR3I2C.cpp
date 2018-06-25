#include "IF11ZR3I2C.hpp"
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include "Frame_imp/utils_Pazur/PureMessageZR3IIC.hpp"
#include "Frame_imp/utils_Pazur/PureMessageZR3.hpp"
#include "Frame_imp/utils_Pazur/PureMessage.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"
#include <qdebug.h>
#include "Frame_imp/FramePazur.hpp"

IF11ZR3I2c::IF11ZR3I2c(QFrame* parent, uint adress):
    cParent(parent),
    _adr(adress)
{
    Init();
}

IF11ZR3I2c::~IF11ZR3I2c()
{
}

void IF11ZR3I2c::InitRest()
{
    const uint smallMIN_PB_W = MIN_PB_W/2;

    QHBoxLayout* smLay = new QHBoxLayout();
    mainLay->addLayout(smLay);
    QPushButton* pb = new QPushButton("slaveTEST");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveTEST()));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay->addWidget(pb);
    smLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("slaveRST");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRST()));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay->addWidget(pb);
    smLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rdVersion");
//    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
//                    PureMessageZR3IIC::slaveRST()));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay->addWidget(pb);

    QHBoxLayout* smLay2 = new QHBoxLayout();
    mainLay->addLayout(smLay2);
    pb = new QPushButton("rdBuildTime");
//    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
//                    PureMessageZR3IIC::slaveRST()));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay2->addWidget(pb);
    smLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rdDevStats");
//    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
//                    PureMessageZR3IIC::slaveRST()));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay2->addWidget(pb);
    smLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rdErrorFlags");
//    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
//                    PureMessageZR3IIC::slaveRST()));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay2->addWidget(pb);
}

void IF11ZR3I2c::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    QHBoxLayout* toAdrLay = new QHBoxLayout();
    mainLay->addLayout(toAdrLay);

    InitRest();
    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
}

void IF11ZR3I2c::internalFrameReaded(QSharedPointer<Frame> fr)
{
//    if(!(*fr).isValid())
//        return;
//    if(((*fr).pureData().at(0)&0x3F)!=(leToAdr->text().toInt(nullptr, 16)&0x3F))
//        return;
//    FramePazur paz(fr->pureData());
//    for(auto msg: paz.getMessages().getMessages())
//    {
//        if((msg.toPureData().at(0)&0xC0)==0xC0) // ifs = 3
//        {
//            QByteArray mm = msg.toPureData().mid(2);
//            if(mm.size()<1)
//                return;
//            if(mm.at(0)==0x01)
//            {
//                if(mm.size()<3)
//                    return;
//                letechACCrnd->setText(QString("%1%2").arg((uint)mm.at(2)&0xFF, 2, 16, QChar('0'))
//                                      .arg((uint)mm.at(1)&0xFF, 2, 16, QChar('0')).toUpper());
//                return;
//            }
//            else if((mm.at(0)&0x3F)==0x3E) // RDo
//            {
//                if(mm.size()<3)
//                    return;
//                uchar nr = mm.at(1);
//                mm = mm.mid(2);
//                switch(nr)
//                {
//                case 0x00:
//                {
//                    if(mm.size()<2)
//                        return;
//                    uint ver = 0;
//                    ver |= mm.at(0)&0xFF;
//                    ver |= (mm.at(1)<<8)&0xFF00;
//                    labWer->setText(QString::number(ver));
//                    break;
//                }
//                case 0x01:
//                    labBuild->setText(mm);
//                    break;
//                case 0x03:
//                {
//                    if(mm.size()<3)
//                        return;
//                    uint ver = 0;
//                    ver |= mm.at(0)&0xFF;
//                    ver |= (mm.at(1)<<8)&0xFF00;
//                    ver |= (mm.at(2)<<16)&0xFF0000;
//                    labDevId->setText(QString("0x%1").arg(ver&0xFFFFFF, 6, 16, QChar('0')));
//                    break;
//                }
//                case 0x04:
//                {
//                    if(mm.size()<20)
//                        return;
//                    uint ver = 0;
//                    ver |= mm.at(0)&0xFF;
//                    ver |= (mm.at(1)<<8)&0xFF00;
//                    labStarts->setText(QString::number(ver));
//                    ver = 0;
//                    ver |= mm.at(2)&0xFF;
//                    ver |= (mm.at(3)<<8)&0xFF00;
//                    labVDown->setText(QString::number(ver));
//                    ver = 0;
//                    ver |= mm.at(4)&0xFF;
//                    ver |= (mm.at(5)<<8)&0xFF00;
//                    ver |= (mm.at(6)<<16)&0xFF0000;
//                    ver |= (mm.at(7)<<24)&0xFF000000;
//                    labTOn->setText(QString::number(ver));
//                    labTDose->setText(QString::number(SU::byteArray322Float32(mm.mid(8, 4))));
//                    labMDRate->setText(QString::number(SU::byteArray322Float32(mm.mid(12, 4))));
//                    ver = 0;
//                    ver |= mm.at(16)&0xFF;
//                    ver |= (mm.at(17)<<8)&0xFF00;
//                    labMUdr->setText(QString::number(ver));
//                    ver = 0;
//                    ver |= mm.at(18)&0xFF;
//                    ver |= (mm.at(19)<<8)&0xFF00;
//                    labUdr->setText(QString::number(ver));
//                    break;
//                }
//                case 0x05:
//                    labRLadd->setText(QString::number(mm.at(0)));
//                    break;
//                default:
//                    break;
//                }
//            }
//        }
//    }
}

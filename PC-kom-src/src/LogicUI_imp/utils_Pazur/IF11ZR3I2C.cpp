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
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(0)));
                    labWer->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay->addWidget(pb);
    smLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rdBuildTime");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(1)));
                    labWer->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay->addWidget(pb);

    QHBoxLayout* smLay2 = new QHBoxLayout();
    mainLay->addLayout(smLay2);
    pb = new QPushButton("rdDevStats");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(2)));
                    labStarts->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay2->addWidget(pb);
    smLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rdErrorFlags");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(3)));
                    labErrorFLags->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay2->addWidget(pb);
    smLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rCLK");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(4)));
                    labRCLK->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay2->addWidget(pb);

    QHBoxLayout* labsLay = new QHBoxLayout();
    mainLay->addLayout(labsLay);
    QLabel* lab = new QLabel("Wersja: ");
    labsLay->addWidget(lab);
    labWer = new QLabel("?");
    labsLay->addWidget(labWer);
    labsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Build: ");
    labsLay->addWidget(lab);
    labBuild = new QLabel("?");
    labsLay->addWidget(labBuild);
    labsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Starts: ");
    labsLay->addWidget(lab);
    labStarts = new QLabel("?");
    labsLay->addWidget(labStarts);
    labsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Errors: ");
    labsLay->addWidget(lab);
    labErrorFLags = new QLabel("?");
    labsLay->addWidget(labErrorFLags);

    QHBoxLayout* labsLay2 = new QHBoxLayout();
    mainLay->addLayout(labsLay2);
    lab = new QLabel("rCLK cnt: ");
    labsLay2->addWidget(lab);
    labRCLK = new QLabel("?");
    labsLay2->addWidget(labRCLK);
    labsLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* reg1Lay = new QHBoxLayout();
    mainLay->addLayout(reg1Lay);
    pb = new QPushButton("Read");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(4)));
                    sbRegThr->setValue(0);});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    reg1Lay->addWidget(pb);
    pb = new QPushButton("Write");
    connect(pb, &QPushButton::clicked, [this](){QByteArray temp; uint val = sbRegThr->value()*1024.0/3.6;
                    temp.append(val&0xFF); temp.append((val>>8)&0xFF);
                    send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveWRSECTION(4, temp)));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    reg1Lay->addWidget(pb);
    reg1Lay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Reg. progu wyzwalania: [V]");
    reg1Lay->addWidget(lab);
    sbRegThr = new QDoubleSpinBox();
    sbRegThr->setValue(0);
    sbRegThr->setMinimum(0);
    sbRegThr->setMaximum(1.6);
    sbRegThr->setDecimals(3);
    reg1Lay->addWidget(sbRegThr);

    QHBoxLayout* reg2Lay = new QHBoxLayout();
    mainLay->addLayout(reg2Lay);
    pb = new QPushButton("Read");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(5)));
                    sbRegBias->setValue(0);});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    reg2Lay->addWidget(pb);
    pb = new QPushButton("Write");
    connect(pb, &QPushButton::clicked, [this](){QByteArray temp; uint val = sbRegBias->value()*1024.0/3.6;
                    temp.append(val&0xFF); temp.append((val>>8)&0xFF);
                    send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveWRSECTION(5, temp)));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    reg2Lay->addWidget(pb);
    reg2Lay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Reg. korekty bias: [V]");
    reg2Lay->addWidget(lab);
    sbRegBias = new QDoubleSpinBox();
    sbRegBias->setValue(0);
    sbRegBias->setMinimum(0);
    sbRegBias->setMaximum(1.6);
    sbRegBias->setDecimals(3);
    reg2Lay->addWidget(sbRegBias);
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
    if(!(*fr).isValid())
        return;
    FramePazur paz(fr->pureData());
    for(auto msg: paz.getMessages().getMessages())
    {
        if((msg.toPureData().at(0)&0xC0)==0xC0) // ifs = 3
        {
            QByteArray mm = msg.toPureData().mid(2);
            if(mm.size()<4)
                return;
            if(mm.at(0)!=PureMessageZR3::techRDIIC_C)
                return;
            if(uchar(mm.at(1))!=_adr)
                return;

            uchar code = mm.at(3);
            QByteArray iicd = mm.mid(4);
            if(code==PureMessageZR3IIC::masterRDSECTIONo_c)
            {
                uchar section = iicd.at(0);
                switch (section)
                {
                case 0:
                {
                    uint ver = 0;
                    ver |= iicd.at(1)&0xFF;
                    ver |= (iicd.at(2)<<8)&0xFF00;
                    labWer->setText(QString("0x%1").arg(ver&0xFFFF, 4, 16, QChar('0')));
                    break;
                }
                case 1:
                {
                    labBuild->setText(iicd.mid(1));
                    break;
                }
                case 2:
                {
                    uint ver = 0;
                    ver |= iicd.at(1)&0xFF;
                    ver |= (iicd.at(2)<<8)&0xFF00;
                    labStarts->setText(QString::number(ver));
                    break;
                }
                case 3:
                {
                    labErrorFLags->setText(QString("0b%1").arg(iicd.at(1)&0xFF, 8, 2, QChar('0')));
                    break;
                }
                case 4:
                {
                    uint ver = 0;
                    ver |= iicd.at(1)&0xFF;
                    ver |= (iicd.at(2)<<8)&0xFF00;
                    sbRegThr->setValue(float(ver)/1024.0*3.6);
                    break;
                }
                case 5:
                {
                    uint ver = 0;
                    ver |= iicd.at(1)&0xFF;
                    ver |= (iicd.at(2)<<8)&0xFF00;
                    sbRegBias->setValue(float(ver)/1024.0*3.6);
                    break;
                }
                default:
                    break;
                }
            }
        }
    }
}

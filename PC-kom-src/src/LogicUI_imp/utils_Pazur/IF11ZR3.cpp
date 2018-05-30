#include "IF11ZR3.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessageZR3.hpp"
#include "Frame_imp/utils_Pazur/PureMessage.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"
#include <qdebug.h>
#include "Frame_imp/FramePazur.hpp"

IF11ZR3::IF11ZR3(QFrame* parent):
    IFPanel(parent, "IF11ZR3base"),
    Restorable("IF11ZR3")
{
    Init();
}

IF11ZR3::~IF11ZR3()
{
    Store("letechACCrnd", letechACCrnd->text());
    Store("sbtechRDSECTION", sbtechRDSECTION->value());
    Store("letechWRSECTIONmagic", letechWRSECTIONmagic->text());
    Store("letechWRSECTION", letechWRSECTION->text());
    Store("sbtechWRSECTION", sbtechWRSECTION->value());
}

void IF11ZR3::LoadConfigs()
{
    letechACCrnd->setText(RestoreAsString("letechACCrnd", "1234"));
    sbtechRDSECTION->setValue(RestoreAsInt("sbtechRDSECTION", 0));
    letechWRSECTIONmagic->setText(RestoreAsString("letechWRSECTIONmagic", "1234"));
    letechWRSECTION->setText(RestoreAsString("letechWRSECTION", ""));
    sbtechWRSECTION->setValue(RestoreAsInt("sbtechWRSECTION", 0));
}

void IF11ZR3::InitRest()
{
    QHBoxLayout* techREQLay = new QHBoxLayout();
    mainLay->addLayout(techREQLay);
    QPushButton* pb = new QPushButton("techREQ");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techREQ(leMagic->text().toInt(nullptr, 16)), 3);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techREQLay->addWidget(pb);
    techREQLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* techACCLay = new QHBoxLayout();
    mainLay->addLayout(techACCLay);
    pb = new QPushButton("techACC");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(
                    PureMessageZR3::techACC(leMagic->text().toInt(nullptr, 16), letechACCrnd->text().toInt(nullptr, 16)), 3);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techACCLay->addWidget(pb);
    techACCLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    QLabel* lab = new QLabel("Recieved rnd:");
    techACCLay->addWidget(lab);
    letechACCrnd = new QLineEdit();
    letechACCrnd->setValidator(new HexValidator(2, 1, letechACCrnd));
    letechACCrnd->setMaximumWidth(50);
    techACCLay->addWidget(letechACCrnd);

    QHBoxLayout* techRSTLay = new QHBoxLayout();
    mainLay->addLayout(techRSTLay);
    pb = new QPushButton("techRESET");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRESET(), 3);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techRSTLay->addWidget(pb);
    techRSTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* techRDSECTIONLay = new QHBoxLayout();
    mainLay->addLayout(techRDSECTIONLay);
    pb = new QPushButton("techRDSECTION");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRDSECTION(sbtechRDSECTION->value()), 3);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techRDSECTIONLay->addWidget(pb);
    techRDSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Nr:");
    techRDSECTIONLay->addWidget(lab);
    sbtechRDSECTION = new QSpinBox();
    sbtechRDSECTION->setMaximum(0x3F);
    sbtechRDSECTION->setMinimum(0);
    techRDSECTIONLay->addWidget(sbtechRDSECTION);

    QHBoxLayout* techWRSECTIONLay = new QHBoxLayout();
    mainLay->addLayout(techWRSECTIONLay);
    pb = new QPushButton("wiWRSECTION(dev)");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessageZR3::techWRSECTION(sbtechWRSECTION->value(),
                    letechWRSECTIONmagic->text().toInt(nullptr, 16),
                    SU::string2ByteArray(letechWRSECTION->text())), 3);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techWRSECTIONLay->addWidget(pb);
    techWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Magic:");
    techWRSECTIONLay->addWidget(lab);
    letechWRSECTIONmagic = new QLineEdit();
    letechWRSECTIONmagic->setValidator(new HexValidator(2, 1, letechWRSECTIONmagic));
    letechWRSECTIONmagic->setMaximumWidth(50);
    techWRSECTIONLay->addWidget(letechWRSECTIONmagic);
    lab = new QLabel("Nr:");
    techWRSECTIONLay->addWidget(lab);
    sbtechWRSECTION = new QSpinBox();
    sbtechWRSECTION->setMaximum(0x3F);
    sbtechWRSECTION->setMinimum(0);
    techWRSECTIONLay->addWidget(sbtechWRSECTION);
    letechWRSECTION = new QLineEdit("fe");
    letechWRSECTION->setValidator(new HexValidator(1, 0, letechWRSECTION));
    mainLay->addWidget(letechWRSECTION);
}

void IF11ZR3::Init()
{
    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void IF11ZR3::internalFrameReaded(QSharedPointer<Frame> fr)
{
    IFPanel::internalFrameReaded(fr);
    if(!(*fr).isValid())
        return;
    if(((*fr).pureData().at(0)&0x3F)!=(leToAdr->text().toInt(nullptr, 16)&0x3F))
        return;
    FramePazur paz(fr->pureData());
    for(auto msg: paz.getMessages().getMessages())
    {
        if(msg.toPureData().at(2)==0x01)
        {
            letechACCrnd->setText(QString("%1%2").arg((uint)msg.toPureData().at(4)&0xFF, 2, 16, QChar('0'))
                                  .arg((uint)msg.toPureData().at(3)&0xFF, 2, 16, QChar('0')).toUpper());
            return;
        }
    }
}

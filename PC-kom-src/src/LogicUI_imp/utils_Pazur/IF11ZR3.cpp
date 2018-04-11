#include "IF11ZR3.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessageZR3.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"
#include <qdebug.h>
#include "Frame_imp/FramePazur.hpp"

IF11ZR3::IF11ZR3(QFrame* parent):
    Restorable("IF11ZR3"),
    cParent(parent)
{
    Init();
}

IF11ZR3::~IF11ZR3()
{
    Store("leToAdr", leToAdr->text());
    Store("letechREQmagic", letechREQmagic->text());
    Store("letechACCmagic", letechACCmagic->text());
    Store("letechACCrnd", letechACCrnd->text());
    Store("sbtechRDSECTION", sbtechRDSECTION->value());
    Store("letechWRSECTIONmagic", letechWRSECTIONmagic->text());
    Store("letechWRSECTION", letechWRSECTION->text());
    Store("sbtechWRSECTION", sbtechWRSECTION->value());
}

void IF11ZR3::LoadConfigs()
{
    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
    letechREQmagic->setText(RestoreAsString("letechREQmagic", "1234"));
    letechACCmagic->setText(RestoreAsString("letechACCmagic", "1234"));
    letechACCrnd->setText(RestoreAsString("letechACCrnd", "1234"));
    sbtechRDSECTION->setValue(RestoreAsInt("sbtechRDSECTION", 0));
    letechWRSECTIONmagic->setText(RestoreAsString("letechWRSECTIONmagic", "1234"));
    letechWRSECTION->setText(RestoreAsString("letechWRSECTION", ""));
    sbtechWRSECTION->setValue(RestoreAsInt("sbtechWRSECTION", 0));
}

void IF11ZR3::InitRest()
{
    const uint MIN_PB_W = 150;

    QHBoxLayout* toAdrLay = new QHBoxLayout();
    mainLay->addLayout(toAdrLay);
    QLabel* lab = new QLabel("Adres docelowy:");
    toAdrLay->addWidget(lab);
    toAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leToAdr = new QLineEdit("FF");
    leToAdr->setInputMask("HH");
    leToAdr->setMaximumWidth(40);
    toAdrLay->addWidget(leToAdr);

    QHBoxLayout* techREQLay = new QHBoxLayout();
    mainLay->addLayout(techREQLay);
    QPushButton* pb = new QPushButton("techREQ");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techREQ(letechREQmagic->text().toInt(nullptr, 16)));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techREQLay->addWidget(pb);
    techREQLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Magic:");
    techREQLay->addWidget(lab);
    letechREQmagic = new QLineEdit();
    letechREQmagic->setValidator(new HexValidator(2, 1, letechREQmagic));
    letechREQmagic->setMaximumWidth(50);
    techREQLay->addWidget(letechREQmagic);

    QHBoxLayout* techACCLay = new QHBoxLayout();
    mainLay->addLayout(techACCLay);
    pb = new QPushButton("techACC");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(
                    PureMessageZR3::techACC(letechACCmagic->text().toInt(nullptr, 16), letechACCrnd->text().toInt(nullptr, 16)));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techACCLay->addWidget(pb);
    techACCLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Recieved rnd:");
    techACCLay->addWidget(lab);
    letechACCrnd = new QLineEdit();
    letechACCrnd->setValidator(new HexValidator(2, 1, letechACCrnd));
    letechACCrnd->setMaximumWidth(50);
    techACCLay->addWidget(letechACCrnd);
    lab = new QLabel("Magic:");
    techACCLay->addWidget(lab);
    letechACCmagic = new QLineEdit();
    letechACCmagic->setValidator(new HexValidator(2, 1, letechACCmagic));
    letechACCmagic->setMaximumWidth(50);
    techACCLay->addWidget(letechACCmagic);

    QHBoxLayout* techRSTLay = new QHBoxLayout();
    mainLay->addLayout(techRSTLay);
    pb = new QPushButton("techRESET");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRESET());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techRSTLay->addWidget(pb);
    techRSTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* techRDSECTIONLay = new QHBoxLayout();
    mainLay->addLayout(techRDSECTIONLay);
    pb = new QPushButton("techRDSECTION");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRDSECTION(sbtechRDSECTION->value()));});
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
                    SU::string2ByteArray(letechWRSECTION->text())));});
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
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void IF11ZR3::SendMessage(QByteArray arr)
{
    QList<Message> m;
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    m.append(Message(to, 3, arr));
    emit Send(QList<Confirm>(), m);
}

void IF11ZR3::internalFrameReaded(QSharedPointer<Frame> fr)
{
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

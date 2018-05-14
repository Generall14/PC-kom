#include "IF10ZR3s.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessageZR3.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"
#include <qdebug.h>
#include "Frame_imp/FramePazur.hpp"
#include <QGroupBox>

IF10ZR3s::IF10ZR3s(QFrame* parent):
    Restorable("IF10ZR3s"),
    cParent(parent)
{
    Init();
}

IF10ZR3s::~IF10ZR3s()
{
    Store("leToAdr", leToAdr->text());
//    Store("lezr3SetDose", lezr3SetDose->text());
    Store("dsbzr3SetDose", dsbzr3SetDose->value());
//    Store("letechREQmagic", letechREQmagic->text());
//    Store("letechACCmagic", letechACCmagic->text());
//    Store("letechACCrnd", letechACCrnd->text());
//    Store("sbtechRDSECTION", sbtechRDSECTION->value());
//    Store("letechWRSECTIONmagic", letechWRSECTIONmagic->text());
//    Store("letechWRSECTION", letechWRSECTION->text());
//    Store("sbtechWRSECTION", sbtechWRSECTION->value());
}

void IF10ZR3s::LoadConfigs()
{
    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
//    lezr3SetDose->setText(RestoreAsString("lezr3SetDose", ""));
    dsbzr3SetDose->setValue(RestoreAsFloat("dsbzr3SetDose", 0.0));
//    letechREQmagic->setText(RestoreAsString("letechREQmagic", "1234"));
//    letechACCmagic->setText(RestoreAsString("letechACCmagic", "1234"));
//    letechACCrnd->setText(RestoreAsString("letechACCrnd", "1234"));
//    sbtechRDSECTION->setValue(RestoreAsInt("sbtechRDSECTION", 0));
//    letechWRSECTIONmagic->setText(RestoreAsString("letechWRSECTIONmagic", "1234"));
//    letechWRSECTION->setText(RestoreAsString("letechWRSECTION", ""));
//    sbtechWRSECTION->setValue(RestoreAsInt("sbtechWRSECTION", 0));
}

void IF10ZR3s::InitRest()
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

    //=============================================================================================
    QGroupBox* mocDawki = new QGroupBox("Pomiar/szacowanie mocy dawki");
    mainLay->addWidget(mocDawki);
    QVBoxLayout* mdLay = new QVBoxLayout(mocDawki);
    mdLay->setMargin(2);

    QHBoxLayout* drRead = new QHBoxLayout();
    mdLay->addLayout(drRead);
    QPushButton* pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadDoseRate());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    drRead->addWidget(pb);
    drRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labDoseRate = new QLabel("-");
    drRead->addWidget(labDoseRate);

    QHBoxLayout* drProbeRead = new QHBoxLayout();
    mdLay->addLayout(drProbeRead);
    pb = new QPushButton("Próbka");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadDoseRateProbe());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    drProbeRead->addWidget(pb);
    drProbeRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labDoseRateProbe = new QLabel("-");
    drProbeRead->addWidget(labDoseRateProbe);

    //=============================================================================================
    QGroupBox* dawka = new QGroupBox("Pomiar/szacowanie dawki");
    mainLay->addWidget(dawka);
    QVBoxLayout* dLay = new QVBoxLayout(dawka);
    dLay->setMargin(2);

    QHBoxLayout* dRead = new QHBoxLayout();
    dLay->addLayout(dRead);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadDose());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    dRead->addWidget(pb);
    dRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labDose = new QLabel("-");
    dRead->addWidget(labDose);

    QHBoxLayout* dSet = new QHBoxLayout();
    dLay->addLayout(dSet);
    pb = new QPushButton("Ustaw");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetDose(dsbzr3SetDose->value()));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    dSet->addWidget(pb);
    dSet->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    dsbzr3SetDose = new QDoubleSpinBox();
    dSet->addWidget(dsbzr3SetDose);
    dsbzr3SetDose->setMaximumWidth(100);
    dsbzr3SetDose->setMinimumWidth(100);
    dsbzr3SetDose->setDecimals(12);



//    QHBoxLayout* techREQLay = new QHBoxLayout();
//    mainLay->addLayout(techREQLay);
//    QPushButton* pb = new QPushButton("techREQ");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techREQ(letechREQmagic->text().toInt(nullptr, 16)));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    techREQLay->addWidget(pb);
//    techREQLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Magic:");
//    techREQLay->addWidget(lab);
//    letechREQmagic = new QLineEdit();
//    letechREQmagic->setValidator(new HexValidator(2, 1, letechREQmagic));
//    letechREQmagic->setMaximumWidth(50);
//    techREQLay->addWidget(letechREQmagic);

//    QHBoxLayout* techACCLay = new QHBoxLayout();
//    mainLay->addLayout(techACCLay);
//    pb = new QPushButton("techACC");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(
//                    PureMessageZR3::techACC(letechACCmagic->text().toInt(nullptr, 16), letechACCrnd->text().toInt(nullptr, 16)));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    techACCLay->addWidget(pb);
//    techACCLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Recieved rnd:");
//    techACCLay->addWidget(lab);
//    letechACCrnd = new QLineEdit();
//    letechACCrnd->setValidator(new HexValidator(2, 1, letechACCrnd));
//    letechACCrnd->setMaximumWidth(50);
//    techACCLay->addWidget(letechACCrnd);
//    lab = new QLabel("Magic:");
//    techACCLay->addWidget(lab);
//    letechACCmagic = new QLineEdit();
//    letechACCmagic->setValidator(new HexValidator(2, 1, letechACCmagic));
//    letechACCmagic->setMaximumWidth(50);
//    techACCLay->addWidget(letechACCmagic);

//    QHBoxLayout* techRSTLay = new QHBoxLayout();
//    mainLay->addLayout(techRSTLay);
//    pb = new QPushButton("techRESET");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRESET());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    techRSTLay->addWidget(pb);
//    techRSTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

//    QHBoxLayout* techRDSECTIONLay = new QHBoxLayout();
//    mainLay->addLayout(techRDSECTIONLay);
//    pb = new QPushButton("techRDSECTION");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRDSECTION(sbtechRDSECTION->value()));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    techRDSECTIONLay->addWidget(pb);
//    techRDSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Nr:");
//    techRDSECTIONLay->addWidget(lab);
//    sbtechRDSECTION = new QSpinBox();
//    sbtechRDSECTION->setMaximum(0x3F);
//    sbtechRDSECTION->setMinimum(0);
//    techRDSECTIONLay->addWidget(sbtechRDSECTION);

//    QHBoxLayout* techWRSECTIONLay = new QHBoxLayout();
//    mainLay->addLayout(techWRSECTIONLay);
//    pb = new QPushButton("wiWRSECTION(dev)");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessageZR3::techWRSECTION(sbtechWRSECTION->value(),
//                    letechWRSECTIONmagic->text().toInt(nullptr, 16),
//                    SU::string2ByteArray(letechWRSECTION->text())));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    techWRSECTIONLay->addWidget(pb);
//    techWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Magic:");
//    techWRSECTIONLay->addWidget(lab);
//    letechWRSECTIONmagic = new QLineEdit();
//    letechWRSECTIONmagic->setValidator(new HexValidator(2, 1, letechWRSECTIONmagic));
//    letechWRSECTIONmagic->setMaximumWidth(50);
//    techWRSECTIONLay->addWidget(letechWRSECTIONmagic);
//    lab = new QLabel("Nr:");
//    techWRSECTIONLay->addWidget(lab);
//    sbtechWRSECTION = new QSpinBox();
//    sbtechWRSECTION->setMaximum(0x3F);
//    sbtechWRSECTION->setMinimum(0);
//    techWRSECTIONLay->addWidget(sbtechWRSECTION);
//    letechWRSECTION = new QLineEdit("fe");
//    letechWRSECTION->setValidator(new HexValidator(1, 0, letechWRSECTION));
//    mainLay->addWidget(letechWRSECTION);
}

void IF10ZR3s::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void IF10ZR3s::SendMessage(QByteArray arr)
{
    QList<Message> m;
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    m.append(Message(to, 2, arr));
    emit Send(QList<Confirm>(), m);
}

void IF10ZR3s::internalFrameReaded(QSharedPointer<Frame> fr)
{
    if(!(*fr).isValid())
        return;
    if(((*fr).pureData().at(0)&0x3F)!=(leToAdr->text().toInt(nullptr, 16)&0x3F))
        return;
    FramePazur paz(fr->pureData());
    for(auto msg: paz.getMessages().getMessages())
    {
        QByteArray mm = msg.toPureData().mid(2);
        if((mm.at(0)==0x20)&&(mm.at(1)==0x04))
        {
            if(mm.size()<11)
                return;
            labDose->setText(SU::displayFloat(SU::byteArray322Float32(mm.mid(2, 4)), 3)+"Sv");
        }
        else if((mm.at(0)==0x20)&&(mm.at(1)==0x02))
        {
            if(mm.size()<11)
                return;
            QString text = SU::displayFloat(SU::byteArray322Float32(mm.mid(2, 4)), 3)+"Sv/h";
            text.append(QString(" +%1\% -%2\%")
                        .arg(int(SU::byteArray2f5_11(mm.mid(6, 2))*100))
                        .arg(int(SU::byteArray2f5_11(mm.mid(8, 2))*100))
                        );
            if(mm.at(10)&0x01)
                text.append(" !DGZ!");
            if(mm.at(10)&0x02)
                text.append(" !GGZ!");
            labDoseRate->setText(text);
        }
        else if((mm.at(0)==0x70))
        {
            if(mm.size()<10)
                return;
            QString text = SU::displayFloat(SU::byteArray322Float32(mm.mid(1, 4)), 3)+"Sv/h";
            text.append(QString(" +%1\% -%2\%")
                        .arg(int(SU::byteArray2f5_11(mm.mid(5, 2))*100))
                        .arg(int(SU::byteArray2f5_11(mm.mid(7, 2))*100))
                        );
            if(mm.at(9)&0x01)
                text.append(" !DGZ!");
            if(mm.at(9)&0x02)
                text.append(" !GGZ!");
            labDoseRateProbe->setText(text);
        }
    }
}

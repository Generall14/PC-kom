#include "IF11ZR3.hpp"
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include "Frame_imp/utils_Pazur/PureMessageZR3.hpp"
#include "Frame_imp/utils_Pazur/PureMessage.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"
#include <qdebug.h>
#include "Frame_imp/FramePazur.hpp"
#include "IF11ZR3I2C.hpp"

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
    Store("letechWRSECTION", letechWRSECTION->text());
    Store("sbtechWRSECTION", sbtechWRSECTION->value());
    Store("letechWrId", letechWrId->text());
    Store("sbtechRLadd", sbtechRLadd->value());
}

void IF11ZR3::LoadConfigs()
{
    letechACCrnd->setText(RestoreAsString("letechACCrnd", "1234"));
    sbtechRDSECTION->setValue(RestoreAsInt("sbtechRDSECTION", 0));
    letechWRSECTION->setText(RestoreAsString("letechWRSECTION", ""));
    sbtechWRSECTION->setValue(RestoreAsInt("sbtechWRSECTION", 0));
    letechWrId->setText(RestoreAsString("letechWrId", "000000"));
    sbtechRLadd->setValue(RestoreAsInt("sbtechRLadd", 3));
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

    QHBoxLayout* techCALLLay = new QHBoxLayout();
    mainLay->addLayout(techCALLLay);
    pb = new QPushButton("techCALL");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techCALL(), 3);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techCALLLay->addWidget(pb);
    techCALLLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* techPALSYLay = new QHBoxLayout();
    mainLay->addLayout(techPALSYLay);
    pb = new QPushButton("techPALSY");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techPALSY(), 3);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techPALSYLay->addWidget(pb);
    techPALSYLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

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
                    leMagic->text().toInt(nullptr, 16),
                    SU::string2ByteArray(letechWRSECTION->text())), 3);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techWRSECTIONLay->addWidget(pb);
    techWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Nr:");
    techWRSECTIONLay->addWidget(lab);
    sbtechWRSECTION = new QSpinBox();
    sbtechWRSECTION->setMaximum(0x3F);
    sbtechWRSECTION->setMinimum(0);
    techWRSECTIONLay->addWidget(sbtechWRSECTION);
    letechWRSECTION = new QLineEdit("fe");
    letechWRSECTION->setValidator(new HexValidator(1, 0, letechWRSECTION));
    mainLay->addWidget(letechWRSECTION);

    QHBoxLayout* techRdsLay = new QHBoxLayout();
    mainLay->addLayout(techRdsLay);
    pb = new QPushButton("Rd ver.");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRdVer(), 3);
                                                this->labWer->setText("?");});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    techRdsLay->addWidget(pb);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("Rd date.");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRdDate(), 3);
                                                this->labBuild->setText("?");});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    techRdsLay->addWidget(pb);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("Rd prog. s.");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRdFRAMFails(), 3);});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    techRdsLay->addWidget(pb);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("Rd dev. s.");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRdFRAMDevStats(), 3);
                                                labMDRate->setText("?");
                                                labTDose->setText("?");
                                                labTOn->setText("?");
                                                labLoc->setText("?");
                                                labVDown->setText("?");
                                                labStarts->setText("?");
                                                labMUdr->setText("?");
                                                labUdr->setText("?");});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    techRdsLay->addWidget(pb);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("Rd DevId");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techRdDevId(), 3);
                                                this->labDevId->setText("?");});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    techRdsLay->addWidget(pb);

    QHBoxLayout* labsLay = new QHBoxLayout();
    mainLay->addLayout(labsLay);
    lab = new QLabel("Wersja: ");
    labsLay->addWidget(lab);
    labWer = new QLabel("?");
    labsLay->addWidget(labWer);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Build: ");
    labsLay->addWidget(lab);
    labBuild = new QLabel("?");
    labsLay->addWidget(labBuild);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("DevId: ");
    labsLay->addWidget(lab);
    labDevId = new QLabel("?");
    labsLay->addWidget(labDevId);

    QHBoxLayout* labs2Lay = new QHBoxLayout();
    mainLay->addLayout(labs2Lay);
    lab = new QLabel("Uruchomienia: ");
    labs2Lay->addWidget(lab);
    labStarts = new QLabel("?");
    labs2Lay->addWidget(labStarts);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Zaniki napięcia: ");
    labs2Lay->addWidget(lab);
    labVDown = new QLabel("?");
    labs2Lay->addWidget(labVDown);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Czas działania [sek]: ");
    labs2Lay->addWidget(lab);
    labTOn = new QLabel("?");
    labs2Lay->addWidget(labTOn);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Dawka: ");
    labs2Lay->addWidget(lab);
    labTDose = new QLabel("?");
    labs2Lay->addWidget(labTDose);

    QHBoxLayout* labs3Lay = new QHBoxLayout();
    mainLay->addLayout(labs3Lay);
    lab = new QLabel("Maks. moc dawki: ");
    labs3Lay->addWidget(lab);
    labMDRate = new QLabel("?");
    labs3Lay->addWidget(labMDRate);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Maks. udar: ");
    labs3Lay->addWidget(lab);
    labMUdr = new QLabel("?");
    labs3Lay->addWidget(labMUdr);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Liczba udarów: ");
    labs3Lay->addWidget(lab);
    labUdr = new QLabel("?");
    labs3Lay->addWidget(labUdr);
    techRdsLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Czas lokalny [sek]: ");
    labs3Lay->addWidget(lab);
    labLoc = new QLabel("?");
    labs3Lay->addWidget(labLoc);


    QHBoxLayout* wrIdLay = new QHBoxLayout();
    mainLay->addLayout(wrIdLay);
    pb = new QPushButton("Zapisz");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techWrDevId(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                letechWrId->text().toInt(nullptr, 16)), 3);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wrIdLay->addWidget(pb);
    lab = new QLabel("DevId:");
    wrIdLay->addWidget(lab);
    letechWrId = new QLineEdit("000000");
    letechWrId->setInputMask("HHHHHH");
    letechWrId->setMaximumWidth(70);
    wrIdLay->addWidget(letechWrId);

    //=====================================================

    uint specs = MIN_PB_W/2;

    QGroupBox* gb = new QGroupBox("Detektor udaru");
    mainLay->addWidget(gb);
    QHBoxLayout* hl = new QHBoxLayout();
    gb->setLayout(hl);
    pb = new QPushButton("Zapisz");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessageZR3::techWrRLadd(
                        leMagic->text().toInt(nullptr, 16),
                        sbtechRLadd->value()
                        ), 3);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
    sbtechRLadd = new QSpinBox();
    sbtechRLadd->setMinimum(0);
    sbtechRLadd->setMaximum(0x1F);
    hl->addWidget(sbtechRLadd);
    hl->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labRLadd = new QLabel("?");
    labRLadd->setAlignment(Qt::AlignRight);
    hl->addWidget(labRLadd);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){
                        SendMessage(PureMessageZR3::techRdRLadd(), 3);
                        labRLadd->setText("?");});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
}

void IF11ZR3::Init()
{
    InitRest();
    InitI2CTabs();

    LoadConfigs();
}

void IF11ZR3::InitI2CTabs()
{
    QHBoxLayout* wthLay = new QHBoxLayout();
    mainLay->addLayout(wthLay);
    QPushButton* pb = new QPushButton("rdFLAGS");
    connect(pb, &QPushButton::clicked, [this](){
                        SendMessage(PureMessageZR3::techRDSECTION(6), 3);});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    wthLay->addWidget(pb);
    for(int i=1;i<=8;i++)
    {
        QCheckBox* cb = new QCheckBox("en"+QString::number(i));
        wthLay->addWidget(cb);
        wthFlags.append(cb);
    }
    pb = new QPushButton("wrFLAGS");
    connect(pb, &QPushButton::clicked, [this](){
        uchar tt = 0x00;
        for(int i=0;i<8;i++)
            tt |= wthFlags.at(i)->isChecked()?(0x01<<i):(0x00);
        QByteArray temp; temp.append(tt);
        SendMessage(PureMessageZR3::techWRSECTION(6,
                    leMagic->text().toInt(nullptr, 16),
                    temp), 3);});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    wthLay->addWidget(pb);

    QTabWidget* tw = new QTabWidget();
    tw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLay->addWidget(tw);

    for(int i=0;i<=8;++i)
    {
        QFrame* fr = new QFrame();
        IF11ZR3I2c* iic = new IF11ZR3I2c(fr, i);
        connect(this, SIGNAL(internalFrameResend(QSharedPointer<Frame>)), iic, SLOT(internalFrameReaded(QSharedPointer<Frame>)));
        connect(iic, &IF11ZR3I2c::send, [this](QByteArray arr){emit SendMessage(arr, 3);});
        tw->addTab(fr, QString::number(i));
    }
}

void IF11ZR3::internalFrameReaded(QSharedPointer<Frame> fr)
{
    IFPanel::internalFrameReaded(fr);
    if(!(*fr).isValid())
        return;
    if(((*fr).pureData().at(0)&0x3F)!=(leToAdr->text().toInt(nullptr, 16)&0x3F))
        return;

    emit internalFrameResend(fr);

    FramePazur paz(fr->pureData());
    for(auto msg: paz.getMessages().getMessages())
    {
        if((msg.toPureData().at(0)&0xC0)==0xC0) // ifs = 3
        {
            QByteArray mm = msg.toPureData().mid(2);
            if(mm.size()<1)
                return;
            if(mm.at(0)==0x01)
            {
                if(mm.size()<3)
                    return;
                letechACCrnd->setText(QString("%1%2").arg((uint)mm.at(2)&0xFF, 2, 16, QChar('0'))
                                      .arg((uint)mm.at(1)&0xFF, 2, 16, QChar('0')).toUpper());
                return;
            }
            else if((mm.at(0)&0x3F)==0x3E) // RDo
            {
                if(mm.size()<3)
                    return;
                uchar nr = mm.at(1);
                mm = mm.mid(2);
                switch(nr)
                {
                case 0x00:
                {
                    if(mm.size()<2)
                        return;
                    uint ver = 0;
                    ver |= mm.at(0)&0xFF;
                    ver |= (mm.at(1)<<8)&0xFF00;
                    labWer->setText(QString("0x%1").arg(ver&0xFFFF, 4, 16, QChar('0')));
                    break;
                }
                case 0x01:
                    labBuild->setText(mm);
                    break;
                case 0x03:
                {
                    if(mm.size()<3)
                        return;
                    uint ver = 0;
                    ver |= mm.at(0)&0xFF;
                    ver |= (mm.at(1)<<8)&0xFF00;
                    ver |= (mm.at(2)<<16)&0xFF0000;
                    labDevId->setText(QString("0x%1").arg(ver&0xFFFFFF, 6, 16, QChar('0')));
                    break;
                }
                case 0x04:
                {
                    if(mm.size()<24)
                        return;
                    uint ver = 0;
                    ver |= mm.at(0)&0xFF;
                    ver |= (mm.at(1)<<8)&0xFF00;
                    labStarts->setText(QString::number(ver));
                    ver = 0;
                    ver |= mm.at(2)&0xFF;
                    ver |= (mm.at(3)<<8)&0xFF00;
                    labVDown->setText(QString::number(ver));
                    ver = 0;
                    ver |= mm.at(4)&0xFF;
                    ver |= (mm.at(5)<<8)&0xFF00;
                    ver |= (mm.at(6)<<16)&0xFF0000;
                    ver |= (mm.at(7)<<24)&0xFF000000;
                    labTOn->setText(QString::number(ver));
                    labTDose->setText(SU::displayFloat(float(SU::byteArray2Int64le(mm.mid(8, 8)))*1e-15, 2, 'f')+"Sv");
                    labMDRate->setText(SU::displayFloat(SU::byteArray322Float32(mm.mid(16, 4)), 2, 'f')+"Sv/h");
                    ver = 0;
                    ver |= mm.at(20)&0xFF;
                    ver |= (mm.at(21)<<8)&0xFF00;
                    labMUdr->setText(QString::number(ver));
                    ver = 0;
                    ver |= mm.at(22)&0xFF;
                    ver |= (mm.at(23)<<8)&0xFF00;
                    labUdr->setText(QString::number(ver));
                    ver = 0;
                    ver |= mm.at(24)&0xFF;
                    ver |= (mm.at(25)<<8)&0xFF00;
                    labLoc->setText(QString::number(ver));
                    break;
                }
                case 0x05:
                    labRLadd->setText(QString::number(mm.at(0)));
                    break;
                case 0x06:
                    for(int i=0;i<6;i++)
                        wthFlags[i]->setChecked(mm.at(0)&(0x01<<i));
                    break;
                default:
                    break;
                }
            }
        }

    }
}

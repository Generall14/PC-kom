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
#include "src/Utils/DisplayMes.hpp"
#include "src/Frame_imp/utils_Pazur/Quantile.hpp"
#include "src/Frame_imp/utils_Pazur/PureMessageZR3IIC.hpp"

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
                    labBuild->setText("?");});
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
    pb = new QPushButton("rdCLK");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(6)));
                    labRCLK->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay2->addWidget(pb);
    smLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rdOffset");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(18)));
                    labOffset->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay2->addWidget(pb);

    QHBoxLayout* smLay3 = new QHBoxLayout();
    mainLay->addLayout(smLay3);
    pb = new QPushButton("rdZero");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(19)));
                    labZero->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay3->addWidget(pb);
    smLay3->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rdCurrent");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRDSECTION(20)));
                    labCurrent->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay3->addWidget(pb);
    smLay3->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rdHist");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveGET_HIST()));
                    labHIST->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay3->addWidget(pb);
    smLay3->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    pb = new QPushButton("rstHist");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveRST_HIST()));
                    labHIST->setText("?");});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    smLay3->addWidget(pb);

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
    lab = new QLabel("Offset: ");
    labsLay2->addWidget(lab);
    labOffset = new QLabel("?");
    labsLay2->addWidget(labOffset);
    labsLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Zero: ");
    labsLay2->addWidget(lab);
    labZero = new QLabel("?");
    labsLay2->addWidget(labZero);
    labsLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Current: ");
    labsLay2->addWidget(lab);
    labCurrent = new QLabel("?");
    labsLay2->addWidget(labCurrent);

    QHBoxLayout* labsLay3 = new QHBoxLayout();
    mainLay->addLayout(labsLay3);
    lab = new QLabel("hist: ");
    labsLay3->addWidget(lab);
    labHIST = new QLabel("?");
    labsLay3->addWidget(labHIST);
    labsLay3->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Offset: ");
//    labsLay3->addWidget(lab);
//    labOffset = new QLabel("?");
//    labsLay3->addWidget(labOffset);

    QHBoxLayout* callLay = new QHBoxLayout();
    mainLay->addLayout(callLay);
    pb = new QPushButton("Call");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveCALL()));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    callLay->addWidget(pb);
    pb = new QPushButton("Palsy");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slavePALSY()));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    callLay->addWidget(pb);
    pb = new QPushButton("MES_RST_UP");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveMES_RST(0x1234)));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    callLay->addWidget(pb);
    pb = new QPushButton("MES_RST_DOWN");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                    PureMessageZR3IIC::slaveMES_RST(-1)));});
    pb->setMaximumWidth(smallMIN_PB_W);
    pb->setMinimumWidth(smallMIN_PB_W);
    callLay->addWidget(pb);
    callLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QFrame* ffr = new QFrame();
    mainLay->addWidget(ffr);
    disp = new DisplayMes(ffr);

    QHBoxLayout* techRDSECTIONLay = new QHBoxLayout();
    mainLay->addLayout(techRDSECTIONLay);
    pb = new QPushButton("RDSECTION");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr, PureMessageZR3IIC::slaveRDSECTION(
                                                                                   sbtechRDSECTION->value())));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techRDSECTIONLay->addWidget(pb);
    pb = new QPushButton("wiWRSECTION(dev)");
    connect(pb, &QPushButton::clicked, [this](){send(PureMessageZR3::techWRIIC(_adr,
                                                                               PureMessageZR3IIC::slaveWRSECTION(
                                                                                   sbtechRDSECTION->value(),
                                                                                   SU::string2ByteArray(letechWRSECTION->text())
                                                                                   )));});
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

    techWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    letechWRSECTION = new QLineEdit("fe");
    letechWRSECTION->setValidator(new HexValidator(1, 0, letechWRSECTION));
    mainLay->addWidget(letechWRSECTION);
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
                case 6:
                {
                    uint ver = 0;
                    ver |= iicd.at(1)&0xFF;
                    ver |= (iicd.at(2)<<8)&0xFF00;
                    labRCLK->setText(QString::number(float(ver)/32));
                    break;
                }
                case 18:
                {
                    int off = 0;
                    off |= iicd.at(1)&0xFF;
                    off |= (iicd.at(2)<<8)&0xFF00;
                    off &= 0x3FF;
                    float val = float(off)*1.5/0x3FF;
                    if(off&0x200)
                        val = val - 1.5;
                    labOffset->setText("0x"+QString::number(off, 16)+"/" + QString::number(val)+" V");
                    break;
                }
                case 19:
                {
                    int off = 0;
                    off |= iicd.at(1)&0xFF;
                    off |= (iicd.at(2)<<8)&0xFF00;
                    off &= 0x3FF;
                    float val = float(off)*1.5/0x3FF;
                    labZero->setText(QString::number(val)+" V");
                    break;
                }
                case 20:
                {
                    int off = 0;
                    off |= iicd.at(1)&0xFF;
                    off |= (iicd.at(2)<<8)&0xFF00;
                    off /= 16;
                    off &= 0x3FF;
                    float val = float(off)*1.5/0x3FF;
                    labCurrent->setText(QString::number(val)+" V");
                    break;
                }
                default:
                    break;
                }
            }
            else if(code==PureMessageZR3IIC::masterHIST_c)
            {
                if(iicd.size()<10)
                    break;
                QString temp = QString("hist|||");
                for(int u=0;u<5;++u)
                {
                    uint v = 0;
                    v |= iicd.at(0)&0xFF;
                    v |= (iicd.at(1)<<8)&0xFF00;
                    temp += " " + QString::number((float(v))/256.0, 'f', 2) + " |";
                    iicd = iicd.mid(2);
                }
                temp += "||";
                labHIST->setText(temp);
                break;
            }
            else if(code==0x84)
            {
                float wpri = SU::byteArray322Float32(iicd.mid(0, 4));
                uint nr = 0;
                nr |= iicd.at(16)&0xFF;
                nr |= (iicd.at(17)<<8)&0xFF00;
                disp->feed(wpri, nr, wpri*Quantile::getLow(nr), wpri*Quantile::getHigh(nr), "Sv/h");

                QFile lastFile("vals.txt");
                if(lastFile.open(QIODevice::Append | QIODevice::Text | QIODevice::WriteOnly))
                {
                    QTextStream out(&lastFile);
                    out << SU::displayFloat(wpri, 2, 'f') << "Sv/h\tNr: " << QString::number(nr);
                    if(iicd.at(18)||iicd.at(19))
                        out << "\t" << PureMessageZR3IIC::getWho(iicd.at(18), QString::number(_adr)+" Rise")
                            << PureMessageZR3IIC::getWho(iicd.at(19), QString::number(_adr)+" Fall");
                    out << "\n";
                    lastFile.close();
                }
            }
        }
    }
}

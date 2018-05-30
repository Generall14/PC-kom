#include "IF_panel.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessage.hpp"

IFPanel::IFPanel(QFrame* parent, QString rname):
    cParent(parent)
{
    InitBase();

    rst = new Restorable(rname);

    leToAdr->setText(rst->RestoreAsString("leToAdr", "FF"));
    leMagic->setText(rst->RestoreAsString("leMagic", "0000"));
}

IFPanel::~IFPanel()
{
    rst->Store("leToAdr", leToAdr->text());
    rst->Store("leMagic", leMagic->text());
    delete rst;
}

void IFPanel::InitBase()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    QHBoxLayout* toAdrLay = new QHBoxLayout();
    mainLay->addLayout(toAdrLay);
    QLabel* lab = new QLabel("Magic:");
    toAdrLay->addWidget(lab);
    leMagic = new QLineEdit("0000");
    leMagic->setInputMask("HHHH");
    leMagic->setMaximumWidth(40);
    toAdrLay->addWidget(leMagic);
    QPushButton* pb = new QPushButton("Oblicz");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wiRDCONST(0), 1);});
    pb->setMaximumWidth(MIN_PB_W/3);
    pb->setMinimumWidth(MIN_PB_W/3);
    toAdrLay->addWidget(pb);

    toAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Adres docelowy:");
    toAdrLay->addWidget(lab);
    leToAdr = new QLineEdit("FF");
    leToAdr->setInputMask("HH");
    leToAdr->setMaximumWidth(40);
    toAdrLay->addWidget(leToAdr);
}

//void IF00::LoadConfigs()
//{
//    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
//    leConnO->setText(RestoreAsString("leConnO", "FF"));
//}

//void IF00::InitRest()
//{


//    QHBoxLayout* toAdrLay = new QHBoxLayout();
//    mainLay->addLayout(toAdrLay);
//    QLabel* lab = new QLabel("Adres docelowy:");
//    toAdrLay->addWidget(lab);
//    toAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    leToAdr = new QLineEdit("FF");
//    leToAdr->setInputMask("HH");
//    leToAdr->setMaximumWidth(40);
//    toAdrLay->addWidget(leToAdr);

//    QHBoxLayout* wkpSTORELay = new QHBoxLayout();
//    mainLay->addLayout(wkpSTORELay);
//    QPushButton* pb = new QPushButton("wkpSTORE");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpSTORE());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpSTORELay->addWidget(pb);
//    wkpSTORELay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

//    QHBoxLayout* wkpCONNECTLay = new QHBoxLayout();
//    mainLay->addLayout(wkpCONNECTLay);
//    pb = new QPushButton("wkpCONNECT");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpCONNECT());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpCONNECTLay->addWidget(pb);
//    wkpCONNECTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

//    QHBoxLayout* wkpCONNECToLay = new QHBoxLayout();
//    mainLay->addLayout(wkpCONNECToLay);
//    pb = new QPushButton("wkpCONNECTo");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpCONNECTo(SU::string2ByteArray(leConnO->text())));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpCONNECToLay->addWidget(pb);
//    wkpCONNECToLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Następnik:");
//    wkpCONNECToLay->addWidget(lab);
//    leConnO = new QLineEdit("FF");
//    leConnO->setInputMask("HH");
//    leConnO->setMaximumWidth(40);
//    wkpCONNECToLay->addWidget(leConnO);

//    QHBoxLayout* wkpBUILDLay = new QHBoxLayout();
//    mainLay->addLayout(wkpBUILDLay);
//    pb = new QPushButton("wkpBUILD");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpBUILD());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpBUILDLay->addWidget(pb);
//    wkpBUILDLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

//    QHBoxLayout* wkpBUILDoLay = new QHBoxLayout();
//    mainLay->addLayout(wkpBUILDoLay);
//    pb = new QPushButton("wkpBUILDo");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpBUILDo());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpBUILDoLay->addWidget(pb);
//    wkpBUILDoLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

//    QHBoxLayout* wkpRESETLay = new QHBoxLayout();
//    mainLay->addLayout(wkpRESETLay);
//    pb = new QPushButton("wkpRESET");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpRESET());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpRESETLay->addWidget(pb);
//    wkpRESETLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//}

//void IF00::Init()
//{
//    mainLay = new QVBoxLayout(cParent);
//    mainLay->setMargin(2);

//    InitRest();

//    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

//    LoadConfigs();
//}

void IFPanel::SendMessage(QByteArray arr, uint ifs)
{
    QList<Message> m;
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    m.append(Message(to, ifs, arr));
    emit Send(QList<Confirm>(), m);
}

void IFPanel::internalFrameReaded(QSharedPointer<Frame> fr)
{
    if(!(*fr).isValid())
        return;
    if(((*fr).pureData().at(0)&0x3F)!=(leToAdr->text().toInt(nullptr, 16)&0x3F))
        return;

    FramePazur paz(fr->pureData());
    for(auto msg: paz.getMessages().getMessages())
    {
        if((msg.toPureData().at(0)&0xC0)==0x40) // ifs = 1
        {
            QByteArray mm = msg.toPureData().mid(2);
            if(mm.isEmpty())
                return;
            if(mm.at(0)==PureMessage::wiRDCONSTo_c)
            {
                if(mm.size()<14)
                    return;
                leMagic->setText(QString("%1").arg(PureMessage::calcMagicNumber(mm.mid(3)), 4, 16, QChar('0')));
            }
        }
    }
}

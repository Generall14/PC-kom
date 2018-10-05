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

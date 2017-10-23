#include "ZR3UIFrame.hpp"
#include <QLayout>
#include <QLabel>
#include <QInputDialog>
#include <QDebug>
#include "../../Frame_imp/FrameZR3.hpp"
#include "../../Factory.hpp"

ZR3UIFrame::ZR3UIFrame(QFrame* parent, uchar adr):
    QObject(parent),
    cFrame(parent),
    _adr(adr)
{
    protHELLO.append(0xFF);
    protHELLO.append(0x01);
    protHELLO.append(_adr);
    protHELLO.append(_myAdr);
    protHELLO.append((char)0x00);
    FrameZR3::AppendLRC(protHELLO);
}

void ZR3UIFrame::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cFrame);
    mainLay->setMargin(1);

    QTabWidget* qtw = new QTabWidget();
    qtw->setTabPosition(QTabWidget::South);
    mainLay->addWidget(qtw);

    dbgFrame = new QFrame();
    qtw->addTab(dbgFrame, "Debug");

    suiFrame = new QFrame();
    qtw->addTab(suiFrame, "Simple UI");

    InitDebug();
}

void ZR3UIFrame::InitDebug()
{
    QVBoxLayout* mainLay = new QVBoxLayout(dbgFrame);
    mainLay->setMargin(6);


    QLabel* lbl1 = new QLabel("Warstwa protokołu");
    lbl1->setAlignment(Qt::AlignCenter);
    mainLay->addWidget(lbl1);

    QHBoxLayout* Lay1 = new QHBoxLayout();
    mainLay->addLayout(Lay1);

    QPushButton* btnHello = new QPushButton("HELLO");
    connect(btnHello, &QPushButton::clicked, [=](){emit FrameToMendium(QSharedPointer<Frame>(Factory::newFrame(protHELLO)));});
    Lay1->addWidget(btnHello);

    Lay1->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QPushButton* btnSetAdr = new QPushButton("SET_ADR");
    Lay1->addWidget(btnSetAdr);
    connect(btnSetAdr, SIGNAL(clicked(bool)), this, SLOT(protSET_ADR()));

    Lay1->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QPushButton* btnSetNextAdr = new QPushButton("SET_NEXT_ADR");
    Lay1->addWidget(btnSetNextAdr);
    connect(btnSetNextAdr, SIGNAL(clicked(bool)), this, SLOT(protSET_NEXT_ADR()));

    lbl1 = new QLabel("Warstwa aplikacji");
    lbl1->setAlignment(Qt::AlignCenter);
    mainLay->addWidget(lbl1);

    QHBoxLayout* Lay2 = new QHBoxLayout();
    mainLay->addLayout(Lay2);

    cbFreadFile = new QComboBox();
    cbFreadFile->addItems(readList);
    Lay2->addWidget(cbFreadFile);

    sboffset = new QSpinBox(cFrame);
    sboffset->setMinimum(0);
    sboffset->setMaximum(0xFFFF);
    Lay2->addWidget(sboffset);

    sbSize = new QSpinBox(cFrame);
    sbSize->setMinimum(0);
    sbSize->setMaximum(0xFF);
    Lay2->addWidget(sbSize);

    QPushButton* btnReadReq = new QPushButton("read req");
    Lay2->addWidget(btnReadReq);
    connect(btnReadReq, SIGNAL(clicked(bool)), this, SLOT(aplReadReq()));

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void ZR3UIFrame::protSET_ADR()
{
    QString astring = QString::number(_adr, 16);
    while(astring.length()<2)
        astring.insert(0, '0');

    bool ok;
    QString text = QInputDialog::getText(cFrame, "Podaj adres", "Adres:", QLineEdit::Normal, astring, &ok);

    if(!ok)
        return;

    text = text.left(2);
    char nadr = text.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane adresu \""+text+"\".");
        return;
    }

    QByteArray temp;
    temp.append(0xFF);
    temp.append(0x02);
    temp.append(_adr);
    temp.append(_myAdr);
    temp.append((char)0x01);
    temp.append(nadr);
    FrameZR3::AppendLRC(temp);
    emit FrameToMendium(QSharedPointer<Frame>(Factory::newFrame(temp)));
    emit AdresChanged(nadr);
    _adr = nadr;
}

void ZR3UIFrame::protSET_NEXT_ADR()
{
    bool ok;
    QString text = QInputDialog::getText(cFrame, "Podaj adres", "Adres:", QLineEdit::Normal, "FE", &ok);

    if(!ok)
        return;

    text = text.left(2);
    char nadr = text.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane adresu \""+text+"\".");
        return;
    }

    QByteArray temp;
    temp.append(0xFF);
    temp.append(0x03);
    temp.append(_adr);
    temp.append(_myAdr);
    temp.append((char)0x01);
    temp.append(nadr);
    FrameZR3::AppendLRC(temp);
    emit FrameToMendium(QSharedPointer<Frame>(Factory::newFrame(temp)));
}

void ZR3UIFrame::aplReadReq()
{
    QByteArray temp;
    temp.append(_adr);
    if(!cbFreadFile->currentText().compare("aplStringListDescriptor"))
        temp.append(QChar(0x0A));

    temp.append((sboffset->value()>>8)&0xFF);
    temp.append((sboffset->value()>>0)&0xFF);
    temp.append((sbSize->value()>>0)&0xFF);
    emit PureDataToMedium(temp);
}

void ZR3UIFrame::FrameToUI(QSharedPointer<Frame> frame)
{

}

uchar ZR3UIFrame::Adr() const
{
    return _adr;
}

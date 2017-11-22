#include "ZR3UIFrame.hpp"
#include <QLayout>
#include <QLabel>
#include <QInputDialog>
#include <QDebug>
#include <QHeaderView>
#include <QGroupBox>
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


    // String list
    QHBoxLayout* Lay3 = new QHBoxLayout();
    mainLay->addLayout(Lay3);

    QPushButton* btnReadString = new QPushButton("Read Strings");
    connect(btnReadString, &QPushButton::clicked, [=](){InitZR3ReadFile(0x0A);});
    Lay3->addWidget(btnReadString);

    sltw = new QTableWidget();
    mainLay->addWidget(sltw);
    sltw->horizontalHeader()->setVisible(false);
    sltw->verticalHeader()->setVisible(false);
    sltw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sltw->setSelectionMode(QAbstractItemView::SingleSelection);
    sltw->setSelectionBehavior(QAbstractItemView::SelectRows);
    sltw->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    sltw->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    sltw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Device descriptor
    QPushButton* btnReadDevDesc = new QPushButton("Read DevDesc");
    connect(btnReadDevDesc, &QPushButton::clicked, [=](){InitZR3ReadFile(0x01);});
    Lay3->addWidget(btnReadDevDesc);

    QGroupBox* devFrame = new QGroupBox("DeviceDescriptor");
    mainLay->addWidget(devFrame);
    QVBoxLayout* devL = new QVBoxLayout();
    devFrame->setLayout(devL);

    QHBoxLayout* devL1 = new QHBoxLayout();
    devL->addLayout(devL1);
    QLabel* dd1 = new QLabel("Wersja programu: ");
    devL1->addWidget(dd1);
    vProg = new QLabel("XX");
    devL1->addWidget(vProg);
    dd1 = new QLabel(" prot. publicznego: ");
    devL1->addWidget(dd1);
    vPub = new QLabel("XX");
    devL1->addWidget(vPub);
    dd1 = new QLabel(" prot. prywatnego: ");
    devL1->addWidget(dd1);
    vPriv = new QLabel("XX");
    devL1->addWidget(vPriv);

    QHBoxLayout* devL2 = new QHBoxLayout();
    devL->addLayout(devL2);
    prod = new QLabel("--------");
    prod->setToolTip("Producent");
    devL2->addWidget(prod);
    ser = new QLabel("--------");
    ser->setToolTip("Numer seryjny");
    devL2->addWidget(ser);
    name = new QLabel("--------");
    name->setToolTip("Nazwa urządzenia");
    devL2->addWidget(name);

    tooltip = new QLineEdit("--------");
    tooltip->setToolTip("Tooltip urządzenia");
    tooltip->setReadOnly(true);
    devL->addWidget(tooltip);
    opis = new QLineEdit("--------");
    opis->setToolTip("Opis urządzenia");
    opis->setReadOnly(true);
    devL->addWidget(opis);

    classList = new QComboBox();
    classList->setToolTip("Lista implementowanych klas");
    devL->addWidget(classList);

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Maximum, QSizePolicy::Maximum));
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

void ZR3UIFrame::InitZR3ReadFile(uchar header)
{
    if(rfile!=NULL)
        return;
    rfile = new ZR3ReadFile(header);
    connect(rfile, &ZR3ReadFile::SendDataFrame, [=](QByteArray ba){ba.insert(0, _adr);emit PureDataToMedium(ba);});
    connect(rfile, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    connect(rfile, SIGNAL(Done(uchar,QByteArray)), this, SLOT(FinalizeZR3ReadFile(uchar,QByteArray)));
    connect(this, SIGNAL(InternalDataReaded(QByteArray)), rfile, SLOT(RecievedData(QByteArray)), Qt::QueuedConnection);
    rfile->start(QThread::NormalPriority);
}

void ZR3UIFrame::FinalizeZR3ReadFile(uchar _header, QByteArray arr)
{
    rfile = NULL;
    if(arr.isEmpty())
        return;
    if(_header==0x0A)
    {
        strings = arr;
        ParseStrings();
    }
    else if(_header==0x01)
    {
        qDebug() << arr;
    }
}

void ZR3UIFrame::ParseStrings()
{
    stringi.clear();
    QList<uint16_t> ptrs;
    int lasti = -3;
    while(1)
    {
        if((strings.at(lasti+3)==QChar(0x00)))
            break;
        int ti = strings.indexOf(char(0x00), lasti+3);
        if(ti<=0)
            break;
        stringi.push_back(QStringList());
        stringi[stringi.size()-1].push_back(QString(strings.mid(lasti+3, ti-lasti+3)));
        uint16_t tt = 0;
        tt = (strings.at(ti+1)<<8)&0xFF00;
        tt |= strings.at(ti+2)&0xFF;
        ptrs.push_back(tt);
        lasti = ti;
    }
    for(int i=0;i<ptrs.size();++i)
    {
        if(i+1==ptrs.size())
        {
            for(QByteArray la: strings.mid(ptrs.at(i)).split(0x00))
            {
                if(!la.isEmpty())
                    stringi[i].append(QString(la));
            }
        }
        else
        {
            for(QByteArray la: strings.mid(ptrs.at(i), ptrs.at(i+1)-ptrs.at(i)).split(0x00))
            {
                if(!la.isEmpty())
                    stringi[i].append(QString(la));
            }
        }
    }
    qDebug() << stringi;

    UpdateStringsTable();
}

void ZR3UIFrame::UpdateStringsTable()
{
    sltw->clear();
    if(stringi.isEmpty())
        return;
    if(stringi.at(0).isEmpty())
        return;
    sltw->setColumnCount(stringi.size()+1);
    sltw->setRowCount(stringi.at(0).size());

    for(int i=1;i<stringi.at(0).size();++i)
        sltw->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
    for(int i=0;i<stringi.size();++i)
    {
        for(int j=0;j<stringi.at(i).size();j++)
            sltw->setItem(j, i+1, new QTableWidgetItem(stringi.at(i).at(j)));
    }
}

void ZR3UIFrame::FrameToUI(QSharedPointer<Frame> frame)
{
    emit InternalDataReaded(frame->pureData().mid(5, frame->pureData().at(4)));
}

uchar ZR3UIFrame::Adr() const
{
    return _adr;
}

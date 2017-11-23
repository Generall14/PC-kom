#include "ZR3UIFrameUI.hpp"
#include "ZR3UIFrame.hpp"

#include <QLayout>
#include <QTabWidget>
#include <QGroupBox>
#include <QHeaderView>

ZR3UIFrameUI::ZR3UIFrameUI(ZR3UIFrame* parent):
    p(parent)
{

}

void ZR3UIFrameUI::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(p->cFrame);
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

void ZR3UIFrameUI::InitDebug()
{
    QVBoxLayout* mainLay = new QVBoxLayout(dbgFrame);
    mainLay->setMargin(6);

    //Protokół
    QGroupBox* gbProt = new QGroupBox("Warstwa protokołu");
    mainLay->addWidget(gbProt);
    QVBoxLayout* gbProtLay = new QVBoxLayout();
    gbProtLay->setMargin(6);
    gbProt->setLayout(gbProtLay);

    QHBoxLayout* Lay1 = new QHBoxLayout();
    gbProtLay->addLayout(Lay1);

    QPushButton* btnHello = new QPushButton("HELLO");
    connect(btnHello, SIGNAL(clicked(bool)), p, SLOT(protHELLO()), Qt::QueuedConnection);
    Lay1->addWidget(btnHello);

    Lay1->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QPushButton* btnSetAdr = new QPushButton("SET_ADR");
    Lay1->addWidget(btnSetAdr);
    connect(btnSetAdr, SIGNAL(clicked(bool)), p, SLOT(protSET_ADR()), Qt::QueuedConnection);

    Lay1->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QPushButton* btnSetNextAdr = new QPushButton("SET_NEXT_ADR");
    Lay1->addWidget(btnSetNextAdr);
    connect(btnSetNextAdr, SIGNAL(clicked(bool)), p, SLOT(protSET_NEXT_ADR()), Qt::QueuedConnection);

    //Aplikacja
    QGroupBox* gbApl = new QGroupBox("Warstwa aplikacji");
    mainLay->addWidget(gbApl);
    QVBoxLayout* gbAplLay = new QVBoxLayout();
    gbAplLay->setMargin(6);
    gbApl->setLayout(gbAplLay);

    QHBoxLayout* Lay2 = new QHBoxLayout();
    gbAplLay->addLayout(Lay2);

    cbFreadFile = new QComboBox();
    cbFreadFile->addItems(readList);
    Lay2->addWidget(cbFreadFile);

    sboffset = new QSpinBox(p->cFrame);
    sboffset->setMinimum(0);
    sboffset->setMaximum(0xFFFF);
    Lay2->addWidget(sboffset);

    sbSize = new QSpinBox(p->cFrame);
    sbSize->setMinimum(0);
    sbSize->setMaximum(0xFF);
    Lay2->addWidget(sbSize);

    QPushButton* btnReadReq = new QPushButton("read req");
    Lay2->addWidget(btnReadReq);
    connect(btnReadReq, SIGNAL(clicked(bool)), this, SLOT(aplReadReq()), Qt::QueuedConnection);

    // String list
    QHBoxLayout* Lay3 = new QHBoxLayout();
    gbAplLay->addLayout(Lay3);

    clang = new QComboBox();
    clang->setToolTip("Język");
    connect(clang, SIGNAL(currentIndexChanged(int)), p, SLOT(UpdateCurrentLanguage(int)), Qt::QueuedConnection);
    Lay3->addWidget(clang);

    QPushButton* btnReadString = new QPushButton("Read Strings");
    connect(btnReadString, &QPushButton::clicked, [=](){p->InitZR3ReadFile(0x0A);});
    Lay3->addWidget(btnReadString);

    QPushButton* btnReadDevDesc = new QPushButton("Read DevDesc");
    connect(btnReadDevDesc, &QPushButton::clicked, [=](){p->InitZR3ReadFile(0x01);});
    Lay3->addWidget(btnReadDevDesc);

    QPushButton* btnReadMethDesc = new QPushButton("Read MethDesc");
    connect(btnReadMethDesc, &QPushButton::clicked, [=](){p->InitZR3ReadFile(0x09);});
    Lay3->addWidget(btnReadMethDesc);

    sltw = new QTableWidget();
    gbAplLay->addWidget(sltw);
    sltw->horizontalHeader()->setVisible(false);
    sltw->verticalHeader()->setVisible(false);
    sltw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sltw->setSelectionMode(QAbstractItemView::SingleSelection);
    sltw->setSelectionBehavior(QAbstractItemView::SelectRows);
    sltw->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    sltw->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    sltw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGroupBox* devFrame = new QGroupBox("DeviceDescriptor");
    gbAplLay->addWidget(devFrame);
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

void ZR3UIFrameUI::aplReadReq()
{
    p->aplReadReq(cbFreadFile->currentText(), sboffset->value(), sbSize->value());
}

void ZR3UIFrameUI::UpdateStringsTable(QList<QStringList> &stringi)
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

    QStringList tlang;
    for(QStringList tl: stringi)
        tlang.append(tl.at(0));
    clang->blockSignals(true);
    clang->clear();
    clang->addItems(tlang);
    clang->blockSignals(false);
}

void ZR3UIFrameUI::UpdateDevDescriptor(QStringList d1, QList<davClass> d2)
{
    if(d1.size()<8)
        return;
    vProg->setText(d1.at(0));
    vPub->setText(d1.at(1));
    vPriv->setText(d1.at(2));
    prod->setText(d1.at(3));
    ser->setText(d1.at(4));
    name->setText(d1.at(5));
    tooltip->setText(d1.at(6));
    opis->setText(d1.at(7));

    QStringList temp;
    for(davClass dc: d2)
    {
        QString str = dc.name + " <";
        for(int i: dc.ptrs)
            str.append(QString("0x%1, ").arg(i&0xFF, 2, 16, QChar('0')));
        str.remove(str.size()-2, 2);
        str.append(">");
        temp.append(str);
    }
    classList->clear();
    classList->addItems(temp);
}

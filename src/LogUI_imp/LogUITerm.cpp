#include "LogUITerm.hpp"
#include <QLayout>
#include <QDebug>
#include "../Factory.hpp"
#include <QTime>
#include <QSpacerItem>
#include <QFile>
#include <QTextStream>

LogUITerm::LogUITerm(QFrame* parent):
    LogUI(parent)
{

}

LogUITerm::~LogUITerm()
{
    QFile config1File;
    QTextStream out(&config1File);

    config1File.setFileName("configs/LogUITermWrapLines.cfg");
    if(config1File.open(QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly))
    {
        out << (int)(chb->isChecked());
        config1File.close();
    }
}

void LogUITerm::LoadConfigs()
{
    QFile config1File;

    config1File.setFileName("configs/LogUITermWrapLines.cfg");
    if(config1File.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        chb->setChecked(QString(config1File.readLine()).toInt());
        config1File.close();
    }
}

void LogUITerm::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(0);

    tedit = new QTextEdit();
    mainLay->addWidget(tedit);

    tedit->setReadOnly(true);
    tedit->setWordWrapMode(QTextOption::NoWrap);

    QHBoxLayout* selectionLayout = new QHBoxLayout();
    mainLay->addLayout(selectionLayout);

    chb = new QCheckBox("Zawijaj wiersze");
    selectionLayout->addWidget(chb);
    connect(chb, SIGNAL(toggled(bool)), this, SLOT(WrapSelect(bool)));

    selectionLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    btnclr = new QPushButton("Wyczyść");
    selectionLayout->addWidget(btnclr);
    connect(btnclr, SIGNAL(clicked(bool)), this, SLOT(Clear()));

    LoadConfigs();
}

void LogUITerm::LogString(QString str, bool)
{
    AppendLog(str);
}

void LogUITerm::AppendLog(QString str)
{
    tedit->append(str);
    lineCounter++;

    if(lineCounter>=LINES_CUT_TR)
    {
        QStringList tlist = tedit->toHtml().split("\n");
        tedit->clear();
        for(int i=tlist.size()-LINES_CUT_SAVE_LINES;i<tlist.size();++i)
            tedit->append(tlist.at(i));
        lineCounter = LINES_CUT_SAVE_LINES;
    }
}

void LogUITerm::Clear()
{
    tedit->clear();
    lineCounter = 0;
}

void LogUITerm::WrapSelect(bool sel)
{
    if(sel)
        tedit->setWordWrapMode(QTextOption::WordWrap);
    else
        tedit->setWordWrapMode(QTextOption::NoWrap);
}

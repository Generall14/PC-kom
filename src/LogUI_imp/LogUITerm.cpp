#include "LogUITerm.hpp"
#include <QLayout>
#include <QDebug>
#include "../Factory.hpp"
#include <QTime>
#include <QSpacerItem>

LogUITerm::LogUITerm(QFrame* parent):
    LogUI(parent)
{

}

void LogUITerm::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);

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

    btnsve = new QPushButton("Zapisz");
    selectionLayout->addWidget(btnsve);
}

void LogUITerm::FrameWrite(QSharedPointer<Frame> frame)
{
    QString temps = "<font face=\"Hack\" color=#6666ff><b>PC ---> DEV ";
    QString templ = QTime::currentTime().toString("HH:mm:ss");
    temps += templ;
    templ.insert(0, "PC ---> DEV ");
    temps += ": </b></font>";
    if(!frame->isValid())
        temps += "<font face=\"Hack\" color=\"red\">";
    temps += frame->toQString();
    templ.append("  " + frame->toQString());
    if(!frame->isValid())
        temps += "</font>";
    AppendLog(temps);
    emit LogString(templ);
}

void LogUITerm::FrameReaded(QSharedPointer<Frame> frame)
{
    QString temps = "<font face=\"Hack\" color=#b3b300><b>PC &#60;--- DEV ";
    QString templ = QTime::currentTime().toString("HH:mm:ss");
    temps += templ;
    templ.insert(0, "PC <--- DEV ");
    temps += ": </b></font>";
    if(!frame->isValid())
        temps += "<font face=\"Hack\" color=\"red\">";
    temps += frame->toQString();
    templ.append("  " + frame->toQString());
    if(!frame->isValid())
        temps += "</font>";
    AppendLog(temps);
    emit LogString(templ);
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

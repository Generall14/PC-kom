#include "Terminal_SendSection.hpp"
#include <QToolButton>
#include <QStringList>

Terminal_SendSection::Terminal_SendSection(QBoxLayout *upperLayout)
{
    QHBoxLayout* send1Lay = new QHBoxLayout();
    upperLayout->addLayout(send1Lay);
    leSend = new QLineEdit();
    leSend->setMinimumWidth(300);
    send1Lay->addWidget(leSend);
    tb = new QToolButton();
    tb->setText(">");
    connect(tb, &QToolButton::clicked, [this](){emit Send(leSend->text());});
    send1Lay->addWidget(tb);

    QHBoxLayout* send2Lay = new QHBoxLayout();
    upperLayout->addLayout(send2Lay);
    cb = new QCheckBox("Wysyłaj automatycznie co [ms]:");
    cb->setChecked(false);
    connect(cb, &QCheckBox::toggled, [this](){timeoutChanged(this->sb->value());});
    send2Lay->addWidget(cb);
    send2Lay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    sb = new QSpinBox();
    sb->setMinimum(100);
    sb->setMaximum(100000);
    sb->setValue(1000);
    send2Lay->addWidget(sb);
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(timeoutChanged(int)));

    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, [this](){emit Send(leSend->text()); timeoutChanged(this->sb->value());});
}

Terminal_SendSection::~Terminal_SendSection()
{
    timer->stop();
    delete timer;
}

QString Terminal_SendSection::Store() const
{
    return QString::number(sb->value()) + ";" + leSend->text();
}

void Terminal_SendSection::Restore(QString desc)
{
    QStringList temp = desc.split(';');
    if(temp.size()!=2)
        return;
    int val;
    bool ok;
    val = temp.at(0).toInt(&ok);
    if(ok)
        sb->setValue(val);
    leSend->setText(temp.at(1));
}

void Terminal_SendSection::Enable()
{
    tb->setEnabled(true);
    pause = false;
    timeoutChanged(sb->value());
}

void Terminal_SendSection::Disable()
{
    tb->setEnabled(false);
    pause = true;
    timer->stop();
}

void Terminal_SendSection::Stop()
{
    timer->stop();
    cb->setChecked(false);
}

void Terminal_SendSection::timeoutChanged(int val)
{
    if((cb->isChecked())&&(!pause))
    {
        timer->stop();
        timer->start(val);
    }
    else
        timer->stop();
}


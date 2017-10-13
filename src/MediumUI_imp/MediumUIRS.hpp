#ifndef MEDIUMUIRS_HPP
#define MEDIUMUIRS_HPP

#include <QFrame>
#include <QComboBox>
#include <QPushButton>
#include <QDebug>
#include "../MediumUI.hpp"

class MediumUiRS : public MediumUI
{
    Q_OBJECT
public:
    MediumUiRS(QFrame* parent);
    virtual ~MediumUiRS();

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();

protected:
    QComboBox* portBox = NULL;
    QComboBox* speedBox = NULL;
    QPushButton* refreshButton = NULL;
    QPushButton* connectButton = NULL;
    QPushButton* disconnectButton = NULL;

    void LoadConfigs();

private slots:
    void Refresh();
    void MakeConnectRequest();
};

#endif

#ifndef MEDIUMUIRS_HPP
#define MEDIUMUIRS_HPP

#include <QFrame>
#include <QComboBox>
#include <QPushButton>
#include <QDebug>
#include "../MediumUI.hpp"
#include "../Utils/Restorable.hpp"

class MediumUiRS : public MediumUI, public Restorable
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
    QComboBox* portBox = nullptr;
    QComboBox* speedBox = nullptr;
    QPushButton* refreshButton = nullptr;
    QPushButton* connectButton = nullptr;
    QPushButton* disconnectButton = nullptr;

    void LoadConfigs();

private slots:
    void Refresh();
    void MakeConnectRequest();
};

#endif

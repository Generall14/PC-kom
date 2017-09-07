#ifndef MEDIUMUIEMPTY_HPP
#define MEDIUMUIEMPTY_HPP

#include <QFrame>
#include "../MediumUI.hpp"

class MediumUiEmpty : public MediumUI
{
    Q_OBJECT
public:
    MediumUiEmpty(QFrame* parent);

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
};

#endif

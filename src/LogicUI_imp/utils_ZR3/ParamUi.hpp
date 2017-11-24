#ifndef PARAMUI_HPP
#define PARAMUI_HPP

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>

#include "param.hpp"

class ParamUi : public QObject
{
    Q_OBJECT
public:
    ParamUi(QWidget* parent, param npar);
    ~ParamUi();
private:
    QWidget* _parent = NULL;
    param _par;
    QGroupBox* mbox = NULL;
};

#endif

#ifndef PARAMUI_HPP
#define PARAMUI_HPP

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QMap>

#include "param.hpp"

class ParamUi : public QObject
{
    Q_OBJECT
public:
    ParamUi(QWidget* parent, param npar);
    ~ParamUi();
    void setData(QByteArray dat);

    static QByteArray getParamValue(param parr);
    static const QMap<QString, int> typeSizes;

private:
    QWidget* _parent = NULL;
    param _par;
    QGroupBox* mbox = NULL;
    QLabel* mVal = NULL;
};

#endif

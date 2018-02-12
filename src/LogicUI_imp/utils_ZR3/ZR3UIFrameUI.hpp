#ifndef ZR3UIFRAMEUI_HPP
#define ZR3UIFRAMEUI_HPP

#include <QObject>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QLabel>
#include <QListWidget>
#include "devClass.hpp"
#include "method.hpp"
#include "transactionDesc.hpp"

class ZR3UIFrame;

class ZR3UIFrameUI : public QObject
{
    friend class ZR3UIFrame;
    Q_OBJECT
public:
    ZR3UIFrameUI(ZR3UIFrame* parent);

    void Init();

private:
    ZR3UIFrame* p = NULL;
    void InitDebug();
    void InitSimpleUI();

    QFrame* dbgFrame = NULL;
    QFrame* suiFrame = NULL;

    //DEBUG
    QComboBox* cbFreadFile = NULL;
    QSpinBox* sboffset = NULL;
    QSpinBox* sbSize = NULL;
    QStringList readList = {"aplDeviceDescriptor", "aplStringListDescriptor", "dupa"};

    QTableWidget* sltw = NULL;
    QComboBox* clang = NULL;

    QLabel* serialNumber = NULL;
    QLabel* vProt = NULL;
    QLabel* vProg = NULL;
    QLabel* vPub = NULL;
    QLabel* vPriv = NULL;
    QLabel* prod = NULL;
    QLabel* ser = NULL;
    QLabel* name = NULL;
    QLineEdit* tooltip = NULL;
    QLineEdit* opis = NULL;
    QListWidget* classList = NULL;

    QComboBox* met = NULL;
    QLabel* lheader = NULL;
    QLabel* ldir = NULL;
    QLabel* ltype = NULL;
    QLabel* larep = NULL;
    QLabel* ltout = NULL;
    QListWidget* lparams = NULL;
    QLineEdit* mettooltip = NULL;
    QLineEdit* metopis = NULL;

    //SIMPLE UI
    QFrame* simpleUiFrame = NULL;

private slots:
    void aplReadReq();

    void UpdateStringsTable(QList<QStringList>& stringi);
    void UpdateDevDescriptor(QStringList d1, QList<davClass> d2);
    void UpdateMetDescriptor(QList<method>& meths);

    void UpdateCurrentMethod(int nr);

    //SImple ui
    void GenSimpleUI();

signals:
    void RegisterTransaction(TransactionDesc);
};

#endif

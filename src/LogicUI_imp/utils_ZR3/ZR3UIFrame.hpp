#ifndef ZR3UIFRAME_HPP
#define ZR3UIFRAME_HPP

#include <QObject>
#include <QFrame>
#include <QPushButton>
#include <QTabWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QStringList>
#include <QList>
#include <QTableWidget>
#include <QLabel>
#include "../../Frame.hpp"
#include "ZR3ReadFile.hpp"

class ZR3UIFrame : public QObject
{
    Q_OBJECT
public:
    ZR3UIFrame(QFrame* parent, uchar adr);

    void Init();
    uchar Adr() const;

public slots:
    void FrameToUI(QSharedPointer<Frame> frame);

signals:
    void FrameToMendium(QSharedPointer<Frame> frame);
    void PureDataToMedium(QByteArray ar);
    void InternalDataReaded(QByteArray ba);
    void AdresChanged(uchar);
    void Error(QString);

protected:
    QFrame* cFrame = NULL;
    uchar _adr;

    QFrame* dbgFrame = NULL;
    QFrame* suiFrame = NULL;

    QLabel* vProg = NULL;
    QLabel* vPub = NULL;
    QLabel* vPriv = NULL;
    QLabel* prod = NULL;
    QLabel* ser = NULL;
    QLabel* name = NULL;
    QLineEdit* tooltip = NULL;
    QLineEdit* opis = NULL;
    QComboBox* classList = NULL;

    QByteArray protHELLO;

    static const char _myAdr = 0xFE;

    void InitDebug();

    QComboBox* cbFreadFile = NULL;
    QSpinBox* sboffset = NULL;
    QSpinBox* sbSize = NULL;
    QStringList readList = {"aplDeviceDescriptor", "aplStringListDescriptor", "dupa"};

    ZR3ReadFile* rfile = NULL;
    void InitZR3ReadFile(uchar header);

    QByteArray strings;
    QList<QStringList> stringi;
    QTableWidget* sltw = NULL;
    void ParseStrings();
    void UpdateStringsTable();

protected slots:
    void protSET_ADR();
    void protSET_NEXT_ADR();

    void aplReadReq();

    void FinalizeZR3ReadFile(uchar _header, QByteArray arr);
};

#endif
